/*Korišćenjem programskog jezika C napisati Linux/UNIX program koji u zadatom direktorijumu
određuje naziv najveće datoteke. Ime direktorijuma se programu prosleđuje kao argument
komandne linije.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#define MAX_NAME 1024

int main(int argc, char * argv[])
{
	char dirname[MAX_NAME];
	char path[MAX_NAME];
	char maxpath[MAX_NAME];
	int size;
	struct stat statbuf;
	DIR * dp;
	struct dirent * dirp;

	if (argc < 2)
	{
		printf("Nema dovoljno ulaznih argumenata\n");
		exit(-1);
	}

	strcpy(dirname, argv[1]);
	
	if (stat(dirname, &statbuf) < 0)
	{
		printf("Doslo je do greske prilikom ocitavanja statusa unete putanje\n");
		exit(-1);
	}

	
	if (!S_ISDIR(statbuf.st_mode))
	{
		printf("Uneti argument ne predstavlja putanju do direktorijuma\n");
		exit(-1);
	}

	dp = opendir(dirname);

	if (dp == NULL)
	{
		printf("Doslo je do greske prilikom otvaranja direktorijuma\n");
		exit(-1);
	}

	size = 0;

	while((dirp = readdir(dp)) != NULL)
	{
		strcpy(path, dirname);
		strcat(path, "/");
		strcat(path, dirp->d_name);

		stat(path, &statbuf);

		if (S_ISREG(statbuf.st_mode))
		{
			if (statbuf.st_size > size)
			{
				strcpy(maxpath, path);
				size = statbuf.st_size;
			}

		}
	}

	printf("Datoteka %s ima maksimalnu velicinu %dB\n", maxpath, size);
	closedir(dp);

	return 0;
}