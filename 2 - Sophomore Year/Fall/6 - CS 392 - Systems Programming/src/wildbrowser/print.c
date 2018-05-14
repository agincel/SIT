#include "wild.h"
#include <curses.h>

int printTag(char *page, int tag) /* returns length of <tag>text</tag> to skip */
{
	int i = 0, recursiveTag, singleLine = 0, currentX = 0, currentY = 0;
	int printingTag = 1;

	while(page[i] != '>')
		i++;
	
	i++;

	/* tag specific things here */
	if(tag == 0) /* title */
	{
		addstr("Title: ");
		//my_str("Title: ");
	}
	else if(tag == 10) /* keep parsing */
		return i;

	while(printingTag == 1)
	{
		while(page[i] != '<')
		{
			if(tag >= 0 && page[i] != '>' && page[i] != '\n') /* hacky solution to printing extra > */
			{
				addch(page[i]);
				//write(0, &page[i], 1);
			}
			i++;
		}

		if(page[i + 1] == '/') /* assume web developers are not stupid */
			printingTag = 0;
		else
		{
			recursiveTag = tagType(&page[i]);
			if(recursiveTag >= 0)
			{
				i += printTag(&page[i], recursiveTag);
				i++;
				printingTag = 0;
			}
			else
			{
				while(page[i] != '<')
					i++;
				while(page[i] != '>')
					i++;
			}

		}
	}

	getyx(stdscr, currentY, currentX);
	if(tag >= 0)
	{
		move(currentY + 1, 0);
		//my_char('\n');
	}

	while(page[i] != '>')
		i++;
	return ++i;
}

void printWebpage(char *page)
{
	int i, currentTag, jump;

	clear();

	for(i = 0; i < strlen(page); i++)
	{
		while(page[i] == '<' && page[i + 1] != '/')
		{
			currentTag = tagType(&page[i]);
			jump = printTag(&page[i], currentTag);
			i += jump;
		}
	}
}