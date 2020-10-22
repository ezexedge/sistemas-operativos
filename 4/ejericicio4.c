#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
long long int factorial (int n) {
long long int resultado= 1;
int num
int randomTime = rand() % 5;

  for (num= 2; num<= n; num++) {

     resultado= resultado * num1;
     printf ("Factorial de %d, resultado parcial %lld\n",
    n, resultado);
   sleep (randomTime);
}




return resultado;
}
int main (int argc, char *argv[]) {
if (argc== 2)
printf ("El factorial de %s es %lld\n", argv[1],
factorial (atoi (argv[1])));
return 0;
} 
