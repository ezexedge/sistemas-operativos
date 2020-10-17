#include <stdio.h>      // printf, fflush, etc
#include <stdlib.h>     // exit

/*
	La diferencia entre return y exit es que
	return es el retorno de una funcion y
	exit es un system call que termina el proceso actual.
	Pueden parecer similares al utilizarlas en main, pero
	el siguiente ejemplo aclara las dudas.
*/

void f(){
	printf("mensaje desde la funcion\n");
	return;
	//exit(0);
}

int main (int argc, char *argv[]) {
	f();
	printf("mensaje desde main\n");
	exit(0);
}
