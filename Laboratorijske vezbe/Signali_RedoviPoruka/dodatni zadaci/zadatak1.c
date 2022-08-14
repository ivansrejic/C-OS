#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <time.h>
#define RED_PORUKA 10001
#define MAX_PORUKA 10
struct student
{
  int index;
  char ime[MAX_PORUKA];
};
struct poruka
{
  long tip;
  struct student std;
};
int main()
{
  int pid;
  int redid;
  struct student std;
  struct poruka bafer;
  //Kreiramo novi proces
  pid = fork();
  if (pid < 0)
  {
    printf("Doslo je do greske prilikom kreiranja novog procesa\n");
    exit(1);
  }
  if (pid == 0)
  {
    //Izvrsava pbroj);roces dete
    if (execl("zadatak1a", "zadatak1a", NULL) < 0)
    {
      printf("Doslo je do greske prilikom ucitavanja izvrsne datoteke\n");
    }
    exit(1);
  }
  //Kod koji izvrsava samo proces roditelj
  //Pribavlja se referenca na red poruka. Red se kreira ukoliko ne postoji
  redid = msgget(RED_PORUKA, IPC_CREAT | 0666);
  if (redid < 0)
  {
    printf("Doslo je do greske prilikom kreiranja novog procesa\n");
    exit(1);
  }
  //primaju se poruke iz reda poruka sve dok ne stigne poruka -1
  do
  {
    if (msgrcv(redid, &bafer, sizeof(bafer) - sizeof(long), 0, 0) < -1)
    {
      printf("Doslo je do greske prilikom prijema poruke\n");
      exit(1);
    }
    std = bafer.std;
    printf("%d\n", std.index);
    printf("%s\n", std.ime);
  }
  while( std.index > -1);
  wait(NULL);
  msgctl(redid, IPC_RMID, 0);
  return 0;
}