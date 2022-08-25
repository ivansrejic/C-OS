/*Korišćenjem programskog jezika C napisati UNIX/Linux program koji simulira problem
proizvođač/potrošač korišćenjem redova poruka (message-queues). Glavni program se deli u dva
procesa. Prvi proces (proizvođač) kreira N slučajnih pozitivnih celih brojeva i šalje ih drugom
procesu. N se određuje tokom izvršenja, takođe kao slučajan pozitivan ceo broj. Po završetku
slanja, prvi proces šalje -1 kao kod za kraj. Drugi proces (potrošač) preuzima poslate brojeve iz
poruka i štampa ih na standardnom izlazu.*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define RED_PORUKA 10001
#define MAX_PORUKA 10

struct poruka
{
	long tip;
	char tekst[MAX_PORUKA];
};

int main()
{
	int pid;
	int redid;
	int broj = 0;
	struct poruka bafer;

	//Kreiramo novi proces
	pid = fork();

	if (pid < 0)
	{
		printf("Doslo je do greske prilikom kreiranja novog procesa\n");
		exit(1);
	}
	if (pid == 0)
	{
		//Izvrsava proces dete
		if (execl("zadatak5a", "zadatak5a", NULL) < 0)
		{
			printf("Doslo je do greske prilikom ucitavanja izvrsne datoteke\n");
		}

		exit(1);
	}

	//Kod koji izvrsava samo proces roditelj
	//Pribavlja se referenca na red poruka. Red se kreira ukoliko ne postoji
	redid = msgget(RED_PORUKA, IPC_CREAT | 0666);

	if (redid < 0)
	{
		printf("Doslo je do greske prilikom kreiranja novog procesa\n");
		exit(1);
	}

	//primaju se poruke iz reda poruka sve dok ne stigne poruka -1
	do
	{
		if (msgrcv(redid, &bafer, MAX_PORUKA, 0, 0) < -1)
		{
			printf("Doslo je do greske prilikom prijema poruke\n");
			exit(1);
		}

		broj = atoi(bafer.tekst);
		printf("%d\n", broj);
	}
	while( broj > -1);

	wait(NULL);
	msgctl(redid, IPC_RMID, 0);
	return 0;
}