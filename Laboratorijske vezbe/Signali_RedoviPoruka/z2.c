//Korišćenjem programskog jezika C napisati UNIX/Linux program koji može da se prekine samo
//ako se kombinacija tastera Ctrl-C pritisne pet puta za redom. Ukoliko korisnik pritisne kombinaciju
//tastera Ctrl-Z program na ekranu ispisuje koliko puta do sada je pritisnuto Ctrl-C.


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define CTRL_C_THRESHOLD 5
int ctrl_c_count = 0;

/* Funkcija za obradu Ctrl-C signala */
void catch_int(int sig_num)
{
	/* Ponovo postavlja signal handler */
	signal(SIGINT, catch_int);

	/* Inkrementira brojac i proverava da li je pritisnuto Ctrl-C dovoljan broj*puta */
	ctrl_c_count++;

	if (ctrl_c_count >= CTRL_C_THRESHOLD)
	{
		char answer[30];
		
		/* Pita korisnika da li stvarno zeli da prekine proces */
		printf("\nRealy Exit? [y/N]: ");
		fflush(stdout);
		fgets(answer, sizeof(answer), stdin);
		if (answer[0] == 'y' || answer[0] == 'Y') 
		{
			printf("\nExiting...\n");
			fflush(stdout);
			exit(0);
		}
		else
		{
			printf("\nContinuing\n");
			fflush(stdout);

			/* reset Ctrl-C counter */
			ctrl_c_count = 0;
		}
	}
}


/* Ctrl-Z signal handler */
void catch_suspend(int sig_num)
{
	/* Ponovo postavlja signal handler */
	signal(SIGTSTP, catch_suspend);

	/* Stampa Ctrl-C brojac */
	printf("\n\nDo sada, Ctrl-C je pritisnuto '%d' puta\n\n", ctrl_c_count);
	fflush(stdout);
}


int main(int argc, char* argv[])
{
	/* Postavlja Ctrl-C and Ctrl-Z signal handlere */
	signal(SIGINT, catch_int);
	signal(SIGTSTP, catch_suspend);

	/* Beskonacna petlja */
	for ( ;; )
		pause();
	
	return 0;
}
