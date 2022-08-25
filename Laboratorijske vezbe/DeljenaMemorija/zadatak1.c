#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#define FULL_KEY 100001
#define EMPTY_KEY 10002
#define MUTEX_KEY 10003
#define MEM_KEY 10005
#define N 10
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
  //celobrojne reference na semafore i deljenu memoriju
  int fullid, emptyid, mutexid;
  int memid;
  int * shmem;//pokazivac za mapiranje deljene memorije u adresni procesa
  int i;
  struct sembuf lock = {0, -1, 0};
  struct sembuf unlock = {0, 1, 0};
  union semun opts;
  //kreiranje i inicijalizacija semafora FULL
  fullid = semget(FULL_KEY, 1, IPC_CREAT | 0666);
  if (fullid < 0)
  {
    printf("Greska prilikom kreiranja semafora FULL\n");
    exit(1);
  }
  opts.val = 0;
  if (semctl(fullid, 0, SETVAL, opts) < 0)
  {
    printf("Greska prilikom inicijalizacije semafora FULL\n");
    exit(1);
  }
  //kreiranje i inicijalizacija semafora empty
  emptyid = semget(EMPTY_KEY, 1, IPC_CREAT | 0666);
  if (emptyid < 0)
  {
    printf("Greska prilikom kreiranja semafora EMPTY\n");
    exit(1);
  }
  opts.val = N;
  if (semctl(emptyid, 0, SETVAL, opts) < 0)
  {
    printf("Greska prilikom inicijalizacije semafora EMPTY\n");
    exit(1);
  }
  //kreiranje i inicijalizacija semafora MUTEX
  mutexid = semget(MUTEX_KEY, 1, IPC_CREAT | 0666);
  if (mutexid < 0)
  {
    printf("Greska prilikom kreiranja semafora MUTEX\n");
    exit(1);
  }
  opts.val = 1;
  if (semctl(mutexid, 0, SETVAL, opts) < 0)
  {
    printf("Greska prilikom inicijalizacije semafora MUTEX\n");
    exit(1);
  }
  //kreira se deljiva memorija velicine N celih brojeva
  memid = shmget(MEM_KEY, N * sizeof(int), IPC_CREAT | 0666);
  if (memid < 0)
  {
    printf("Greska prilikom kreiranja deljive memorije\n");
    exit(1);
  }
  if (fork() == 0)
  {
    //izvrsava proces dete koje funkcionise kao proizvodjac
    //pozicija u baferu u kojoj ce se obaviti sledeci upis
    int next_write = 0;
    //mapira se deljiva memorija u adresni prostor procesa
    shmem = shmat(memid, NULL, 0);
    if (shmem == NULL)
    {
      printf("Greska prilikom mapiranja deljive memorije\n");
      exit(1);
    }
    for (i = 0; i < 20; i++)
    {
      //standardna sekvenca operacija za proces proizvodjac
      semop(emptyid, &lock, 1);
      semop(mutexid, &lock, 1);
      //upis podataka u deljivu memoriju
      int p = rand() % 100;
      shmem[next_write] = p;
      next_write = (next_write + 1) % N;
      printf("Generisana vrednost je %d\n", p);
      semop(mutexid, &unlock, 1);
      semop(fullid, &unlock, 1);
      sleep(2);
    }
    //izbacujemo deljenu memoriju iz adresnog prostora
    shmdt(shmem);
  }
  else
  {
    //izvrsava proces roditelj koji funkcionise kao potrosac
    //pozicija u baferu sa koje ce se obaviti sledece citanje
    int next_read = 0;
    //mapiraa se deljiva memorija u adresni prostor procesa
    shmem = shmat(memid, NULL, 0);
    if (shmem == NULL)
    {
      printf("Greska prilikom mapiranja deljive memorije\n");
      exit(1);
    }
    for (i = 0; i < 20; i++)
    {
      //standardna sekvenca operacija za proces potrosac
      semop(fullid, &lock, 1);
      semop(mutexid, &lock, 1);
      //upis podataka u deljivu memoriju
      printf("Ocitana vrednost je %d\n", shmem[next_read]);
      next_read = (next_read + 1) % N;
      semop(mutexid, &unlock, 1);
      semop(emptyid, &unlock, 1);
      sleep(5);
    }
    //izbacujemo deljenu memoriju iz adresnog prostora
    shmdt(shmem);
    //uklanjamo sve semafore i deljenu memoriju
    semctl(fullid, 0, IPC_RMID, 0);
    semctl(emptyid, 0, IPC_RMID, 0);
    semctl(mutexid, 0, IPC_RMID, 0);
    shmctl(memid, IPC_RMID, 0);
  }
  return 0;
}
