// --- DATAVODI --- PIPE ---

///Kreiranje datavoda 
#include<unistd.h>
int pipe(int p[2]);

-Sistemski poziv koji kreira novi datavod i smešta par deskriptora koji ukazuju na krajeve datavoda u niz p:
        p[0] - kraj datavoda koji se koristi za čitanje
        p[1] - kraj datavoda koji se koristi za pisanje
-Funkcija vraća 0 u slučaju uspešnog izvršenja odnosno -1 ukoliko je došlo do greške.

//Zatvaranje datavoda
int close(int fd);

-Sistemski poziv koji zatvara deskriptor kojim se pristupa jednom od krajeva datavoda.
-Kada se u svim procesima zatvore svi deskriptori koji ukazuju na datavod datavod se automatski uništava.

//Citanje i pisanje iz datavoda 
ssize_t read(int fd,void* buff,size_t count);
ssize_t write(int fd,const void* buff,size_t count);

-Prvi argument predstavlja deskriptor odgovarajućeg kraja datavoda.
-Drugi argument predstavlja pokazivač na bafer iz koga se podaci upisuju u datavod ili u koji se podaci upisuju iz datavoda.
-Treći argument predstavlja veličinu bafera u bajtovima.
-Povratna vrednost funkcija predstavlja broj pročitanih bajtova odnosno broj upisanih bajtova u datavod.

spirntf() i atoi() , jedna pravi string , druga int iz stringa //valjda





// --- PREUSMERAVANJE U/I OPERACIJA ---

int dup(int oldfd);
int dup2(int oldfd,int newfd);

-Sistemski poziv dup nalazi najmanji slobodan deskriptor datoteke i postavlja ga da ukazuje na istu datoteku na koju ukazuje i deskriptor oldfd.
-Sistemski poziv dup2 zatvara deskriptor newfd, ukoliko je otvoren, i modifikuje ga takod a ukazuje na istu datoteku na koju ukazuje i deskriptor oldfd.
-Oba sistemska poziva u slučaju uspeha vraćaju kopiju deskriptora oldfd, a u slučaju greške vraćaju -1.





// --- IMENOVANI DATAVOD ---

int mkfifo(const char *pathname,mode_t mode);

-Imenovani datavodi se mogu koristiti za komunikaciju bilo koja dva proceasa u sistemu (ne postoji ograničenje vezano za srodstvo procesa).
-Imenovani datavodi su sastavni deo datotečnog sistema.
-Za rad sa imenovanim datavodima mogu se koristiti sve funkcije koje se koriste za rad sa standardnim datotekama.





// --- SIGNALI ---

-Po prijemu signala proces ga može obraditi na jedan od tri načina: 
        -primljeni signal se ignoriše
        -koristi se podrazumevana obrada signala
        -proces definiše funkciju za obradu signala

-Signal se detektuje prilikom prelaska iz kernel moda u user mod:
        po završetku sistemskog poziva
        context switching (promena aktivnog procesa)

//Slanje signala
#include <signal.h>
#include <sys/types.h>
int kill (pid_t pid, int sig);

-Sistemski poziv koji šalje signal specificiranom procesu ili grupi procesa.
-Prvi argument pid definiše procese kojima se signal šalje:
        -pid > 0 - signal se šalje procesu sa zadatim identifikatorom
        -pid == 0 - signal se šalje svim procesima koji pripadaju istoj grupi kao i proces koji šalje signal
        -pid < -1 - signal se šalje svim procesima koji pripadaju grupi -pid
        -pid == -1 - signal se šalje svim procesima kojima tekući proces može da pošalje signal isključujući njega samog i proces init(1)
-Drugi argument sig definiše signal koji se šalje:
        -SIGHUP - prekinuta komunikacija terminalom
        -SIGINT - procesu se šalje signal Ctrl + C
        -SIGQUIT - procesu se šalje signal Ctrl + \
        -SIGKILL - signal koji prekida proces i koji se ne može blokirati
        -SIGBUS/SIGSEGV - greška na magistrali odnosno greška pri segmentaciji
        -SIGPIPE - write opoeracija nad datavodom iz koga nijedan proces ne čita podatke
        -SIGALRM - signal alarma
        -SIGTERM - signal za terminaciju procesa
        -SIGSTOP - signal koji suspenduje izvršavanje procesa
        -SIGTSTP - izvršavanje procesa u pozadini (Ctrl + Z)
        -SIGCONT - proces nastavlja izvršavanje nakon suspendovanja
        -SIGCHLD - proces dete je završilo sa izvršavanjem
        -SIGUSR1/SIGUSR2 - korisnički definisani signali

