/*
*	Adam Gincel
*	my_num_base.c
*	Takes a base 10 number and an alphabet, and converts the number to 
*	the base of the length of the string, using the string to print out results.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"
#include <limits.h>

void my_num_base(int x, char* alphabet)
{
	if(alphabet != 0)
	{
		unsigned int divisor = 1, base = my_strlen(alphabet), i, j;
		j = 0;
		if(x < 0)
			my_char('-'); /* If x is negative, print the minus sign */

		i = x >= 0 ? x : (x == INT_MIN ? (unsigned int)INT_MAX + 1 : -x);

		if(base == 1)
		{
			for(j = 0; j < i; j++)
				my_char(alphabet[0]);
		}
		else if(base >= 1)
		{
			while (i / divisor >= base) divisor *= base; /* Brings divisor up to same magnitude as int */

			while (divisor != 0) 
			{
				my_char(alphabet[(i / divisor)]); /* If x is negative, multiply the digit recieved by -1 */
				i = i - (i / divisor) * divisor;
				divisor = divisor / base;
			}
		}
	}
	
}
