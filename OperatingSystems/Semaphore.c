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





// --- System V SEMAFORI ---
-IPC System V semaphore se koristi za sinhronizaciju PROCESS-A !!! Ovi ostali semafori se koriste za threadove(niti)
-Objekti koji se koriste za sinhorinizaciju procesa se obicno kreiraju u jezgru OS i postoje nezavisno od procesa u kojima se koriste 
-Ne predstavlja samo jednu celobrojnu vrednost vec predstavlja niz celobrojnih vrednosti.
-Kreiranje semafora i njegova inicijalizacija su dva odvojena procesa.
#include<sys/sem.h>

//Kreiranje semafora
int semget(key_t key,int nsems,int flag);
-Key je jedinstveni identifikator
-nsems specificira broj celobrojnih vrednosti koje semafor sadrzi 
-flag se definise kao rezultat OR operacije nad razlicitim vrednostima i odredjuje:
    - pravo pristupa semaforu (0666 - svi imaju pristup)
    - mod kreiranja semafora :
            -> IPC_CREAT - kreira semafor ako on ne postoji vec 
            -> IPC_EXCL - koristi se u kombinaciji sa IPC_CREAT i zahteva da semafor sa zadatim
                identifikatorom ne postoji u sistemu.
-Sistemski poziv vraća celobrojni identifikator (referencu) semafora a u slučaju greške vraća (-1).
-Ukoliko u sistemu ne postoji semafor sa zadatim identifikatorom a specificiran je flag IPC_CREAT kreira se novi System V semafor.
-Ukoliko u sistemu već postoji semafor sa zadatim identifikatorom (a nije specificiran flag IPC_CREAT | IPC_EXCL) ne kreira se novi semafor već se samo vraća referenca na postojeći System V semafor.

//Operacije nad semaforom
int semop(int semid,struct sembuf* semops,int nsops);
-Prvi argument semid predstavlja identifikator (referencu) System V semafora koji je dobijen pozivom funkcije semget.
-Drugi argument semops predstavlja niz operacija koje treba izvršiti nad celobrojnim vrednostima System V semafora. Svaka operacija je zadata kao sembuf
struktura.
-Treći argument nsops predstavlja broj elemenata niza sa operacijama.

-Struktura sembuf je deklarisana u zaglavlju <sys/sem.h> i ima sledeći izgled:
struct sembuf
    {
        ushort sem_num;
        short sem_op;
        short sem_flg;
    };
-Polje sem_num specificira indeks celobrojne vrednosti na koju se operacija odnosi.
-Polje sem_op definiše operaciju koja se obavlja. Moguće vrednosti su:
        > 0 - pozitivne vrednosti se dodaju odgovarajućoj celobrojnoj vrednosti semafora odnosno
        ekvivalent je V operacija
        < 0 - negativne vrednosti se oduzimaju od odgovarajuće celobrojne vrednosti semafora
        odnosno ekvivalent je P operacija. Nijedna celobrojna vrednost ne može biti negativna.
        0 - proces koji je izvršio sistemski poziv se blokira dok odgovarajuća celobrojna vrednost ne
        dobije vrednost 0.
-Polje sem_flag definiše način na koji se operacija obavlja. Najčešće ima vrednost NULL (kada se prihvata podrazumevani način izvršavanja operacije). Vrednost IPC_NOWAIT sprečava blokiranje procesa koji je izvršio sistemski poziv.
-Sistemski poziv vraća 0 ukoliko su sve operacije uspešno izvršene odnosno -1 ako je došlo do greške prilikom izvršavanja neke od operacija.

//Kontrola semafora
int semctl (int semid, int semnum, int cmd, union semun arg);
-Prvi argument semid predstavlja identifikator (referencu) System V semafora koji je dobijen pozivom funkcije semget.
-Drugi argument semnum predstavlja indeks celobrojne vrednosti na koju se operacija odnosi.
-Treći argument cmd definiše operaciju koju treba izvršiti nad semaforom. predstavlja broj elemenata niza sa operacijama.
-Četvrti argument arg omogućava definisanje parametara neophodnih za operaciju i definiše se kao unija semun.

-Unija semun je deklarisana u zaglavlju <sys/sem.h> i ima sledeći izgled:
union semun
    {
        int val;
        struct semid_ds *buf;
        ushort *array;
        struct seminfo * __buf;
        void * __pad;
    };
-Polje val se koristi za zadavanje vrednosti prilikom inicijalizacije celobrojne vrednosti semafora.
-Neke od mogućih operacija koje se mogu izvršiti nad System V semaforom:
        -SETVAL - definiše vrednost odgovarajuće celobrojne vrednosti System V semafora
        -IPC_RMID - brisanje System V semafora iz sistema.
