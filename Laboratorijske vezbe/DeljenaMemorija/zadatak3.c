#include "zadatak3.h"
int main()
{
  int s, mutex, statusi;
  int i;
  enum status * shmem;
  union semun opts;
  s = semget(SEMAFORI_KEY, N, IPC_CREAT| 0666);
  
  //sve semafore koji su vezani za filozofe inicijalizujemo na 1
  opts.val = 0;
  for (i = 0; i < N; i++)
    semctl(s, i, SETVAL, opts);
  mutex = semget(MUTEX_KEY, 1, IPC_CREAT | 0666);
  opts.val = 1;
  semctl(mutex, 0, SETVAL, opts);
  statusi = shmget(STATUS_KEY, N * sizeof(enum status), IPC_CREAT | 0666);
  //mapiramo deljenu memoriju u adresni prostor procesa
  shmem = (enum status *)shmat(statusi, NULL, 0);
  //inicijalizujemo status svih filozofa na THINKING
  for (i = 0; i < N; i++)
    shmem[i] = THINKING;
  //izbacujemo deljivu memoriju iz adresnog prostora jer nam vise nije potrebna
  shmdt(shmem);
  //pokrecemo N filozofa
  for (i = 0; i < N; i++)
  {
    if (fork() == 0)
    {
      char buff[2];
      sprintf(buff, "%d", i);
      execl("zadatak3a", "zadatak3a", buff, NULL);
    }
  }
  //cekamo da se svi filozofi zavrse
  for (i = 0; i < N; i++)
    wait(NULL);
  //brisemo sve kreirane objekte
  semctl(s, 0, IPC_RMID, opts);
  semctl(mutex, 0, IPC_RMID, opts);
  shmctl(statusi, IPC_RMID, 0);
  return 0;
}
