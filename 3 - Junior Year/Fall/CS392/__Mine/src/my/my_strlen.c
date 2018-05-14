/*
*	Adam Gincel
*	my_strlen.c
*	Returns the length of a given string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

int my_strlen(char* str)
{
	if (str == 0)
		return -1;
	else
	{
		int length = 0;
		while (str[0] != '\0')
		{
			length++;
			str++;
		}

		return length;
	}
}
