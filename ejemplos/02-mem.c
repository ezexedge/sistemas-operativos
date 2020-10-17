#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen

int main (int argc, char *argv[])
{
	char *p;
	char *word;

	p=(char *)malloc(sizeof(char));

	*p='A';	

	printf("Letra     = %c\n", *p);
	printf("sizeof *p = %ld\n", sizeof(*p));
	printf("Pos. mem in hexadecimal *p = %p\n", &(*p)); // Lugar de memoria donde se encuentra la letra 'A'
	printf("Pos. mem in hexadecimal  p = %p\n", &p);    // Lugar de memorio donde se encuentra el puntero p


	printf("sizeof char = %ld\n", sizeof(char));
	printf("sizeof int  = %ld\n", sizeof(int));
	printf("sizeof long = %ld\n", sizeof(long));

	free(p);

	word=(char *)malloc(sizeof(char) * strlen("CADENA") + 1 );
	strcpy(word,"CADENA");
	printf("word     = %s\n", word);
	printf("strlen = %ld\n", strlen(word));
	printf("strlen = %ld\n", strlen("CADENA"));
	free(word);

	exit(0);
}

