/*
*	Adam Gincel
*	my_strcpy.c
*	Copies string B into String A.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strcpy(char *strA, char *strB)
{
	/*handle overlapping strings by making a copy of string B*/
	char *strSrc = my_strdup(strB);
	int lenSrc = my_strlen(strSrc), i;

	if(strA == NULL)
		return NULL;
	else if(strB == NULL)
		return strA;

	for(i = 0; i < lenSrc; i++)
		strA[i] = strSrc[i];
	strA[i] = '\0';

	free(strSrc);
	return strA;
}
