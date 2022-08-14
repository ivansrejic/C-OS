#include "zadatak3.h"
//globalne promenljive koje treba da budu vidljive u svim funkcijama
int s, mutex, statusi;
enum status * shmem;
struct sembuf lock = {0, -1, 0};
struct sembuf unlock = {0, 1, 0};
void think(int no);
void take_forks(int no);
void put_forks(int no);
void eat(int no);
void test(int no);
int main(int argc, char * argv[])
{
  int i;
  int no = atoi(argv[1]);
  //pribavljamo referencu na semafore S koji predstavljaju filozofe
  s = semget(SEMAFORI_KEY, N, 0666);
  //pribavljamo referencu na MUTEX semafor
  mutex = semget(MUTEX_KEY, 1, 0666);
  statusi = shmget(STATUS_KEY, N * sizeof(enum status), 0666);
  //mapiramo deljenu memoriju u adresni prostor procesa
  shmem = (enum status *)shmat(statusi, NULL, 0);
  for (i = 0; i < 10; i++)
  {
    think(no);
    take_forks(no);
    eat(no);
    put_forks(no);
  }
  //izbacujemo deljenu memoriju iz adresnog prostora
  shmdt(shmat);
  return 0;
}
void think(int no)
{
  //razmislja najvise 10s
  printf("Filozof %d razmislja\n", no);
  sleep(rand() % 11);
}
void eat(int no)
{
  //jede najvise 5s
  printf("Filozof %d vecera\n", no);
  sleep(rand() % 6);
}
void take_forks(int no)
{
  //zakljucavamo MUTEX
  lock.sem_num = 0;
  semop(mutex, &lock, 1);
  //od mnogo razmisljanja se ogladni
  shmem[no] = HUNGRY;
  //filozof pokusava da pribavi viljuske
  test(no);
  //otkljucavamo MUTEX
  unlock.sem_num = 0;
  semop(mutex, &unlock, 1);
  //P operacija nad odgovarajucim semaforom S
  //ukoliko viljuske nisu pribavljene filozof se blokira
  lock.sem_num = no;
  semop(s, &lock, 1);
}
void test(int no)
{
  if (shmem[no] == HUNGRY
    && shmem[(no + N -1) % N] != EATING
    && shmem[(no + 1) % N] != EATING)
  {
    shmem[no] = EATING;
    unlock.sem_num = no;
    semop(s, &unlock, 1);
  }
}
void put_forks(int no)
{
  //zakljucavamo MUTEX
  lock.sem_num = 0;
  semop(mutex, &lock, 1);
  //posle jela filozof ponovo moze da misli
  shmem[no] = THINKING;
  //signalizira svojim susedima da je oslobodio viljusku
  test((no + N -1) % N);
  test((no + 1) % N);
  //otkljucavamo MUTEX
  unlock.sem_num = 0;
  semop(mutex, &unlock, 1);
}
