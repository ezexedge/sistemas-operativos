#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
//int c;

pid_t pid;
pid = fork();

printf("Soy el proceso padre: \n\t Mi PID es %d. El PID de mi padre es: %d. \n\t Mi hijo %d terminó. \n", getpid(), getppid(), pid);


}
