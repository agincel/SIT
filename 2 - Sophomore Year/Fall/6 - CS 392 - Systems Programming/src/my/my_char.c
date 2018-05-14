/*
*	Adam Gincel
*	my_char.c
*	Prints out a single character using the system write() function. Given.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"
#include <unistd.h>

void my_char(char c)
{
	if(c != 0)
		write(1, &c, 1);
}

void my_newline()
{
	my_char('\n');
}
