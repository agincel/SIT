/*
*	Adam Gincel
*	my_int.c
*	Prints out a given integer, positive or negative.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

void my_int(int x)
{
	int divisor = 1;

	if(x < 0) 
		my_char('-'); /* If x is negative, print the minus sign */

	while (x >= 0 ? x / divisor >= 10 : x / divisor <= -10) 
		divisor *= 10; /* Brings divisor up to same magnitude as int */

	while (divisor > 0) 
	{
		my_char((char)(x >= 0 ? (x / divisor) : -(x / divisor)) + '0'); /* If x is negative, multiply the digit recieved by -1 */
		x = x - (x / divisor) * divisor;
		divisor = divisor / 10;
	}
}
