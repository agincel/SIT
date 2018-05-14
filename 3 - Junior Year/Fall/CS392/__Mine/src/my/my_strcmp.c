/*
*	Adam Gincel
*	my_strcmp.c
*	Compares two strings lexicographically.	
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

int my_strcmp(char *strA, char *strB)
{
	int lenA = my_strlen(strA), lenB = my_strlen(strB), i, result = 0;

	if(strA == 0 || strB == 0) /* 0 if both, -1 if a is null, 1 if b is null */
		return strA == 0 && strB == 0 ? 0 : strA == 0 ? -1 : 1; 

	for(i = 0; result == 0 && i < lenA && i < lenB; i++)
		result = strA[i] < strB[i] ? -1 : strA[i] == strB[i] ? 0 : 1;
	

	if(result == 0)
		result = lenA < lenB ? -1 : lenA == lenB ? 0 : 1; 

	return result;
}
