/*Program koji sortira vrste celobroje matrice pri cemu se za sortiranje svake
 *vrste pokrece posebna nit*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 4
int a[N][N];
/*Funkcija niti*/
void * sortiranje(void * arg)
{
  int k = *((int *)arg);
  int i, j, pom;
  /*Sortiranje matrice */
  printf("Sortiram vrstu:%d\n", k);
  for (i = 0; i < N - 1; i++)
    for(j = i + 1; j < N; j++)
      if (a[k][i] > a[k][j])
      {
      	pom = a[k][i];
      	a[k][i] = a[k][j];
      	a[k][j] = pom;
      }
}
int main()
{
  int i, j;
  int rowIdices[] = {0,1,2,3};
  /*Niz identifikatora niti. Po jedan za svaku vrstu*/
  pthread_t niti[N];
  /*Sa standardnog ulaza citamo elemente matrice*/
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      scanf("%d", &a[i][j]);
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
      printf("%d\t", a[i][j]);
    printf("\n");
  }
  printf("\n");
  /*Kreiramo niti */
  for (i = 0; i < N; i++)
    pthread_create(&niti[i], NULL, (void *)sortiranje, (void *)&rowIdices[i] );
  /*Main f-ja ceka da se niti zavrse*/
  for (i = 0; i < N; i++)
    pthread_join(niti[i], NULL);
  /*Na standardni izlaz stampamo sortiranu matricu*/
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
      printf("%d\t", a[i][j]);
    printf("\n");
  }
  return 0;
}
