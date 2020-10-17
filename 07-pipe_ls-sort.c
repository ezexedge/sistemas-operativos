#include <unistd.h> // execlp pipe dup2
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// ls | sort -r

int main(int argc, char *argv[])
{
	int tubo[2];
	pipe(tubo);
/*
    fd[0] R         fd[0] R
    fd[1] W         fd[1] W
*/
	if (fork()!=0) { // padre
		dup2(tubo[0], STDIN_FILENO);
		close(tubo[1]);
				    //argv[0], argv[1], argv[2]
		execlp("sort", "sort", "-r"   , NULL);
		printf("Padre\n");
		close(tubo[0]);
	} else { // hijo
		dup2(tubo[1], STDOUT_FILENO);
		close(tubo[0]);
		execlp("ls", "ls", NULL);
		printf("Hijo\n");
		close(tubo[1]);
	}
	return(0);
}
