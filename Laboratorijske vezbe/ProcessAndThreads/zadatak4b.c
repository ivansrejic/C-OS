#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARGS 20
#define MAX_ARG_LENGTH 100

int main(int argc, char * argv[])
{
  int i;
  char **argumenti = (char**)malloc((argc+1)*sizeof(char*));
  argumenti[0] = (char *)malloc((strlen("./zadatak4a")+1) * sizeof(char));
  strcpy(argumenti[0], "./zadatak4a");
  for (i = 1; i < argc; i++)
  {
    argumenti[i] = (char *)malloc((strlen(argv[i])+1) * sizeof(char));
    strcpy(argumenti[i], argv[i]);
  }
  /*Poslednji argument mora da bude NULL da bi ukazao na kraj vektora sa
   *argumentima*/
  argumenti[argc] = NULL;
  if (fork() == 0)
  {/*Izvrsava novokreirani proces*/
    if (execv("./zadatak4a", argumenti) < 0)
    {
      printf("Doslo je do greske!\n");
      exit(1);
    }
  }
  else
    /*Izvrsava proces roditelj koji ceka da se dete zavrsi*/
    wait(NULL);
  /*Oslobadjamo memoriju koja je zauzeta za vektor argumenata */
  for (i = 0; i < argc; i++)
    free(argumenti[i]);
  free(argumenti);
  return 0;
}
