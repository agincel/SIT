/*
*	Adam Gincel
*	my_strrindex.c
*	Finds and returns a pointer to the last ocurring index of a given character within a given string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strrindex(char* str, char c)
{
	int characterIndex = -1, i = 0;
	char *empty = "";

	if(str == empty)
		return "";

	while (str != NULL && str[i] != '\0')
	{
		if(str[i] == c)
			characterIndex = i;
		i++;
	}

	return characterIndex == -1 ? 0 : str + characterIndex;

}
