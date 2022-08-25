#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//Maksimalna velicina bafera za slanje i prihvatanje poruka
#define MAX_BUF 80
int main(int argc, char * argv[])
{
  int pid;
  int pd[2];
  char buffer[MAX_BUF];
  FILE * f;
  int count = 0;
  //Najpre se kreira datavod. U slucaju greske program se prekida
  if (pipe(pd) < 0)
  {
    printf("Doslo je do greske prilikom kreiranja datavoda.\n");
    exit(1);
  }
  //Kreira se proces dete sa kojim ce ici komunikacija
  pid = fork();
  //U slucaju greske program se prekida
  if (pid < 0)
  {
    printf("Doslo je do greske prilikom kreiranja novog procesa.\n");
    exit(1);
  }
  //Deo koda koji izvrsava proces dete
  if (pid == 0)
  {
    //Proces dete samo upisuje podatke pa zatvara kraj datavoda za citanje
    close(pd[0]);
    //Otvara se datoteka iz koje se citaju podaci
    f = fopen("podaci", "r");
    fgets(buffer, MAX_BUF, f);
    while(!feof(f))
    {
      write(pd[1], buffer, MAX_BUF);
      fgets(buffer, MAX_BUF, f);
    }
    //Kraj komunikacija pa se zatvara i kraj datavoda za pisanje
    printf("Zatvaram predajnu stranu\n");
    close(pd[1]);
  }
  else
  {
    //Deo koda koji izvrsava proces roditelj
    //Proces roditelj cita podatke iz datavoda pa se zatvara kraj datavoda za pisanje
    close(pd[1]);
    while(1)
    {
      //Citamo podatek iz datavoda. Funkcija vraca broj ocitanih bajtova
      count = read(pd[0], buffer, MAX_BUF);
      //Ako je ocitano 0B znaci da je komunikacija zavrsena
      if (count == 0){
	printf("Procitao sam 0\n");
	break;
      }
      printf("%s", buffer);
    }
    //Komunikacija je zavrsena pa zatvaramo i kraj datavoda za citanje
    close(pd[0]);
  }
}
