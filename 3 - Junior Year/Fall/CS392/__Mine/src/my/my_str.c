/*
*	Adam Gincel
*	my_str.c
*	Prints out a given string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

void my_str(char* str)
{
	while(str != 0 && str[0] != '\0')
	{
		my_char(str[0]);
		str++;
	}
}
