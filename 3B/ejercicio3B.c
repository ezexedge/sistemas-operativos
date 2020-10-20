#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
int c;
//pid_t pid;
printf("Comienzo.:\n");


    printf ("Inicio del proceso padre. PID=%d\n", getpid ());
for (c = 0; c < 3 ; c++ )
{
//pid = fork();
   if (fork() == 0)
        {		/* Proceso hijo */
        printf("Inicio proceso hijo. PID=%d, padre: PPID=%d\n",
              
        getpid(),getppid());
        sleep(1);
        }else{
    printf ("Fin del proceso %d\n", getpid ());        }


}
//printf("finProceso\n");
return 0;

}
