#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	DIR* dp;
	struct dirent* dirp;
	int brfldr, brdat, brlnk;
	struct stat statbuf;
	int result;
	char path[255];

	if (argc != 2)
	{
		printf("Neophodan je jedan argument (putanja do direktorijuma)!\n");
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL)
	{
		printf("Greska prilikom otvaranja foldera %s!\n", argv[1]);
		exit(1);
	}

	brfldr = brdat = brlnk = 0;

	while( (dirp = readdir(dp)) != NULL )
	{
		//formiranje putanje do datoteke
		strcpy(path, argv[1]);
		strcat(path, "/");
		strcat(path, dirp->d_name);

		printf("Test: %s\n", path);

		if ((result = stat(path, &statbuf)) == -1)
		{
			printf("Neuspesno citanje podataka o objektu %s\n:", dirp->d_name);
			continue;
		}

		if (S_ISDIR(statbuf.st_mode))
		{
			printf("Objekat: %s je direktorijum\n", dirp->d_name);
			brfldr++;
		}

		if(S_ISREG(statbuf.st_mode))
		{
			printf("Objekat: %s je regularna datoteka\n", dirp->d_name);
			brdat++;
		}

		if(S_ISLNK(statbuf.st_mode))
		{
			printf("Objekat: %s je link\n", dirp->d_name);
			brlnk++;
		}
	}

	printf("Statistika za folder: %s\nPodfoldera: %d\nReg. datoteka: %d\nLinkova: %d\n", argv[1], brfldr, brdat, brlnk);

	closedir(dp);
}
