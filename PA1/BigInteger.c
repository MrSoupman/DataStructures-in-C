#include "BigInteger.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//helper method that allocates and returns a digit node
DigitNode* CreateNode(int num, DigitNode* nextNode)
{
	DigitNode* node = (DigitNode*)malloc(sizeof(DigitNode*));
	node->digit = num;
	node->next = nextNode;
	return node;
}
void FreeNode(DigitNode* node)
{
	DigitNode *ptr;
	while(node != NULL)
	{
		ptr = node;
		node = node->next;
		free(ptr);

	}
}

//Frees any allocated memory, returns an 'empty' big integer as a way to prevent malformed inputs
BigInteger* ThrowException(BigInteger* big)
{
	big->negative = 1;
	FreeNode(big->front);
	big->front = NULL;
	big->numDigits = 0;
	return big;
}

//Since C does not have exceptions, whenever we throw an exception, the biginteger will be empty, and have its negative flag set
int isValid(BigInteger* biggie)
{
	return biggie->front == NULL && biggie->negative == 1;
}

BigInteger* parse(char* integer)
{
	//init our big integer
	BigInteger* big = (BigInteger *)malloc(sizeof(BigInteger *));
	big->front == NULL; //front is empty
	big->numDigits = 0; //no digits in our big integer

	//checks for negative number
	if(integer[0] == '-')
		big->negative = 1;
	else
		big->negative = 0;


    int i, isTrail = 0;
	for(i = big->negative; i < strlen(integer); i++)
	{
        char c = integer[i];
		if(isdigit(c))
		{
			if(isTrail) //Space in middle, malformed input
			{
				//Returns our version of an exception
				return ThrowException(big);
			}
			int num = c -'0';
			if(num == 0 && big->front == NULL) //checking for leading zeroes
				continue;
			big->front = CreateNode(num,big->front);
			big->numDigits++;
		}
		//How do we deal with numbers that have spaces in the middle, as well as numbers that have
		//trailing zeroes?
		else if(isspace(c))
			isTrail = 1;
		else
			return ThrowException(big);
	}

	//At the end, check if input was just a zero or something
	if(big->front == NULL)
	{
		big->negative = 0;
		big->numDigits = 1;
		big->front = CreateNode(0,big->front);
	}
	return big;
}


char* toString(BigInteger* big) //borked lol
{
	int count = big->numDigits + 2; //we add 2, one for possible negative sign, another for null terminal
	char* temp = malloc(count);
	memset(temp,'\0',sizeof(temp));
	DigitNode *ptr = big->front;

	//Store the reversed big Integer into temp
	while(ptr != NULL)
	{
		char c = (ptr->digit) + '0';
		strncat(temp,&c,1);
		ptr = ptr->next;
	}
	char* str = malloc(count);
	memset(str,'\0',sizeof(str));
	int i;
	if(big->negative)
		strncat(str, "-", 2);

	//Reverse the string
	for(i = count-1; i >= 0; i--) //-1 because of null terminal
	{
		char c = temp[i];
		strncat(str,&c,1);
	}
	free(temp);
	return str;
}