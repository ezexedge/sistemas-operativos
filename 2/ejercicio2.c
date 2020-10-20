#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
int c;
pid_t pid;
     
printf("Comienzo.:\n");
for (c = 0; c < 6 ; c++ )
{
pid = fork();
}
printf("Proceso\n");

printf("pid %d. pid padre: %d. \n\t pid hijo %d terminó. \n", getpid(), getppid(), pid);
     
return 0;
}
