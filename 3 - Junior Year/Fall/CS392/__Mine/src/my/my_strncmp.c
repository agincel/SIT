/*
*	Adam Gincel
*	my_strncmp.c
*	Compares strA and strB lexicographically, up to the first n characters.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

int my_strncmp(char *strA, char *strB, int n)
{
	int lenA = my_strlen(strA), lenB = my_strlen(strB), i, result = 0;

	lenA = lenA > n ? (n < 0 ? 0 : n) : lenA;
	lenB = lenB > n ? (n < 0 ? 0 : n) : lenB; /*limit lengths to n */

	if(strA == 0 || strB == 0) /* 0 if both, -1 if a is null, 1 if b is null */
		return strA == 0 && strB == 0 ? 0 : strA == 0 ? -1 : 1; 
	else if(n <= 0)
		return 0;

	for(i = 0; result == 0 && i < lenA && i < lenB; i++)
		result = strA[i] < strB[i] ? -1 : strA[i] == strB[i] ? 0 : 1;

	if(result == 0)
		result = lenA < lenB ? -1 : lenA == lenB ? 0 : 1; 

	return result;
}