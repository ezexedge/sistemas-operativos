#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { 
	int a;
//	int b;
	printf("Hola Mundo!!!\n"); 

	for (a=0 ; a < argc ; a++ ) {
		printf("argv[%d]= %s\n",a,argv[a]); 
	}
	printf("\n"); 

	return(0); 
}
