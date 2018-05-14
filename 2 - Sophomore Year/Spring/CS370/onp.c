/*
*  ONP.c
*  Takes a number of expressions to convert, then converts that many infix expressions to postfix.
*
*  Written by: Adam Gincel, Alex Massenzio, and Matt Gomez
*  I pledge my honor that I have abided by the Stevens Honor System.
*
*  February 9th 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int operatorValue(char op)               /* Converts a character to an integer value for comparison */
{
	if (op == '+' || op == '-')          /* + and - are 1 */
		return 1;
	else if (op == '*' || op == '/')     /* * and / are 2 */
		return 2;
	else if (op == '^')                  /* ^ is 3 */
		return 3;
	else if (op == '(')                  /* Open paren is a special case so it is -1 */
		return -1;
	else if (op == ')')                  /* Close paren is highest priority so it is 4 */
		return 4;
	else
		return 0;
}

int main()
{
	char expression[401];                /* char * holding current expression */
	char stack[401];                     /* char* stack which operators get pushed to and popped from as per the shunting yart algorithm */

	char toPrint[401];                   /* the final string is written to here, then printed */

	int numExpressions = 0, i = 0, j = 0, stackTop = -1, printTop = -1;
	char current = '\0';
	int currentValue = 0;

	scanf("%d", &numExpressions);        /* how many expressions are we evaluating */

	for(i = 0; i < numExpressions; i++)  /* for that many expressions */
	{
		for(j = 0; j < 401; j++)         /* clear out expression, stack, and toPrint for every line */
		{
			expression[j] = '\0';        /* guarantees zeroed out string */
			stack[j] = '\0';             /* and stack */
			stackTop = -1;
			toPrint[j] = '\0';           /* and printing string */
			printTop = -1;
		}

		scanf("%s", expression);         /* load our expression */
		j = 0;
		while(expression[j] != '\0')     /* iterate through string */
		{
			current = expression[j];
			currentValue = operatorValue(current);
			if(currentValue == 0)        /* normal character */
			{
				toPrint[++printTop] = current;
			}
			else if (currentValue == 1 || currentValue == 2 || currentValue == 3)  /* + - * / ^ */
			{
				if (stackTop < 0 || currentValue > operatorValue(stack[stackTop])) /* if highest priority, push to stack */
				{
					stack[++stackTop] = current;
				}
				else                     /* otherwise pop from stack until it is highest priority */
				{
					while(stackTop > -1 && currentValue <= operatorValue(stack[stackTop]))
					{
						toPrint[++printTop] = stack[stackTop--];
					}
					                     /* now we push our operator to the stack */
					stack[++stackTop] = current;
				}
			}
			else if (currentValue == -1) /* always push an open parenthesis */
			{
				stack[++stackTop] = current;
			}
			else if (currentValue == 4)  /* close parenthesis - pop until open parenthesis */
			{
				while(operatorValue(stack[stackTop]) != -1) 
				{
					toPrint[++printTop] = stack[stackTop--];
				}

				stackTop--;              /* pop open parenthesis into nothing; don't print */
			}
			j++;                         /* go to next character in expression */
		}
	
			while(stackTop > -1)             /* pop any leftover operators on the stack */
		{
			toPrint[++printTop] = stack[stackTop--];
		}

		printf("%s\n", toPrint);         /* print our finished expression, then get new one */
	}

	return 0;                            /* program executed successfully */
}

