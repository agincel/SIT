/*
*	Adam Gincel
*	my_str2vect.c
*	Breaks up a string by spaces and inserts each word into an array index.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

char **my_str2vect(char* str)
{
	char **returner;
	int i = 0, lenArrayIndex = -1, returnerIndex = -1, k = 0, numWords = 0, *lenArray;
	char *empty = "";

	if(str == NULL)
		return NULL;
	else if(str == empty)
	{
		returner = (char **)malloc(sizeof(char *)*1);
		returner[0] = (char *)malloc(sizeof(char)*1);
		returner[0][0] = '\0';
		return returner;
	}


	while(str[i] != '\0') /* learn total number of words */
	{
		while(str[i] == ' ' && str[i] != '\0')
			i++;
			
		if(str[i] != '\0')
			numWords++;

		while(str[i] != ' ' && str[i] != '\0')
			i++;
	}

	lenArray = (int *)malloc(sizeof(int)*numWords); /* instantiate array of lengths */
	for(i = 0; i < numWords; i++)
		lenArray[i] = 0;

	i = 0;
	while(str[i] != '\0') /* Fill len array appropriately, to help malloc the Vector */
	{
		while(str[i] == ' ' && str[i] != '\0')
			i++;
			
		if(str[i] != '\0')
			lenArrayIndex++;

		while(str[i] != ' ' && str[i] != '\0')
		{
			lenArray[lenArrayIndex]++;
			i++;
		}
		lenArray[lenArrayIndex]++; /* account for null terminator */
	}

	returner = (char **)malloc(sizeof(char *)*(numWords + 1)); /* instantiate vector */
	for(i = 0; i < numWords; i++)
		returner[i] = (char *)malloc(sizeof(char)*(lenArray[i] + 1));
	returner[i] = NULL;

	i = 0;
	while(str[i] != '\0') /* Actually fill the vector */
	{
		while(str[i] == ' ' && str[i] != '\0')
			i++;
			
		if(str[i] != '\0')
			returnerIndex++;

		for(k = 0; k < lenArray[returnerIndex] - 1 && str[i] != '\0'; k++, i++) /* we know the length of the word, so just fill it in returner */
			returner[returnerIndex][k] = str[i];

		if(str[i] != '\0')
			returner[returnerIndex][k] = '\0';
	}

	free(lenArray);
	return returner;
}