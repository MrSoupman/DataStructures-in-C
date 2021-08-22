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
void FreeBigInteger(BigInteger* big)
{
	FreeNode(big->front);
	free(big);
}

//Frees any allocated memory, exits program with exit_failure
int ThrowException(BigInteger* big)
{
	FreeNode(big->front);
	exit(EXIT_FAILURE);
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
				fprintf(stderr, "Malformed input, exitting...");
				ThrowException(big);
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
		{
			fprintf(stderr, "Malformed input, exitting...");
			ThrowException(big);
		}
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


BigInteger* add(BigInteger *first, BigInteger *second)
{
	int len;
	//Need to get the longest digit length
	if(first->numDigits > second->numDigits)
		len = first->numDigits;
	else
		len = second->numDigits;

	char* temp = malloc(len + 2);
	memset(temp,'\0',sizeof(temp));
	int i;
	DigitNode *ptr1 = first->front, *ptr2 = second->front;
	short digit, carry= 0;
	while(ptr1 != NULL && ptr2 != NULL)
	{
		digit = ptr1->digit + ptr2->digit;
		if(carry)
		{
			digit++;
			carry = 0;
		}
		if(digit > 9)
		{
			carry = 1;
			digit %= 10;
		}
		char c = (digit) + '0';
		strncat(temp, &c, 1);
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}

	//Appends remaining digits
	char c;
	if(ptr1 != NULL)
	{
		while(ptr1 != NULL)
		{
			c = (ptr1->digit) + '0';
			strncat(temp, &c, 1);
			ptr1 = ptr1->next;
		}
	}
	else if(ptr2 != NULL)
	{
		while(ptr2 != NULL)
		{
			c = (ptr2->digit) + '0';
			strncat(temp,&c , 1);
			ptr2 = ptr2->next;
		}
	}
	BigInteger* ans = parse(temp);
	free(temp);
	return ans;
}

char* toString(BigInteger* big)
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