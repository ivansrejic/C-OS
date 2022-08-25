#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  int pid;
  char datoteka[100];
  /*Sa standardnog ulaza citamo ime datoteke koju zelimo da kopiramo*/
  scanf("%s", datoteka);
  pid = fork();
  
  if (pid == 0)
  {
    if (execlp("cp", "cp", datoteka, "./tmp", NULL) < 0)
    {
      printf("Doslo je do greske!\n");
      exit(1);
    }
  }
  else
    /*Izvrsava proces roditelj koji ceka da se njegov proces dete zavrsi odnosno
    *da se kopiranje izvrsi*/
    wait(NULL);
  return 0;
}
