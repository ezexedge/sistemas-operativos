#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int     fd[2];
	pid_t   childpid;
	char    string[] = "Hello, world!\n";
	char    readbuffer[80];
        
	pipe(fd);
        
	if((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
        
	if(childpid == 0)
	{
		/* Child process closes up input side of pipe */
		close(fd[0]);

      	//sleep(5);  
 		/* Send "string" through the output side of pipe */
		write(fd[1], string, (strlen(string)+1));
		exit(0);
	}
	else
	{
		/* Parent process closes up output side of pipe */
		close(fd[1]);

      	//sleep(5);  
		/* Read in a string from the pipe */
		read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received string: %s", readbuffer);
	}

	return(0);
}

/*

Padre			   Hijo
	fd[0] R			fd[0] R
	fd[1] W			fd[1] W

Padre			   Hijo
	fd[0] R 		 fd[X] R
	fd[X] W			 fd[1] W

Padre			   Hijo
	fd[1] W <======= fd[0] R

*/


