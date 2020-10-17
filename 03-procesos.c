#include <stdlib.h> 	// exit
#include <stdio.h>		// printf, fflush, etc
#include <sys/types.h>  // fork
#include <unistd.h>     // waitpid

int main(int argc, char *argv[]) {
	pid_t pid;

    printf("pid %d ppid %d\n", getpid(), getppid()); 
	fflush(stdout);

	printf("Comienzo.:\n"); 
	fflush(stdout);

	pid = fork();

  	printf("Pid %d ppid %d Hpid:%d\n",getpid(),getppid(),pid); 
	fflush(stdout);

	if( pid == 0 ){ //Hijo
		sleep(3);
	}

	printf("Fin proceso %d\n",getpid());
	fflush(stdout);

	exit(0);
}
