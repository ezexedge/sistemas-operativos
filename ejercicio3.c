#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    pid_t pid1, pid2,pid3;
    int status1, status2,status3;
 
    if ( (pid1=fork()) == 0 )
    { /* hijo */
        printf("Soy el primer hijo (%d, hijo de %d)\n",  getpid(), getppid());
    }
    else
    { /*  padre */
        if ( (pid2=fork()) == 0 )
        { /* segundo hijo  */
            printf("Soy el segundo hijo (%d, hijo de %d)\n",  getpid(), getppid());
        }
        else
        {
            if ( (pid3=fork()) == 0 )
        { /* segundo hijo  */
            printf("Soy el tercer hijo (%d, hijo de %d)\n",  getpid(), getppid());
        }else{

        
            waitpid(pid1, &status1, 0);
/* Esperamos al segundo hijo */
            waitpid(pid2, &status2, 0);
            
            waitpid(pid3, &status3, 0);


            printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
        }


        }
    }
 
    return 0;
}
