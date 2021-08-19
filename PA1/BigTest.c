#include "BigInteger.h"
#include <stdio.h>
#include <stddef.h>
int main(int argc, char** argv)
{
	BigInteger *biggie;
	if(argc < 2)
		biggie = parse("000");
	else
		biggie = parse(argv[1]);
	DigitNode *ptr = biggie->front;

	printf("%s\n","Parse test");
	while(ptr != NULL)
	{
		printf("%d",ptr->digit);
		ptr = ptr->next;
	}
	printf("\n%s","Negative: ");
	if(biggie->negative)
		printf("Yes\n");
	else
		printf("No\n");
	printf("%s : %d\n","Number of digits",biggie->numDigits);
	return 0;
}
