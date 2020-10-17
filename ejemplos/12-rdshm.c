#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

#define BUFSZ 4096

int main(int argc, char *argv[])
{
	int shmid;			/* Segment ID */
	char *shmbuf;		/* Address in process */
    
	/* Expect an segment id on the command-line */
	if(argc != 2) {
		puts("USAGE: wrshm <identifier>");
		exit(EXIT_FAILURE);
	}
	shmid = atoi(argv[1]);
    
	/* Attach the segment */
	if((shmbuf = shmat(shmid, 0, SHM_RDONLY)) < (char *)0) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}
    
	printf("Contenido de la shmem:\n");
	write(STDOUT_FILENO, shmbuf, BUFSZ);

    /* Detach */
    if((shmdt(shmbuf)) < 0) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}
