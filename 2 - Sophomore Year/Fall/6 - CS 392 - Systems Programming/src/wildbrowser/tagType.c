#include "wild.h"

int my_modified_strcmp(char *page, char *tagName)
{
	int i;
	for(i = 0; i < strlen(tagName); i++)
	{
		if(page[i] == '\0' || page[i] != tagName[i])
			return 0;
	}

	return 1;
}

int tagType(char *page)
{
	/* we want to acknowledge:
		<title> = 0
		<p> = 1
		<b> = 2
		<strong> = 3
		<a> = 4
		ignored (for now), return -1

		To pass by a tag but parse through what's inside it, return 10? for now
	*/
	if(my_modified_strcmp(&page[1], "title"))
		return 0;
	else if(my_modified_strcmp(&page[1], "p"))
		return 1;
	else if(my_modified_strcmp(&page[1], "b"))
		return 2;
	else if(my_modified_strcmp(&page[1], "strong"))
		return 3;
	else if(my_modified_strcmp(&page[1], "a"))
		return 4;
	else if(my_modified_strcmp(&page[1], "div"))
		return 10; /* we want what's inside divs */
	else if(my_modified_strcmp(&page[1], "nav"))
		return 10;
	else
		return -1;
}