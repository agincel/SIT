/*
*	Adam Gincel
*	my_revstr.c
*	Prints out the reverse of the given string, then returns the string's length.
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

int my_revstr(char* str)
{
	int leftIndex = 0, rightIndex = my_strlen(str) - 1;
	char temp;
	if(str == 0)
		return -1;

	while(leftIndex < rightIndex)
	{
		temp = str[rightIndex];
		str[rightIndex] = str[leftIndex];
		str[leftIndex] = temp;
		leftIndex++;
		rightIndex--;
	}
	return my_strlen(str);
}
