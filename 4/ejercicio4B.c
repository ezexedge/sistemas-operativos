#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void factorial (int n1,int n2) {
 int resultado1= 1;
 int resultado2=1;
int num1,num2;
pid_t process;

int randomTime = rand() % 5;

if((process = fork()) == 0){  
for (num1= 2; num1<= n1; num1++) {
resultado1= resultado1 * num1;
printf ("Factorial de %d, resultado parcial %d\n",
n1, resultado1);
sleep (randomTime);
}
}

if((process= fork()) == 0){ 
for (num2= 2; num2<= n2; num2++) {
resultado2= resultado2 * num2;
printf ("Factorial de %d, resultado parcial %d\n",
n2, resultado2);
sleep (randomTime);
} 
}

printf("el factorial de %d es %d\n el factorial de %d es %d, procesos %d\n",n1,resultado1,n2,resultado2,process);
}

int main (int argc, char *argv[]) {

//if (argc== 2)
factorial (atoi (argv[1]),atoi(argv[2]));
return 0;
} 
