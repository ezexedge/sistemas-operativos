#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void manejadorUSR1(int sig);
void manejadorUSR2(int sig);
void manejadorTERM(int sig);
int cuenta1 = 0, cuenta2 = 0;
int main()
{
 if ( signal(SIGUSR1, manejadorUSR1) == SIG_ERR) {
 perror("Error instalando manejadorUSR1 - ");
 return -1;
 }
 if ( signal(SIGUSR2, manejadorUSR2) == SIG_ERR) {
 perror("Error instalando manejadorUSR2 - ");
 return -1;
 }
 if ( signal(SIGTERM, manejadorTERM) == SIG_ERR) {
 perror("Error instalando manejadorTERM - ");
 return -1;
 }
	printf("Proceso %d esperando..\n",getpid());
	printf("Ejecutar kill -15 %d\n",getpid());
	while(1)
		sleep(5);
	exit(0); 
}
//-------------------------
void manejadorUSR1(int sig) {
 if ( signal(SIGUSR1, manejadorUSR1) == SIG_ERR) {
 perror("Error instalamdno manejadorUSR1 - ");
 exit(0);
 }
 cuenta1++;
}
//-------------------------
void manejadorUSR2(int sig) { 

 if ( signal(SIGUSR2, manejadorUSR2) == SIG_ERR) {
 perror("Error instalamdno manejadorUSR2 - ");
 exit(0);
 }
 cuenta2++;
}
//---------------------------
void manejadorTERM(int sig) {
 printf("Señales USR1 recibidas: %i \n", cuenta1);
 printf("Señales USR2 recibidas: %i \n", cuenta2);
 exit(0);
} 
