/*
 * mkshm.c - Create and initialize shared memory segment
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 4096		/* Size of the segment */

int main(int argc, char* argv[])
{
	int shmid;
     
	if((shmid = shmget(IPC_PRIVATE, BUFSZ*sizeof(char), 0666)) < 0) {
		perror("shmget");
		exit(EXIT_FAILURE);
	}

	printf("Segment created: %d\n", shmid);

	system("ipcs -m");

	exit(EXIT_SUCCESS);
}
