#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void manejador(int sig);

int main(int argc, char *argv[]) { 

	if ( signal(SIGTERM, manejador) == SIG_ERR) {
		perror("Error instalando manejador de SIGTERM");
		exit (-1); 
	} 
	printf("Proceso %d esperando..\n",getpid());
	printf("Ejecutar kill -15 %d\n",getpid());
	while(1)
		sleep(5);
	exit(0); 
} 

void manejador(int sig) {
		printf(":p \n");
} 

