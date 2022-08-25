//Korišćenjem programskog jezika C napisati UNIX/Linux program koji od korisnika očekuje da sa
//tastature unese korisničko ime. Ukoliko korisnik ne unese ništa u roku od 30 sekundi proces
//obaveštava korisnika da je vreme za unos isteklo i izlazi.


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
char user[40];


/* Handler za alarm */
void catch_alarm(int sig_num)
{
	printf("Operacija je istekla. Izlazim...\n\n");
	exit(0);
}

int main(int argc, char* argv[])
{
	/* Signal handler za ALRM signal */
	signal(SIGALRM, catch_alarm);

	/* Prompt korisniku da unese string */
	printf("Username: ");
	fflush(stdout);

	/* Startuje alarm od 30 sekundi */
	alarm(30);

	/* Ceka da korisnik unese ime */
	gets(user);

	/* Ukoliko korisnik unese ime uklanja alarm */
	alarm(0);

	printf("Username: '%s'\n", user);

	return 0;
}
