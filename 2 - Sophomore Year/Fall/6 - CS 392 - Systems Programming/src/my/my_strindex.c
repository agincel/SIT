/*
*	Adam Gincel
*	my_strindex.c
*	Finds and returns a pointer to the first ocurring index of a given character within a given string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strindex(char* str, char c)
{
	int characterIndex = -1, i = 0;

	char *empty = "";
	if(str == empty)
		return "";

	while (str != 0 && str[i] != '\0')
	{
		if(str[i] == c)
			characterIndex = (characterIndex == -1) ? i : characterIndex;
		i++;
	}

	return characterIndex == -1 ? NULL : str + characterIndex;
}
