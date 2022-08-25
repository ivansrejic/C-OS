#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
int main(int argc, char* argv[])
{
  int fd;
  int backupFd;
  // Otvara tekstualnu datoteku
  fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0666);
  // Smesta standardni izlaz za koriscenje kasnije
  // dup ce duplirati standardni izlaz na najmanji slobodan deskriptor
  backupFd = dup(1);
  // Redirektuje standardni izlaz na otvorenu tekstualnu datoteku
  dup2(fd, 1);
  // Zatvara deskriptor za datoteku (kopija ostaje)
  close(fd);
  printf("Upisujem u fajl\n");
  //obavezno forsirati izlaz da pre promene standardnog ulaza
  fflush(stdout);
  dup2(backupFd,1);
  close(backupFd);
  printf("Ispisujem u konzolu\n");
}
