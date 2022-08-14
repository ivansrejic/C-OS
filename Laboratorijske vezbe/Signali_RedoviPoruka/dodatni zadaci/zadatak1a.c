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
  int N; //broj poruka koje ce biti poslate
  int redid;
  int i,j;
  struct poruka bafer;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  //Pribavlja se referenca na red poruka. Red se kreira ukoliko ne postoji
  redid = msgget(RED_PORUKA, IPC_CREAT | 0666);
  if (redid < 0)
  {
    printf("Doslo je do greske prilikom kreiranja novog procesa\n");
    exit(1);
  }
  //Odredjuej se broj poruka koje ce biti poslate
  srand(tm.tm_sec);
  N = rand() % 20;
  //U red se salje N slucajnih pozitivnih celih brojeva + (-1) na kraju za kraj
  //komunikacije
  for (i = 0; i < N + 1; i++)
  {
    if (i == N)
    {
      bafer.std.index=-1;//poslednja poruka je -1
    }
    else
    {
      bafer.std.index = rand() % 20000;//slucajno generisani brojevi
    }
    for(j=0;j<MAX_PORUKA-1;j++)
    {
      bafer.std.ime[j] = 65 + rand()%26;
    }
    bafer.std.ime[j] = '\0';
    //Tip poruke u ovom primeru nije bitan i postavlja se na 1
    bafer.tip = 1;
    //Poruka se salje u red
    if (msgsnd(redid, &bafer, sizeof(bafer) - sizeof(long), 0) < -1)
    {
      printf("Doslo je do greske prilikom prijema poruke\n");
      exit(1);
    }
  }
  return 0;
}