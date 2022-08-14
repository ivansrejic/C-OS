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
	int N; //broj poruka koje ce biti poslate
	int redid;
	int i;
	struct poruka bafer;

	//Pribavlja se referenca na red poruka. Red se kreira ukoliko ne postoji
	redid = msgget(RED_PORUKA, IPC_CREAT | 0666);
	if (redid < 0)
	{
		printf("Doslo je do greske prilikom kreiranja novog procesa\n");
		exit(1);
	}

	//Odredjuej se broj poruka koje ce biti poslate
	N = rand() % 20;

	//U red se salje N slucajnih pozitivnih celih brojeva + (-1) na kraju za kraj komunikacije
	for (i = 0; i < N + 1; i++)
	{
		if (i == N)
			sprintf(bafer.tekst, "%d", -1);//poslednja poruka je -1
		
		else
			sprintf(bafer.tekst, "%d", rand() % 100);//slucajno generisani brojevi
		
		//Tip poruke u ovom primeru nije bitan i postavlja se na 1
		bafer.tip = 1;

		//Poruka se salje u red
		if (msgsnd(redid, &bafer, sizeof(bafer.tekst), 0) < -1)
		{
			printf("Doslo je do greske prilikom prijema poruke\n");
			exit(1);
		}
	}

	return 0;
}