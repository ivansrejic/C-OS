#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
	DIR* dp;
	struct dirent* dirp;

	if (argc != 3)
	{
		printf("Neophodna su dva argumenta (putanja do direktorijuma i string koji se trazi)!\n");
		exit(-1);
	}

	if ((dp = opendir(argv[1])) == NULL)
	{
		printf("Greska prilikom otvaranja direktorijuma %s!\n", argv[1]);
		exit(-1);
	}

	while( (dirp = readdir(dp)) != NULL )
	{
		if (strstr(dirp->d_name, argv[2]) != NULL)
			printf("%s\n", dirp->d_name);
	}

	closedir(dp);
}