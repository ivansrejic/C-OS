#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//Maksimalna velicina bafera za slanje i prihvatanje poruka
#define MAX_BUF 80
int main(int argc, char * argv[])
{
  int pd1;
  char buffer[MAX_BUF];
  FILE * f;
  //Najpre se proverava da li ima dovoljno ulaznih argumenatareira se proces dete sa kojim ce ici komunikacija
  if (argc < 2)
  {
    printf("Nema dovoljno ulaznih argumenata\n");
    exit(1);
  }
  //U slucaju da je sve u redu sa ulaznim argumentima, argument sa pozicije 1, koji predstavlja deskriptor datavoda, se konvertuje u int
  pd1 = atoi(argv[1]);
  //Deskriptor datavoda mora da bude vrednost razlicita od 0
  if (pd1 == 0)
  {
    printf("Preneta je pogresna vrednost za deskriptor datavoda.\n");
    exit(1);
  }
  //Otvara se datoteka iz koje se citaju podaci
  f = fopen("podaci", "r");
  fgets(buffer, MAX_BUF, f);
  while(!feof(f))
  {
    write(pd1, buffer, MAX_BUF);
    fgets(buffer, MAX_BUF, f);
  }
  //Kraj komunikacija pa se zatvara i kraj datavoda za pisanje
  close(pd1);
}
