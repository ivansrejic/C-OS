Nije moguće pristupiti svakoj memorijskoj lokaciji. Pokušaj čitanja memorijske lokacije sa adresom 0 bi doveo do greške (segmentation violation).
Postoje četiri segmenta memorije kojima je dozvoljen pristup:
    1. Tekst (kod) segment - segment u kome se nalaze instrukcije programa.
    2. Globalni podaci - segment u kome se nalaze globalne promenjive koje definiše program.
    3. Heap - memorijske lokacije za dinamički kreirane promenljive koje vraća malloc naredba.
    4. Magacin - segment u kome se nalaze lokalne promenjive, argumenti poziva funkcija i povratne vrednosti funkcija.

///Dinamicko zauzimanje i oslobadjanje memorije

#include <stdlib.h>
char * malloc (unsigned int size);
void free (char * ptr);

-Sistemski poziv malloc() zauzima memoriju koja je dovoljna da se u nju smesti objekat čija je veličina size bajtova.
-U slučaju uspeha sistemski poziv vraća pokazivač na početak zauzete memorije a
-U slučaju greške vraća NULL.
-Zauzeta memorija koja više nije neophodna oslobađa se sistemskim pozivom free().
-Postoje i brže verzije ovih funkcija i one su deklarisane u zaglavlju <malloc.h>.
-Da bi se ove funkcije koristile program se prevodi sa: gcc -lmalloc.

char * calloc (unsigned int elem, unsigned int elsize);
char * realloc (char * ptr, unsigned int size);

Sistemski poziv calloc() rezerviše memoriju za niz elemenata čija je dimenzija specificirana.
Sistemski poziv realloc() menja veličinu prethodno rezervisanog segmenta memorije.

//Analiza i izmena sadržaja memorijskih lokacija

void *memcpy(void *dest, const void *src, size_t n);
void *memccpy(void *dest, const void *src, int c, size_t n);
void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);





// --- DELJENA MEMORIJA ---

//Kreiranje deljene memorije
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
int shmget(key_t key, int size, int flg);

-Prvi argument key predstavlja jedinstveni identifikator segmenta deljene memorije na nivou čitavog sistema. Mora biti poznat svim procesima koji žele da koriste određeni segment deljene memorije.
-Vrednost drugog argumenta size definiše veličinu segmenta deljene memorije koji se kreira.
-Vrednost trećeg argumenta flag se definiše kao rezultat OR operacije nad različitim vrednostima i određuje :
    -prava pristupa segmentu deljene memorije (koristićemo vrednost 0666 koja svim korisnicima dodeljuje sve privilegije nad deljenom memorijom)
    -mod kreiranja segmenta deljene memorije. Najčešća vrednost je:
        IPC_CREAT – sistemski poziv kreira segment deljene memorije ukoliko on već ne postoji u sistemu.

-Sistemski poziv vraća celobrojni identifikator (referencu) segmenta deljene memorije a u slučaju greške vraća (-1). Dobijeni identifikator (referenca) je važeći samo kod procesa koji je izvršio sistemski poziv i kod njegove dece.
-Ukoliko u sistemu ne postoji segment deljene memorije sa zadatim identifikatorom a specificiran je flag IPC_CREAT kreira se novi segment deljene memorije.
-Ukoliko u sistemu već postoji segment deljene memorije sa zadatim identifikatorom ne kreira se novi segment već se samo vraća referenca na postojeći segment deljene memorije.

//Mapiranje segmenta deljene memorije

void * shmat(int shm_id, char * ptr, int flag);

-Sistemski poziv mapira segment deljene memorije u adresni prostor procesa.
-Prvi argument shm_id predstavlja identifikator (referencu) segmenta deljene memorije koji je dobijen pozivom funkcije shmget.
-Drugi argument ptr u našem slučaju uvek ima vrednost NULL.
-Treći atgument definiše način korišćenja segmenta deljene memorije:
    SHM_RDONLY - deljenu memoriju je moguće samo čitati
    0 - moguća je i i zmena sadržaja deljene memorijeu bajtovima.
-U slučaju uspeha sistemski poziv vrača pokazivač na početak adresnog prostora u koji je mapirana deljena memorija. U slučaju greške sistemski poziv vraća NULL.

//Uklanjanje segmenta deljene memorije

void * shmdt(const void * shmaddr);

-Sistemski poziv uklanja segment deljene memorije iz adresnog prostora procesa.
-Prvi argument shmaddr predstavlja pokazivač na početak adresnog prostora u koji je mapiran segment deljene memorije (adresa koju vraća funkcija shmat).

//Kontrola reda poruka

int shmctl (int shmid, int cmd, struct shmid_ds buf);

-Prvi argument shmid predstavlja identifikator (referencu) segmenta deljene memorije koji je dobijen pozivom funkcije shmget.
-Drugi argument cmd definiše operaciju koju treba izvršiti nad segmentom deljene memorije. Za brisanje deljene memorije se koristi operacija IPC_RMID.