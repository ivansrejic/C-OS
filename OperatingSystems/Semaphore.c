S - semaforska promenljiva // Semafor se ponasa kao celobrojna promenljiva
Nad semaforom se vrse 2 operacije - P i V

P(S): if S > 0
      then S = S-1
      else Blokirati proces na semaforu S 

V(S): if Postoji proces koji ceka na semaforu S
      then Aktiviraj proces iz liste cekanja
      else S = S+1





// --- MUTEX ---
-Mutex predstavlja implementaciju binarnog semafora
-Korisi se za medjusobno iskljucivanje thread-ova prilikom pristupanja deljivom resursu
-pthread_mutex_t tip promenljive

#include<pthread.h>
//Kreiranje mutexa
int pthread_mutex_init(pthread_mutex_t* mutex,pthread_mutexattr_t *attr);
-Prvi argument je pokazivac na promenljivu tipa mutex, koja je prethodno deklarisana
-Drugi argument definise atribute mutex-a koji se kreira. NULL obezbedjuje default vrednosti.

//Brisanje mutexa
int pthread_mutex_destroy(pthread_mutex_t* mutex);

//Zakljucavanje mutexa
int pthread_mutex_lock(pthread_mutex_t* mutex);
-Thread koja zakljuca mutex, postaje njegov vlasnik i samo ga ona moze otkljucati.
-U jednom trenutku samo jedan thread moze biti vlasnik mutexa 

//Otkljucavanje mutexa
int pthread_mutex_unlock(pthread_mutex_t* mutex);
-Vraca gresku ako mutex nije zakljucan ili je neki drugi thread vlasnik





//--- USLOVNA PROMENLJIVA ---

tip promenljive pthread_cond_t;

//Kreiranje uslovne promenljive
int pthread_cond_init(pthread_cond_t* condition,pthread_attr_t* attr);
-Priv argument je uslovna promenljiva koja je prethodno deklarisana
-Drugi argument definise atribute. NULL obezbedjuje default vrednosti za atribut.

//Brisanje uslovne promenljive
int pthread_cond_destroy(pthread_cond_t* condition);

//Blokiranje niti
int pthread_cond_wait(pthread_cond_t* condition, pthread_mutex_t* mutex);
-Blokira izvrsavanje niti na odredjenoj uslovnoj premonljivoj
-Nit se blokira na uslovnoj promenljivoj sve dok druga nit ne signalizira da je uslov koji se ceka ispunjen
-Funkcija se poziva samo ako je mutex zakljucan 
-Mutex se automatski otklucava tokom cekanja niti

//Signalizacija uslovne promenljive
int pthread_cond_signal(pthread_cond_t* condition);
int pthread_cond_broadcast(pthread_cond_t* condition);
-Sistemski poziv signalizira(budi)nit koja ceka na uslovnoj promenljivoj
-Funkcija se poziva u okviru kriticne sekcije, mutex mora biti zakljucan
-Ukoliko vise niti ceka na uslovnu promenljivu, koristi se broadcast





// --- POSIX SEMAFORI ---
-POSIX semafori predstavljaju implementaciju semafora opsteg tipa.
-Mogu biti binarni i n-arni
-POSIX semafori nemaju vlasnika 
-Semafor se definise kao promenljiva tipa sem_t
-Sve neophodne funkcije u 
#include<semaphore.h>

//Kreiranje semafora
int sem_init(sem_t* sem, int pshared, unsigned int value);
-Prvi argument je pokazivac na promenljivu tipa POSIX semafor koja je prethodno deklarisana
-Drugi argument je uvek 0 (Zato sto semafore koristimo samo za sinhronizaciju niti)
-Treci argument predstavlja vrednost na koju se kreirani semafor inicijalizuje

//Brisanje semafora
int sem_destroy(sem_t* sem);

//P i V funkcija semofora
int sem_wait(sem_t* sem);
int sem_post(sem_t* sem); // OVO je V, inkrementira vrednost semafora

//Imas definisano gore sta su P i V
