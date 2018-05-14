/*
*	Adam Gincel
*	my_find.c
*	Finds and returns the first ocurring index of a given character within a given string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

int my_find(char* str, char c)
{
	int characterIndex = -1, i = 0;

	while (str != 0 && str[i] != '\0')
	{
		if(str[i] == c)
			characterIndex = (characterIndex == -1) ? i : characterIndex;
		i++;
	}

	return characterIndex;
}
