/*
*	Adam Gincel
*	my_strrindex.c
*	Finds the rightmost index of a given character in a given string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

int my_rfind(char* str, char c)
{
	int characterIndex = -1, i = 0;

	while (str != 0 && str[i] != '\0')
	{
		if(str[i] == c)
			characterIndex = i;
		i++;
	}

	return characterIndex;
}
