#include<stdlib.h>

//malloc 
void* malloc(size_t size)// memory allocation -> Dinamicka rezervacija prostora zeljene velicine

int *p;
p = (int*)malloc(4);

//calloc
void* calloc(size_t num,size_t size) // isto kao malloc , sa tim da je dinamicki rezervisana memorija num * size , primer dole

int* p;
iny N;
p = (int*)calloc(N,sizeof(int)); // N bloka po sizeof(int) (4 bytes), npr za niz od N elemenata rezervisemo odredjenu memoriju
// isti rezultat se moze dobiti i { malloc(N*sizeof(int));}

//realloc
void realloc(void* p,size_t newSize) // Menja velicinu alociranog memorijskog prostora na koju ukazuje pokazivac naveden kao parametar

//free
void free(void* p) // Memorijski blok prethodno alociran sa malloc,calloc ili realloc se oslobadja



