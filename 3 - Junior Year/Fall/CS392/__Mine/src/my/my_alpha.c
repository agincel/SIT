/*
*	Adam Gincel
*	my_alpha.c
*	Prints all capital letters A-Z.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

void my_alpha()
{
	char i = 'A';
	while(i <= 'Z')
	{
		my_char(i);
		i++;
	}	
}