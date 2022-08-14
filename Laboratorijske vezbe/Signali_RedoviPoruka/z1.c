//Korišćenjem programskog jezika C napisati UNIX/Linux program koji onemogućava da se tekući
//proces prekine jednim pritiskom kombinacije tastera Ctrl-C. Proces se prekida tek kada se ova
//kombinacija tastera pritisne dva puta za redom.


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* Funkcija za obradu signala */
void catch_int(int sig_num)
{
	/* Postavlja se default funkcija za obradu signala za sledeci put kada bude pritisnuta kombinacija Ctrl-C */
	signal(SIGINT, SIG_DFL);
	printf("Nije moguce prekinuti program!\n");
	fflush(stdout);
}

int main(int argc, char* argv[])
{
	/* Postavlja funkciju catch_int da obradjuje signal SIGINT */
	signal(SIGINT, catch_int);

	/* Beskonacna petlja */
	for ( ; ; )
		pause();
}
