/*
*	Adam Gincel
*	my_strcat.c
*	Appends a string B onto string A, assuming A has enough room for the concatenation.	
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_strcat(char *strA, char *strB)
{
	int i = 0, j = 0;

	if(strA == NULL)
		return NULL;
	else if(strB == NULL)
		return strA;

	while(strA[i] != '\0')
		i++;
	/* i now equals the index after visible characters in A */

	for(j = 0; strB[j] != '\0'; i++, j++)
		strA[i] = strB[j];
	strA[i] = '\0'; /* add null terminator to end */

	return strA;
}