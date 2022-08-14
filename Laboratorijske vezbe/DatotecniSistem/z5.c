/*Korišćenjem programskog jezika C napisati Linux/UNIX program koji u zadatom direktorijumu
rekurzivno (maksimalno do dubine 3) briše sve regularne datoteke čija je veličina veća od 10KB.
Za brisanje datoteka koristiti rm komandu Linux operativnog sistema.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#define MAX_NAME 1024
void processdir(char * path, int level);


int main(int argc, char * argv[])
{
	char dirname[MAX_NAME];
	char path[MAX_NAME];
	struct stat statbuf;
	DIR* dp;
	struct dirent* dirp;
	int count, size;

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
		printf("Uneti argument ne predstavlja putanu do direktorijuma\n");
		exit(-1);
	}

	processdir(dirname, 1);

	return 0;

}


void processdir(char * path, int level)
{
	DIR * dp;
	struct dirent * dirp;
	char path1[MAX_NAME];
	struct stat statbuf;

	dp = opendir(path);

	if (dp == NULL)
	{
		printf("Greska prilikom otvaranja direktorijuma\n");
		exit(-1);
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		strcpy(path1, path);
		strcat(path1, "/");
		strcat(path1, dirp->d_name);

		stat(path1, &statbuf);

		if (S_ISREG(statbuf.st_mode) && statbuf.st_size > 10 * 1024)
		{
			if (fork() == 0)
			{
				printf("Delete file: %s\n", path1);
				execlp("rm", "rm", path1, NULL);
			}
			else
			{
				wait(NULL);
			}
		}
		else if (S_ISDIR(statbuf.st_mode) && level < 3)
		{
			processdir(path1, level + 1);
		}
	}

	closedir(dp);
}