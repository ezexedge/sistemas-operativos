#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

union semun {
	int val;                    /* value for SETVAL */
	struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
	unsigned short int *array;  /* array for GETALL, SETALL */
	struct seminfo *__buf;      /* buffer for IPC_INFO */
};

int shmid, status;
void *shared_memory = (void *)0;
int sem_prod, sem_cons;

void liberar_recursos(int pid){
	if ( semctl(sem_prod, 0, IPC_RMID) == -1){
		fprintf(stderr, "Error eliminando semaforo productor. %d\n",pid);
		exit(EXIT_FAILURE);
	}
	if ( semctl(sem_cons, 0, IPC_RMID) == -1){
		fprintf(stderr, "Error eliminando semaforo consumidor. %d\n",pid); 
		exit(EXIT_FAILURE);
	}
	if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed. %d\n",pid);
		exit(EXIT_FAILURE);
	}
	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "shmctl(IPC_RMID) failed. %d\n",pid);
		exit(EXIT_FAILURE);
	}
}

int error( char *msg, int pid ){
	fprintf(stderr, msg, pid);
	liberar_recursos(pid);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	pid_t pid;
	union semun arg;
	char *letra;
	struct sembuf arriba = {0,1,SEM_UNDO};
	struct sembuf abajo = {0,-1,SEM_UNDO};

	shmid = shmget((key_t)1234, sizeof(char), 0666 | IPC_CREAT);

	if (shmid == -1) error("shmget failed\n",0);

	if (( shared_memory = shmat(shmid, 0, 0)) < (void *)0) error("shmat failed\n",0);

	printf("Memory id: %d\n", shmid);fflush(stdout);

	letra = (char *)shared_memory;

	*letra='A';	

	/*
	Constructed by logically ORing one or more of the following values:
		IPC_CREAT	Creates the data structure if it does not already exist.
		IPC_EXCL	Causes the semget subroutine to fail if the IPC_CREAT value is also set and
					the data structure already exists.
		S_IRUSR	Permits the process that owns the data structure to read it.
		S_IWUSR	Permits the process that owns the data structure to modify it.
		S_IRGRP	Permits the group associated with the data structure to read it.
		S_IWGRP	Permits the group associated with the data structure to modify it.
		S_IROTH	Permits others to read the data structure.
		S_IWOTH	Permits others to modify the data structure.
	*/
	sem_prod = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	sem_cons = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	if ((sem_prod == -1) || (sem_cons==-1))
		error("Error creando semaforos",0);
	
	arg.val = 0;
	
	if (semctl(sem_cons, 0, SETVAL, arg) == -1)
		error("Error incializando el semaforo del consumidor.",0);

	arg.val = 1;

	if ( semctl(sem_prod, 0, SETVAL, arg)== -1) 
		error("Error incializando el semaforo del productor.",0);

	if ( (pid = fork()) == -1)
		error("Error creando procesos\n",0);

	if (pid == 0) {
		// Hijo
		while ( *letra < 90 ) { // 'Z' = 90
 			if ( semop(sem_prod, &abajo, 1) == -1 )
				error("Error bajando el semaforo del productor\n",pid);

			printf("Letra H: %c\n", (*letra)++); fflush(stdout);

			if ( semop(sem_cons, &arriba, 1) == -1)
				error("Error subiendo el semaforo del consumidor\n",pid);
		}
		return(0);
	} else {
		// Padre
		while ( *letra < 90 ) { // 'Z' = 90
			if ( semop(sem_cons, &abajo, 1) == -1)
				error("Error bajando semaforo del consumidor\n",pid);


			printf("Letra P: %c\n", (*letra)++); fflush(stdout);
			
			if ( semop(sem_prod, &arriba, 1) == -1)
				error("Error subiendo semaforo del productor\n",pid);
		}
	}

	printf("Espero a hijo %d ...\n", pid); fflush(stdout);
	waitpid(pid, &status, 1);
	printf("Libero recursos...\n"); fflush(stdout);
	liberar_recursos(0);
	printf("Fin.\n");fflush(stdout);
    return(EXIT_SUCCESS);
}
