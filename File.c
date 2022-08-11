#include<stdio.h>

EOF = identifikator kraja fajla

// otvaranje file-a
FILE* fopen(char* imeFajla,char* mod); //imeFajla - putanja do fajla , mod - nacin i svrha otvaranja fajla

//mod
r - read // File mora da postoji, inace vraca error
w - write // Ako file ne postoji, kreira se novi. Ukoliko postoji, brise se sav prethodni sadrzaj
a - append // Dodavanje. Ako file ne postoji, kreira se novi. Ukoliko postoji, prethodni sadrzaj se NE brise, vec se dodaje
r+ , w+ , a+ // i za citanje i za upis. Vaze ista pravila kao i za r,w,a

return value = 0 ako file nije otvoren // moze biti i null. Moze vratiti null ako je file otvoren za upis, a nema dovoljno memorije na disku

FILE* f;
if(f != NULL)
{
    //uradi nesto
}
else
{

}

//efektivnije resenje za proveru uspesnosti otvaranja file-a
if(!(f = fopen("fileLocation","r"))) // vraca 0 ako nije otvoren
{
    printf("File nije pronadjen");
}

// zatvaranje file-a
int fclose(FILE* stream);
return value = 0 ako je file uspesno zatvoren;


// TEKSTUALNI FILE-OVI

// upisivanje u text file

//fprintf
int fprintf(FILE* file,char* format) // format - Literal koji se upisuje u file
return value = broj karaktera koji je upisan u file // ako je uspesno proslo upisivanje
return value < 0 // ako nije uspesno

//fputs
int fputs(char* string,FILE* file) // upisuje string u file. fprintf upisuje bilo koji literal, fputs upisuje string.
return value > 0 // ako je uspesno
return value < 0 // ako nije uspesno

//fputc
int fputc(char c,FILE* file) // upisuje karakter u file

//fscanf
int fscanf(FILE* file,const char* format) //Citanje podataka iz file-a ciji je format zapisa unapred poznat
return value = broj uspesno ucitanih parametara
return value = 0 // nijedan podatak nije ucitan

//fgets
char* fgets(char* string, int n, FILE* tok) // Citanje iz text file-a ciji format nije unapred poznat
return value = pointer na string;
return value = NULL // nijedan podatak nije ucitan

//fgetc
int fgetc(FILE* tok) // Cita jedan karakter

//feof
file end of file

int feof(FILE* tok) //
return value = 0 // sve dok ima sta da se cita iz fajla
while(!feof(file))
{
    //radi nesto
}


// BINARNI FILE-OVI

Isto se otvara, samo sto se u MOD , dodaje slovo b (rb, wb, ab, rb+, wb+, ab+);

// fread
size_t fread(void* odrediste, size_t n, size_t broj, FILE* file); // citanje iz binarnog file-a
odrediste - Pokazivac na pocetak niza podataka u memoriji gde ce ucitani podaci biti smesteni. // Po tipu parametar je neodredjen, pa se moze preneti niz bilo kog tipa 
n - velicina jednog podatka u bajtovima
broj = broj podataka koji se ucitavaju

return value = broj uspesno ucitanih podataka . Ukoliko je ovaj broj != od broja podataka koje zelimo ucitati, doslo je do greske (if value != broj);

// fwrite
size_t fwrite(void* odrediste, size_t velicina, size_t broj, FILE* file) // upis u binarni file. 
odrediste - Pokazivac na pocetak niza podataka koje zelimo da upisemo u binarni file
velicina - velicina jednog podatka u bajtovima
broj - ukupan broj podataka koji se jednim pozivom ove f-je upisuje u file

return value = Broj uspesno upisanih podataka. Ukoliko se ovaj broj != od broja podataka koje zelimo da upisemo, doslo je do greske(if value != broj);


// Pozicioniranje u file-u

//fseek
int fseek(FILE *f, long int offset, int reference) // Omogucava pozicioniranje na zeljeni byte u file-u
offset - pomeraj
referenca - referentna tacka u odnosu na koju se racuna offset (pomeraj) ->
        SEEK_SET - Pocetak file-a
        SEEK_CUR - Trenutna pozicija u file-u (nakon citanja fread f-jom, pozicija je velicina*broj+1)
        SEEK_END - Kraj file-a
        