//Obrada signala
#include <signal.h>
#include <sys/types.h>
void (*signal(int signum, void(*handler)(int)))(int);

-Sistemski poziv koji definiše kako će proces obrađivati određeni signal.
-Prvi argument signum predstavlja identifikator signala za koji se definiše način obrade.
-Drugi argument handler definiše način obrade:
        -SIG_DFL - podrazumevana obrada signala
        -SIG_IGN - signal se ignoriše
        -pokazivač na funkciju koja se poziva po pristizanju signala
-Sistemski poziv vraća pokazivač na funkciju koja je prethodno bila zadužena za obradu signala u slučaju uspeha odnosno SIG_ERR u slučaju greške.

int pause();

-Sistemski poziv koji suspenduje izvršavanje procesa sve do prijema nekog signala (bez obzira da li se po prijemu signala poziva neka funkcija za obradu signala ili se
proces prekida).
-Ukoliko se signal ignoriše neće se nastaviti izvršavanje procesa.
-Funkcija uvek vraća -1.

int alarm(unsigned int seconds);

-Sistemski poziv koji tekućem procesu šalje signal SIGALRM posle specificiranog broja sekundi.
-Podrazumevana obrada za signal SIGALRM je prekid izvršavanja procesa.





// --- REDOVI PORUKA ---

//Kreiranje reda poruka
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
int msgget(key_t key, int msgflg);

-Sistemski poziv koji kreira novi red poruka.
-Prvi argument key predstavlja jedinstveni identifikator reda poruka na nivou čitavog sistema. Mora biti poznat svim procesima koji žele da koriste određeni red poruka
-Vrednost drugog argumenta msgflg se definiše kao rezultat OR operacije nad različitim vrednostima i određuje :
        prava pristupa redu poruka (koristićemo vrednost 0666 koja svim korisnicima dodeljuje sve privilegije nad red poruka)
        -mod kreiranja reda poruka. Najčešća vrednost je: IPC_CREAT - sistemski poziv kreira red poruka ukoliko on već ne postoji u sistemu.
-Sistemski poziv vraća celobrojni identifikator (referencu) reda poruka a u slučaju greške vraća (-1). Dobijeni identifikator (referenca) je važeći samo kod procesa koji je izvršio sistemski poziv i kod njegove dece.
-Ukoliko u sistemu ne postoji red poruka sa zadatim identifikatorom a specificiran je flag IPC_CREAT kreira se novi red poruka.
-Ukoliko u sistemu već postoji red poruka sa zadatim identifikatorom ne kreira se novi semafor već se samo vraća referenca na postojeći red poruka.

//Slanje i primanje poruka
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
int msgsnd(int msgid, int msgbuf * msgp, size_t msgsz, int msgflg);
int msgrcv(int msgid, int msgbuf * msgp, size_t msgsz, int msgtyp, int msgflg);

-Prvi argument msgid predstavlja identifikator (referencu) reda poruka koji je dobijen pozivom funkcije msgget.
-Drugi argument msgp predstavlja pokazivač na bafer koji sadrži poruku koja se šalje ili u koji će biti smeštena poruka koja se prima.
-Treći argument msgsz predstavlja veličinu bafera poruke u bajtovima.

-Argument msgflg definiše mod slanja/prijema poruke a vrednost 0 označava prihvatanje podrazumevanog moda rada.
-Argument msgtyp kod funkcije za prijem je nenegativan ceo broj koji definiše tipove poruka koje se čitaju iz reda:
-msgtyp == 0 - čitaju se sve poruke bez obzira na tip
-msgtyp > 0 - čitaju se samo poruke specificiranog tipa
-Čitanjem se poruka uklanja iz reda poruka.

struct msgbuf {
long mtype;
/* tip poruke, mora biti > 0 */
char mtext[1]; /* tekst poruke */
};

//Kontrola reda poruka
int msgctl (int msqid, int cmd, struct msgid_ds buf);

-Prvi argument msgmid predstavlja identifikator (referencu) reda poruka koji je dobijen pozivom funkcije msget.
-Drugi argument cmd definiše operaciju koju treba izvršiti nad semaforom. Za brisanje reda poruka se koristi operacija IPC_RMID.