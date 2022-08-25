// --- Funkcije za rad sa datotekama --- 

//Otvaranje datoteke

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open (char * filename, int flags [, mode_t mode]);

-Sistemski poziv open() se koristi za otvaranje postojeće datoteke za čitanje ili pisanje odnosno za kreiranje nove datoteke.
-Prvi argument funkcije filename je znakovni niz koji sadrži puno ime datoteke zadato kao apsolutna ili relativna putanja.
-Drugi argument flags se dobija kao razultat OR operacije nad sledećim konstantama:
    O_RDONLY – datoteka se otvara samo za čitanje.
    O_WRONLY – datoteka se otvara samo za upis.
    O_RDWR – datoteka se otvara za upis i za čitanje.
    O_APPEND – pozicionira pokazivač datoteke na kraj. Datoteka je spremna za upis na kraj.
    O_CREAT – ukoliko datoteka sa zadatim imenom ne postoji, kreira se nova.
    O_TRUNC – ukoliko datoteka sa zadatim imenom postoji njen sadržaj se briše (datoteka postaje dužine nula)
-Treći argument mode je opcioni i koristi se prilikom kreiranja nove datoteke za definisanje privilegija. Ukoliko se izostavi koriste se podrazumevane privilegije koje zavise od toga koji je korisnik pokrenuo proces.
-U slučaju uspeha sistemski poziv vraća pozitivnu celobrojnu vrednost koja predstavlja deskriptor datoteke a u slučaju greške vraća -1.
-Svakoj otvorenoj datoteci u sistemu je pridružen deskriptor datoteke.

//Zatvaranje datoteke

int * close (int fd);

-Sistemski poziv close zatvara datoteku koja je prethodno otvorena korišćenjem sistemskog poziva open.
-Arguemnt fd predstavlja deskriptor datoteke koja se zatvara.
-Po izlasku iz programa sistem automatski zatvara sve otvorene datoteke.

//Čitanje i pisanje iz datavoda

#include <unistd.h>
ssize_t read(int fd, void * buff, size_t count);
ssize_t write(int fd, void * buff, size_t count); // Iz PIPE CITA I UPISUJE

//Pozicioniranje pokazivača datoteke

off_t lseek(int fd, off_t offset, int mode);

-Sistemski pozivi koji se koriste za pozicioniranje pokazivača datoteke na proizvoljnu poziciju u datoteci.
-Prvi argument fd predstavlja deskriptor odgovarajuće datoteke.
-Drugi argument offset definiše novu poziciju unutar datoteke a tumači se na osnovu vrednosti trećeg argumenta.
-Treći argument mode definiše kako se određuje nova pozicija:
    SEEK_SET – offset je definisan u odnosu na početak datoteke.
    SEEK_CUR – offset je definisan u odnosu na trenutnu poziciju pokazivača datoteke.
    SEEK_END – offset je definisan u odnosu na kraj datoteke.
-Povratna vrednost funkcija predstavlja novu poziciju u datoteci U slučaju greške funkcija vraća -1.

//Informacije o datoteci

int stat(char * name, struct stat * buff);

-Sistemski pozivi omogućava pribavljanje informacija o nekoj datoteci.
-Prvi argument name predstavlja ime datoteke koje je zadato kao apsolutna ili relativna putanja.
-Drugi argument buffer predstavlja pokazivač na strukturu koja će prihvatiti informacije o datoteci.

//Struktura stat

#include <sys/stat.h>
struct stat 
{
    dev_t   st_dev; /* broj uređaja */
    ino_t   st_ino; /* broj inode strukture */
    mode_t  st_mode; /* dozvole pristupa datoteci */
    nlink_t st_nlink; /* broj linkova ka ovoj datoteci */
    uid_t   st_uid; /* identifikacija korisnika */
    gid_t   st_gid; /* identifikacija grupe */
    dev_t   st_rdev; /* tip uređaja */
    off_t   st_size; /* veličina datoteke u bajtovima*/
    blksize_t   st_blksize; /* veličina blokova za U/I datotečnog sistema */
    blkcnt_t    st_blocks; /* broj dodeljenih blokova */
    time_t  st_atime; /* vreme poslednjeg pristupa datoteci */
    time_t  st_mtime; /* vreme poslednje modifikacije datoteke */
    time_t  st_ctime; /* vreme poslednje promene statusa */
};

//Makroi za određivanje tipa datoteke
-Makro naredbe koje za argument uzimaju atribut st_mode iz strukture stat a vraćaju TRUE ili FALSE u zavisnosti od tipa datoteke:
    S_ISDIR - direktorijum
    S_ISREG - regularna datoteka
    S_ISCHR - znakovna specijalna datoteka
    S_ISBLK - blok specijalna datoteka
    S_ISFIFO - imenovani datavod (pipe) ili FIFO
    S_ISLNK - link
    S_ISSOCK - socket





    // --- FUNKCIJE ZA RAD SA DIREKTORIJUMIMA

    //Otvaranje direktorijuma

#include <dirent.h>
DIR * opendir(const char * pathname);

-Sistemski pozivi omogućava otvara postojeći direktorijum.
-Prvi argument pathname predstavlja ime direktorijuma koje je zadato kao apsolutna ili relativna putanja.
-U slučaju greške sistemski poziv vraća NULL.
-U slučaju uspeha sistemski poziv vraća pokazivač na DIR strukturu. Ova struktura se koristi u svim sistemskim poziivma za rad sa direktorijumima kada je potrebno identifikovati otvoreni direktorijum.

//Čitanje sadržaja direktorijuma

struct dirent * readdir(DIR * dp);

-Sistemski pozivi omogućava čitanje sadržaja otvorenog direktorijuma.
-Prvi argument dp predstavlja pokazivač na otvoreni direktorijum.
-U slučaju uspeha sistemski poziv vraća pokazivač na dirent strukturu koja sadrži informacije o stavki direktorijuma.
-Pokazivač dp se automatski inkrementira da pokazuje na sledeću stavku u direktorijumu. Kako bi obradili sve stavke u nekom direktorijumu treba sukcesivno
pozivati funkciju readdir dok funkcija ne vrati NULL vrednost. Funkcija vraća NULL vrednost kada pokazivač dp dodje do kraja direktorijuma.

struct dirent 
{
    ino_t d_ino;
    char d_name[NAME_MAX+1]; /* ime stavke koja se nalazi u direktorijumu,
može biti poddirektorijum, datoteka ili veza
(link) */
}

//Resetovanje direktorijuma

void rewinddir(DIR * dp);

//Zatvaranje direktorijuma

void close(DIR * dp);

//Kreiranje direktorijuma

#include <sys/stat.h>
int mkddir(const chat * pathname, mode_t mode);

//Brisanje direktorijuma

#include <sys/stat.h>
int rmdir(const chat * pathname);


