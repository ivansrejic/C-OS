/*Korišćenjem programskog jezika C napisati Linux/UNIX program koji u zadatom direktorijumu
(naziv direktorijuma se zadaje kao prvi argument komandne linije) pronalazi i štampa nazive svih
datoteka koje u imenu sadrže string koji se zadaje kao drugi argument komandne linije.
Pretraživanje se obavlja rekurzivno u zadatom direktorijumu i svim njegovim poddirektorijumima.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void processdir(char* foldername, char* str)
{
	DIR* dp;
	struct dirent* dirp;
	
	struct stat statbuf;
	int result;

	if ((dp = opendir(foldername)) == NULL)
	{
		printf("Greska prilikom otvaranja foldera %s!\n", foldername);
		return;
	}

	while( (dirp = readdir(dp)) != NULL )
	{
		char tmp[1024] = "";
		strcat(tmp, foldername);
		strcat(tmp, "/");
		strcat(tmp, dirp->d_name);

		printf("Obradjujem %s u %s.\n", dirp->d_name, tmp);
		
		if ((result = stat(tmp, &statbuf)) == -1)
		{
			printf("Neuspesno citanje podataka o objektu: %s\n", tmp);
			continue;
		}

		if (strstr(dirp->d_name, str) != NULL)
			printf("*********Pronasao %s\n", tmp);

		if (S_ISDIR(statbuf.st_mode) && strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
		{
			printf("Otvaram folder %s.\n", tmp);
			processdir(tmp, str);
		}
	}

	closedir(dp);
}
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Neophodna su dva argumenta (putanja do foldera i string koji se trazi)!\n");
		exit(1);
	}

	processdir(argv[1], argv[2]);
}