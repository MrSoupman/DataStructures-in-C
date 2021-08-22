#ifndef BIGINT_H
#define BIGINT_H
#include <stdlib.h>
typedef struct DigitNode
{
	short digit;
	struct DigitNode *next;

}DigitNode;

typedef struct BigInteger
{
	short negative; //0 is false, 1 is true
	int numDigits; //number of digits in this integer
	DigitNode *front;
}BigInteger;

BigInteger* parse(char* integer);
char* toString(BigInteger* big);

#endif
