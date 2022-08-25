#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include <sys/shm.h>
#define PRVI_KEY 10001
#define DRUGI_KEY 10002
#define TRECI_KEY 10003
#define MEM_KEY 10005
#define N 1024
union semun
{
  int val;
  struct semid_ds *buf;
  ushort *array;
  struct seminfo * __buf;
  void * __pad;
};

int main()
{
  int sem1, sem2, sem3, memid; //reference semafora i deljive memorije
  int i, j;
  FILE * f;
  //pokazivac na niz bajtova koji se koristi za mapiranje deljive memorije
  char * shmem;
  //pomocne strukture za inicijalizaciju i operacije nad semaforom
  struct sembuf lock = {0, -1, 0};
  struct sembuf unlock = {0, 1, 0};
  union semun opts;
  //kreiramo i inicijalizujemo semafore
  //inicijalno se postavljaju na vrednosti 1-0-0 jer zapocinje da se izvrsava
  //proces P1 pa naknon njega proces P1 pa tek onda P3
  sem1 = semget(PRVI_KEY, 1, IPC_CREAT | 0666);
  sem2 = semget(DRUGI_KEY, 1, IPC_CREAT | 0666);
  sem3 = semget(TRECI_KEY, 1, IPC_CREAT | 0666);
  opts.val = 1;
  semctl(sem1, 0, SETVAL, opts);
  opts.val = 0;
  semctl(sem2, 0, SETVAL, opts);
  opts.val = 0;
  semctl(sem3, 0, SETVAL, opts);
  //kreiramo deljenu memoriju
  memid = shmget(MEM_KEY, N * sizeof(char), IPC_CREAT | 0666);
  if (fork() == 0)
  {
    //proces P1 koji generise slova a-z i semsta ih u prvih 512 bajtova
    //mapiramo deljenu memoriju
    shmem = (char *)shmat(memid, NULL, 0);
    for (i = 0; i < 10; i++)
    {
      semop(sem1, &lock, 1);//P(S1)
      //upisujemo slova u prvih 512 bajtova
      for (j = 0; j < N/2; j++)
	       shmem[j] = 'a' + rand() % ('z'-'a' + 1);
      semop(sem2, &unlock, 1); //V(S2)
    }
    //izbacujemo delejnu memoriju iz adresnog prostora
    shmdt(shmem);
    return 0;
  }
  if (fork() == 0)
  {
    //proces P2 koji generise cifre i smesta ih u poslednjih 512 bajtova
    //mapiramo deljenu memoriju
    shmem = (char *)shmat(memid, NULL, 0);
    for (i = 0; i < 10; i++)
    {
      semop(sem2, &lock, 1);//P(S2)
      //upisujemo slova u prvih 512 bajtova
      for (j = N/2; j < N; j++)
	       shmem[j] = '0' + rand() % ('9' - '0' + 1);
      semop(sem3, &unlock, 1); //V(S3)
    }
    //izbacujemo delejnu memoriju iz adresnog prostora
    shmdt(shmem);
    return 0;
  }
  //roditeljski proces P3 koji stampa sadrzaj deljene memorije u datoteku
  //mapiramo deljenu memoriju
  shmem = (char *)shmat(memid, NULL, SHM_RDONLY);
  for (i = 0; i < 10; i++)
  {
    semop(sem3, &lock, 1);//P(S3)
    //sadrzaj deljene memorije upisujemo u datoteku
    char buff[N + 1];
    //koristimo funkciju strncpy jer u deljenoj memoriji na kraju nemamo /0
    //kao kraj stringa
    strncpy(buff, shmem, N);
    buff[N] = '\0';
    //sadrzaj bafera upisujemo u datoteku
    f = fopen("sadrzaj", "a");
    fprintf(f, "%s\n", buff);
    fclose(f);
    sleep(5);
    semop(sem1, &unlock, 1); //V(S1)
  }
  //izbacujemo delejnu memoriju iz adresnog prostora
  shmdt(shmem);
  semctl(sem1, 0, IPC_RMID, opts);
  semctl(sem2, 0, IPC_RMID, opts);
  semctl(sem3, 0, IPC_RMID, opts);
  shmctl(memid, IPC_RMID, 0);
  return 0;
}
