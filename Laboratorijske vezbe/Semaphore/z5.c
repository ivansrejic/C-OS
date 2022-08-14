/*Pristup bazi podataka obavlja se radi upisa i čitanja od strane više procesa. U jednom trenutku može
postojati više procesa koji čitaju sadržaj iz baze podataka procedurom read_database(), ali ako jedan
proces upisuje sadržaj u bazu podataka procedurom write_database(), nijednom drugom procesu nije
dozvoljen pristup bazi podataka radi upisa i čitanja. Prednost imaju procesi koji čitaju sadržaj, tako da
dok god ima procesa koji čitaju iz baze podataka, proces koji treba da upisuje podatke mora da čeka.
Korišćenjem programskog jezika C napisati Linux program koji korišćenjem procesa i poznatih IPC
mehanizama simulira prethodno opisani algoritam. (Sinhronizacion problem Čitaoci – pisci).*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int A = 0; /*Globalna promenljiva koja prestavlja bazu podataka*/
int N = 0; /*Globalna promenljiva koja predstavlja brojac citaoca koji u datom trenutku koriste bazu podataka*/

sem_t mutex_DB, mutex_N; /*Semafori za medjusobno iskljucenje*/

void read_database(int i)
{
	/*Operacija citanja iz baze se simulira stampanjem globalne promenljive A*/
	printf("Nit %d je procitala vrednost %d\n", i, A);
	sleep(rand()%3);
}

void write_database()
{
	/*Operacija upisa u bazu se simulira izmenom vrednosti globalne promenljive
	A*/
	printf("Pisac menja vrednost u bazi podataka.\n");
	A = A + rand()%10;
	sleep(rand()%5);
}

void * pisac(void * arg)
{
while(1)
{
/*Pristup bazi je smesten u KS*/
sem_wait(&mutex_DB);
write_database();
sem_post(&mutex_DB);
/*Pravi pauzu pre sledeceg pristupa bazi podataka*/
sleep(rand() % 10);
}
}
void * citalac(void * arg)
{
	int i;
	i = *((int *)arg);
	while(1)
	{
		/*Promenljivoj N se pristupa u KS*/
		sem_wait(&mutex_N);

		/*Povecava se broj citalaca*/
		N++;
		/*Prvi citalac zakljucava bazu podataka kako bi sprecio pisca da joj pristupa*/
		if (N == 1)
			sem_wait(&mutex_DB);

		sem_post(&mutex_N);

		read_database(i);

		/*Promenljivoj N se pristupa u KS*/
		sem_wait(&mutex_N);

		/*Smanjuje se broj citalaca*/
		N--;

		/*Poslednji citalac otkljucava bazu podataka*/
		if (N==0)
			sem_post(&mutex_DB);

		sem_post(&mutex_N);

		/*Pravi pauzu pre sledeceg pristupa bazi podataka */
		sleep(rand() % 7);
	}
}

int main()
{
	int i;
	int red_br[4];

	/*Identifikatori nit, 4 citaoca + 1 pisac*/
	pthread_t niti[5];
	srand(3232234);

	/*Kreiranje i inicijalizacija semafora*/
	sem_init(&mutex_N, 0, 1);
	sem_init(&mutex_DB, 0, 1);

	/*Kreiranje citalaca i pisca*/
	for (i = 0; i < 4; i++)
	{ 
		red_br[i] = i;
		pthread_create(&niti[i], NULL, (void *)citalac, (void *)&red_br[i]);
	}

	pthread_create(&niti[4], NULL, (void *)pisac, (void *)NULL);

	/*Ceka se da se niti zavrse*/
	for(i = 0; i < 5; i++)
		pthread_join(niti[i], NULL);

	/*Brisanje semafora*/
	sem_destroy(&mutex_N);
	sem_destroy(&mutex_DB);
}