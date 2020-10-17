#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int shmid;

	/* Expect an segment id on the command-line */
	if(argc != 2) {
		printf("USAGE: %s <identifier>",argv[0]);fflush(stdout);
		exit(EXIT_FAILURE);
	}
	shmid = atoi(argv[1]);

	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	printf("segment removed: %d\n", shmid);
	system("ipcs -m");

	exit(EXIT_SUCCESS);
}
