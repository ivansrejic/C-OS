#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
int main(int argc, char* argv[])
{
  int fd;
  // Otvara tekstualnu datoteku
  fd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0666);
  // Redirektuje standardni izlaz na otvorenu tekstualnu datoteku
  dup2(fd, 1);
  //close(1);
  //dup(fd);
  // Zatvara deskriptor za datoteku (kopija ostaje)
  close(fd);
  // Poziva izvrsnu datoteku
  execlp(argv[1], argv[1], NULL);
  printf("Ne bi trebalo nikada da se izvrsi!");
}
