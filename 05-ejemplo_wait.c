#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	pid_t result=1;
	time_t t;
	int status;

	if ((pid = fork()) < 0) {
		perror("fork() error");
		exit(1);
	} else if (pid == 0) {
		sleep(5);
		//sleep(25);
		exit(23);
	}
	else {
		printf("child is %d\n", pid);
		do {
			//printf("WNOHANG:%d, WUNTRACED:%d, WCONTINUED:%d\n",WNOHANG,WUNTRACED,WCONTINUED );
			// WNOHANG:1, WUNTRACED:2, WCONTINUED:8
			//if ((result = waitpid(pid, &status, WUNTRACED | WCONTINUED)) == -1)
			if ((result = waitpid(pid, &status, WNOHANG)) == -1)
				perror("wait() error");
			else if (result == 0) {
				time(&t);
				printf("child is still running at %s", ctime(&t));
				sleep(1);
   			} else {
				if (WIFEXITED(status))
					printf("child exited with status of %d, result = %d\n", WEXITSTATUS(status),result);
				else
					puts("child did not exit successfully");
			}
			//printf("result=%d\n",result);
		} while (result == 0);
	}
	return(0);
}
