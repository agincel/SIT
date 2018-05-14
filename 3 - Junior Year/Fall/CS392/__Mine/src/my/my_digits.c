/*
*	Adam Gincel
*	my_digits.c
*	Prints out digits 0-9.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

void my_digits()
{
	char i = '0';
	while(i <= '9')
	{
		my_char(i);
		i++;
	}
}