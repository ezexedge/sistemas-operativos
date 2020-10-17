#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main( int argc, char *argv[])
{
	pid_t childID;
	int a;
	//int cantidad=64000;
	int cantidad=5;

	for (a=0 ; a<cantidad ; a++ ){

     	if ((childID = fork()) == -1) {  // Intenta crear al hijo.
        	perror("fork error");
        	sleep(1);
        	exit(EXIT_FAILURE);
     	}
     	else if (childID > 0) { // Look, Yo Soy tu padre!
        	printf("Proceso padre, espera 1 seg...\n"); fflush(stdout);
        	sleep(1);
     	}
     	else { 
			printf("hijo %d me voy en 2 seg...\n",getpid());
        	sleep(2);
        	exit(0);
		}
	}
	sleep(15);
	return(0); // El Hijo aqui no llega nunca
}
