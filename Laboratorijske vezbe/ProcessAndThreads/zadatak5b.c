#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char * argv[])
{
  int i;
  char * argumenti[4];
  int pid;
  char datoteka[100];
  /*Sa standardnog ulaza citamo ime datoteke koju zelimo da kopiramo*/
  scanf("%s", datoteka);
  /*Izvrsava proces dete koji ce obaviti kopiranjeKopiranje se vrsi komandom: cp ime_dat ./tmp */
  /*Argument na poziciji 0 je uvek jednak imenu programa koji pozivamo. */  
  argumenti[0] = (char *)malloc(100 * sizeof(char));
  strcpy(argumenti[0], "cp");
  /*Argument na poziciji 1 je datoteka koju kopiramo */  
  argumenti[1] = (char *)malloc(100 * sizeof(char));
  strcpy(argumenti[1], datoteka);
  /*Argument na poziciji 2 je direktorijum u koji kopiramo */  
  argumenti[2] = (char *)malloc(100 * sizeof(char));
  strcpy(argumenti[2], "./tmp");
  /*Poslednji argument mora da bude NULL da bi ukazao na kraj vektora sa argumentima*/ 
  argumenti[3] = NULL;
  pid = fork();
  if (pid == 0)
  {
      /*Koristimo  funkciju  execvp  jer  ulazne  argumente  procesa  koji  pozivamo prosledjujemo
       u vidu vektora a izvrsna datoteka (Linux komanda cp) se nalazinegde  na  putanji  koja  je
       definisana  environment  promenljivom  PATH.  Prvi argument je ime izvrsne datoteke koju
       pozivamo, drugi argument je vektorsa ulaznim argumentima koje prosledjujemo programu koji 
       pozivamo. */
      if (execvp("cp", argumenti) < 0)
      {
        printf("Doslo je do greske!\n");
        exit(1);
      }
  }
  else /*Izvrsava proces roditelj koji ceka da se njegov proces dete zavrsi odnosno da se kopiranje izvrsi*/
  {
    wait(NULL);
    for (i = 0; i < 3; i++)
      free(argumenti[i]);
  }
  return 0;
}
