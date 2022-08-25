

/*Program koji na standardnom izlazu ispisuje recenicu "Ovo je test za niti!"
 *pri cemu svaku rec ispisuje posebna nit*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N 5
char reci[N][20] = {"Ovo", "je", "test", "za", "niti!"};
struct argument
{
  int rec;
  pthread_t prethodna_nit;
};
void * stampanje(void * arg)
{
  struct argument * p = (struct argument *)arg;
  if (p->rec > 0)
    pthread_join(p->prethodna_nit, NULL);
  printf(" %s", reci[p->rec]);
  fflush(stdout);
  sleep(3);
}
int main()
{
  int i;
  /*Niz ulaznih argumenata niti. Po jedan za svaku nit.*/
  struct argument args[N];
  /*Niz identifikatora niti. Po jedan za svaku rec*/
  pthread_t niti[N];
  /*Kreiramo niti */
  for (i = 0; i < N; i++)
  {
    args[i].rec = i;
    if (i > 0)
      args[i].prethodna_nit = niti[i - 1];
    pthread_create(&niti[i], NULL, (void *)stampanje, (void *)&args[i]);
  }
  /*Main f-ja ceka da se poslednja nit zavrsi*/
  pthread_join(niti[N-1], NULL);
  return 0;
}
  
