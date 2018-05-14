/*
*	Adam Gincel
*	my_vect2str.c
*	When given a 2D vector of strings, appends those strings connected with spaces and returns a single concatenated string.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char *my_vect2str(char **vect)
{
	int i = 0, j = 0, k = 0, lenResult = 0;
	char *result, *empty = "";

	if(vect == NULL)
		return NULL;

	while(vect[i] != NULL && vect[i] != empty) /* Iterate through vector to get needed length to malloc string */
	{
		if(vect[i] != empty)
		{
			while(vect[i][j] != '\0')
			{
				lenResult++;
				j++;
			}
		}
		j = 0;
		lenResult++;
		i++;
	}
	lenResult--;

	i = 0;
	j = 0;

	result = (char *)malloc(sizeof(char)*(lenResult + 1));

	while(vect[i] != NULL) /* iterate thorugh vector again to add characters */
	{
		if(vect[i] != empty)
		{
			while(vect[i][j] != '\0')
			{
				result[k] = vect[i][j];
				j++;
				k++;
			}
		}
		result[k++] = ' ';
		j = 0;
		i++;
	}
	result[--k] = '\0';

	return result;
}