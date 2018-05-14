/*
*	Adam Gincel
*	my_strdup.c
*	Takes a string and duplicates it, returning a pointer to the newly allocated string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strdup(char *str)
{
	char *strNew, *empty = "";
	int lenSrc = my_strlen(str), i;

	if(str == NULL)
		return NULL;
	else if(str == empty)
	{
		strNew = malloc(sizeof(char)*1);
		strNew[0] = '\0';
		return strNew;
	}

	if(lenSrc < 0)
		lenSrc = 0;
	strNew = (char *)malloc(sizeof(char)*(lenSrc + 1));

	for(i = 0; i < lenSrc; i++)
		strNew[i] = str[i];
	strNew[i] = '\0';

	return strNew;
}