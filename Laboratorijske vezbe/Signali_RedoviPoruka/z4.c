//Korišćenjem programskog jezika C napisati UNIX/Linux program koji svom procesu detetu,
//korišćenjem redova poruka, prosleđuje ulaz koji prima preko tastature, a process dete dobijene
//poruke štampa na ekranu. Predvideti da se unosom teksta “QUIT” prekida rad programa.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGLEN 50

struct mymsgbuf
{
	long mtype;
	char mtext[MSGLEN];
};

main()
{
	int msqid;
	struct mymsgbuf buf;

	buf.mtype = 1;
	strcpy(buf.mtext, "");

	msqid = msgget(10104, 0666 | IPC_CREAT);

	if (fork() == 0)
	{
		while(strcmp(buf.mtext, "quit") != 0)
		{
			msgrcv(msqid, &buf, 50, 0/*sve poruke*/, 0/*blokirajuci */);
			printf("Proces dete: %s\n", buf.mtext);
		}
	}
	else
	{
		while(strcmp(buf.mtext, "quit") != 0)
		{
			scanf("%s", buf.mtext);
			msgsnd(msqid, &buf, strlen(buf.mtext)+1, 0/*blokirajuci */);
		}

		wait(NULL);
		msgctl(msqid, IPC_RMID, NULL);
	}

}