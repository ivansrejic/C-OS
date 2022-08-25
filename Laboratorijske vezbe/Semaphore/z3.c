/*Korišćenjem programskog jezika C kreirati višenitni Linux proces. 
U okviru procesa se izvršavaju tri niti (N1, N2 i N3) koje pristupaju deljivom resursu. 
Deljivi rersurs je predstavljen celobrojnim nizom od 20 elemenata. 

Niti pristupaju deljivom resursu na sledeći način:
• Nit N1, na svake 2 sekunde, upisuje slučajnu vrednost na slučajnu poziciju u prvoj polovini niza
(pozicije 0 do 9).
• Nit N2, na svake 4 sekunde, upisuje slučajnu vrednost na slučajnu poziciju u drugoj polovini
niza (pozicije 10 do 19).
• Nit N3, na svakih 8 sekundi, upisuje slučajnu vrednost na slučajnu poziciju u nizu (pozicije 0 do
19).
Korišćenjem nekog od poznatih mehanizama za sinhronizaciju i međusobno isključenje niti, obezbediti
da nit N3 može da pristupi deljivom resursu samo ako u datom trenutku deljivom resursu ne pristupa ni
nit N1 ni nit N2. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 20

/*Deljivi resurs koji se definise kao globalna promenljiva*/
int niz[N];

/*Semafori za medjusobno iskljucenje prilikom priatupanja deljivom resursu*/
pthread_mutex_t mutex1, mutex2;

void* nit1(void * arg)
{
	int pos;

	while(1)
	{
		/*Pristupanje deljivom resursu u KS*/
		pthread_mutex_lock(&mutex1);

		/*Vrednost se upisuje u prvu polovinu niza tj. pozicije 0-9*/
		pos = rand() % 10;
		niz[pos] = rand() % 100;
		printf("Prva nit je na poziciju %d upisala vrednost %d\n", pos,
		niz[pos]);

		pthread_mutex_unlock(&mutex1);

		/*Pauziramo 2s*/
		sleep(2);
	}
}
void * nit2(void * arg)
{
	int pos;
	while(1)
	{
		/*Pristupanje deljivom resursu u KS*/
		pthread_mutex_lock(&mutex2);

		/*Vrednost se upiosuje u drugu polovinu niza tj. pozicije 10-19;*/
		pos = rand() % 10 + 10;
		niz[pos] = rand() % 100;
		printf("Druga nit je na poziciju %d upisala vrednost %d\n", pos,
		niz[pos]);

		pthread_mutex_unlock(&mutex2);

		/*Pauziramo 4s*/
		sleep(4);
	}
}
void * nit3(void * arg)
{
	int pos;

	while(1)
	{
		/*Pristupanje deljivom resursu u moguce samo ako nit1 i nit2 nisu u 
		svojim KS.Zbog toga je potrebno zakljucati oba mutex*/
		pthread_mutex_lock(&mutex1);
		pthread_mutex_lock(&mutex2);

		/*Vrednost se upisuje u citac niz tj. pozicije 0-19;*/
		pos = rand() % 20;
		niz[pos] = rand() % 100;

		printf("Treca nit je na poziciju %d upisala vrednost %d\n", pos, niz[pos]);

		pthread_mutex_unlock(&mutex2);
		pthread_mutex_unlock(&mutex1);

		/*Pauziramo 8s*/
		sleep(8);
	}
}
int main()
{
	pthread_t n1, n2, n3;

	/*Kreiranje mutex-a*/
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);

	/*Kreiranej nit*/
	pthread_create(&n1, NULL, (void *)nit1, (void *)NULL);
	pthread_create(&n2, NULL, (void *)nit2, (void *)NULL);
	pthread_create(&n3, NULL, (void *)nit3, (void *)NULL);

	/*Ceka se da se niti n1, n2, n3 zavrse*/
	pthread_join(n1, NULL);
	pthread_join(n2, NULL);
	pthread_join(n3, NULL);

	/*Unistavaju se mutex-i*/
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
}
