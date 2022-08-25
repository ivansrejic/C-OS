#include <pthread.h>

//prilikom prevodjenja programa, neophodno je linkeru dodati opciju -lpthread
//command line za prevodjenje 
gcc threads.c -o threads -lpthreads

// --- Kreiranje niti (thread-a) ---
int pthread_create(pthread_t *threadhandle,pthread_attr_t *attribute, void* (*start_routine)(void*),void* arg);
Argumenti:
    -handle novokreirane niti ukoliko se funkcija uspesno izvrsi
    -argumenti za kreiranje niti(mogu imati NULL vrednost)
    -pointer na funkciju koja sadrzi programski kod koji ce niti izvrsavati // Funkcija mora da vraca void* i da ima jedan ulazni argument koji je void*
    -pointer na ulazni argument niti //Npr ako imamo sortiranje kao funkciju odnosno start_routine, ovde dajemo arg za tu funkciju

// --- Cekanje niti ---
int pthread_join (pthread_t threadhandle,void** returnValue); // (&nit , NULL ) Uglavnom
Nit koja je pozvala funkciju pthread_join se zaustavlja i ceka da se zavrsi nit koja je zavrsena svojim handle-om

