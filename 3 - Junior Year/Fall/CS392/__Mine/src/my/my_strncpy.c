/*
*	Adam Gincel
*	my_strncpy.c
*	Copies the first n characters of string B into string A.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strncpy(char *strA, char *strB, int n)
{
	/*handle overlapping strings by making a copy of string B*/
	char *strSrc = my_strdup(strB);
	int lenSrc = my_strlen(strSrc), i;

	if(strA == NULL)
		return NULL;
	else if(strB == NULL)
		return strA;
	else if(n <= 0)
		return strA;

	if(lenSrc > n)
		lenSrc = n < 0 ? 0 : n;

	for(i = 0; i < lenSrc; i++)
		strA[i] = strSrc[i];
	strA[i] = '\0';

	free(strSrc);
	return strA;
}
