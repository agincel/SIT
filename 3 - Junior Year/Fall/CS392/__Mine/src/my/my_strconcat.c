/*
*	Adam Gincel
*	my_strconcat.c
*	Allocates a new string, combining strA and strB into it.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strconcat(char *strA, char *strB)
{
	int lenA = my_strlen(strA), lenB = my_strlen(strB), newLen = lenA + lenB - 1, i, j;

	char *strNew = (char *)malloc(sizeof(char) * newLen);

	for(i = 0; i < lenA; i++)
		strNew[i] = strA[i];

	for(j = 0; j < lenB; j++, i++)
		strNew[i] = strB[j];

	strNew[i] = '\0';
	return strNew;
}