#include <sys/types.h>
#include <unistd.h>

// --- Kreiranje novog procesa ---
pid_t fork();
// Kreira novi proces na osnovu postojeceg procesa
Nakon kreiranja, child process je identican parent process-u osim u:
    PID != PPID (ProcessID i ParentProcessID)
    Razlicit je adresni prostor
    Child process sadrzi kopije svih resursa koje je proces roditelj koristio

U slucaju uspeha.
    return value = PID u parent processu
    return value = 0 u child processu
    if value == -1 -> error
// Ovako proveravamo da li kod izvrsava parent process ili child process

// --- PID tekuceg process-a ---
pid_t getpid();

// --- PID parent process-a ---
pid_t getppid();

// --- Susprendovanje izvrsavanja process-a ---
unsigned int sleep(unsigned int seconds);
//Process se suspenduje na odredjeno vreme, nakon toga nastavlja svoje izvrsenje od sledece linije koda

// --- Zavrsetak process-a ---
void exit(int status);
// 

// --- Status process-a ---
pid_t wait(int* status-ptr);
pid_t waitpid(pid_t pid,int* status-ptr);
//Process koji je pozvao funkciju se zaustavlja dok se ne zavrsi child process
Wait -> Zaustavlja process dok se ne zavrsi bilo koji child process
WaitPID -> Zaustavlja process dok se ne zavrsi child process ciji je PID specificiran

// --- Izvrsavanje programa ---
int execl(const char *path, const char *arg, ...); // Ocekuje listu argumenata koja se zavrsava sa NULL (string npr i to, sve se zavrsava sa /0 (NULL)) { Ako prosledjujemo argumente npr, na kraju moramo da imamo NULL}
int execv(const char *path, char *const argv[]); // Ocekuje niz argumenata, prvi argument odgovara argv[0] i mora da bude ime programa koji se poziva
int execlp(const char *file, const char *arg, ...); // Omogucava pretrazivanje izvrsnih datoteka u PATH putanji (ako ne sadrzi '/' , Ponasa se kao i execl)
int execvp(const char *file, char *const argv[]); // Omogucava pretrazivanje izvrsnih datoteka u PATH putanji (ako ne sadrzi '/' , Ponasa se kao i execv)
int execle(const char *path, const char * arg, ..., char *const envp[]); // omogucavaju specificiranje vrednosti environment promenljivih (ova i execve)
int execve(const char *filename, char *const argv[], char *const envp[]);
//U slucaju uspeha, funkcija se NE vraca u process koji ju je pozvao vec zapocinje izvrsavanje novog programa
//U slucaju greske vraca -1 !!!