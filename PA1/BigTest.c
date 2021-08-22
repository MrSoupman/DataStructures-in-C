#include "BigInteger.h"
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
int main(int argc, char** argv)
{
	int c;
	
	do
	{
		printf("(p)arse, (a)dd, (m)ultiply, or (q)uit? => ");
		c = tolower(getchar());
		getchar(); //flush input stream
		if(c == 'p')
		{
			printf("\tEnter integer => ");
			char buff[256];
			fgets(buff, 255, stdin);
			BigInteger* biggie = parse(buff);
			char* str = toString(biggie);
			printf("\tValue = %s\n", str);
			FreeBigInteger(biggie);
		}
		if(c == 'a')
		{
			char buff[256];
			printf("\tEnter first integer => ");
			fgets(buff, 255, stdin);
			BigInteger* first = parse(buff);
			memset(buff,'\0',sizeof(buff));
			printf("\tEnter second integer => ");
			fgets(buff, 255, stdin);
			BigInteger* second = parse(buff);
			BigInteger* ans = add(first, second);
			char* str = toString(ans);
			printf("\t\tSum: %s\n", str);
			free(str);
			FreeBigInteger(first);
			FreeBigInteger(second);
			FreeBigInteger(ans);

		}
	} while (c != 'q');
	
	
	
	return EXIT_SUCCESS;
}
