/*
*	Adam Gincel
*	my_strconcat.c
*	Allocates a new string, combining strA and the first n characters of strB into it.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strnconcat(char *strA, char *strB, int n)
{
	int lenA = my_strlen(strA), lenB = my_strlen(strB), newLen, i, j;
	char *strNew;

	if(lenB > n) 
		lenB = n >= 0 ? n : 0;

	newLen = lenA + lenB - 1;

	strNew = (char *)malloc(sizeof(char) * newLen);

	for(i = 0; i < lenA; i++) /* Add all of strA to strNew, except for \0 */
		strNew[i] = strA[i];

	for(j = 0; j < lenB; j++, i++) /* i is in correct index to continue through strNew, j used to iterate through strB */
		strNew[i] = strB[j];

	strNew[i] = '\0'; /* last character now needs to be \0 */
	return strNew;
}