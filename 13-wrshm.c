/*
 * wrshm.c - Write data to a shared memory segment
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h> // memset

#define BUFSZ 4096

int main(int argc, char *argv[])
{
	int shmid;			/* Segment ID */
	char *shmbuf;		/* Address in process */
	char *shmbuf2;		/* Address in process */
//	int fd;				/* File descriptor */
	int c, i;
    
	/* Expect an segment id on the command-line */
	if(argc != 2) {
		puts("USAGE: wrshm <identifier>");
		exit(EXIT_FAILURE);
	}
	shmid = atoi(argv[1]);
    
	/* Attach the segment */
	if((shmbuf = shmat(shmid, 0, 0)) < (char *)0) {
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	shmbuf2=shmbuf;
	memset(shmbuf, 0, BUFSZ); // llena de 0 la memoria

	/* Write user input to the segment */
	i = 0;
	while((c = getchar()) != EOF) {
		*(shmbuf++) = c;
		++i;
	}
	write(STDOUT_FILENO, shmbuf, i);
	printf("wrote %d characters to shared memory\n", i);
  
    /* Detach */
    if((shmdt(shmbuf2)) < 0) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}
