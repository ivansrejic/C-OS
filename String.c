#include <stdio.h>

//strlen
strlen(char* string) // vraca duzinu stringa , povratna vrednost je size_t koji sadrzi vrednost memorije koju string zauzima. Moze i int da vrati

//strcpy
char* strcpy(char* string1,char* string2) // vrsi kopiranje string2 u string1
strcpy(x+9,y+7) // kopira y string od 7.karaktera u string x od 9.karaktera

//strncpy
char* strncpy(char* string1,char* string2,size_t n) // vrsi kopiranje n karaktera iz string2 u string1 

//strcmp
int strcmp(char* string1,char* string2) // vrsi uporedjivanje string1 i string2 -> <0 prvi razlicit karakter string1 < string2 ; >0 prvi razlicit karakter string1 > string2 ; =0 string1 = string2

//strncmp
int strncmp(char* string1,char* string2,size_t n) // uporedjuje prvih n karaktera string1 i string2 , povratna vrednost ista kao i u strcmp

//strcat
char* strcat(char* string1,char* string2) // konkatenacija string1 i string2

//strncat
char* strncat(char* string1,char* string2,size_t n) // konkatenacija n karaktera string2 u string1 

//strchr
char* strchr(char* string,char ch) // trazi karakter ch u string1 , ako je char* return value - vraca string od tog karaktera do kraja. Vraca null ako nije sadrzan u string. return value moze biti i boolean

//strstr
char* strstr(char* string1,char* string2) // Pronalazi string2 u string1 i vraca poziciju u string1 ako se sadrzi. Ako se ne sadrzi vraca 0

//strtok
char* strtok(char* string1, char* delimetri) // izdvajanje reci iz reecenice. Nisam bas siguran tacno
