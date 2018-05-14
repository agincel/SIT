#include "wild.h"
#include <curses.h>

int state = 0; /* 0 = address bar, 1 = viewing page */
char *addressBar;
char *displayingPage;

void toquit()
{
	echo();
	endwin();
	exit(0);
}

int main(int argc, char *argv[])
{
	int i = 0, ch = 0, currentY, currentX;
	addressBar = (char *)malloc(sizeof(char) * 4096);

	signal(SIGINT, toquit);

    initscr();              /* initialize the curses screen */
    keypad(stdscr, TRUE);   /* enable keyboard */
    raw();
    nonl();                 
    cbreak();               /* take input chars one at a time */
    noecho();               /* do not echo input */
    curs_set(0);            /* hide cursor */
    scrollok(stdscr, TRUE);
	noecho();

	state = 0;
	displayingPage = openingPage();
	my_str(displayingPage);
	printWebpage(displayingPage);
	ch = getch();
	clear();
	addstr("Type an address, then press enter:");
	move(1, 0);


	while(1)
	{
		if(state == 0) /* address bar */
		{
			ch = getch();
			if(ch == 13) /* enter, try to go to page */
			{
				state = 1;
				displayingPage = webRequest(addressBar);
			}
			else if(ch == KEY_BACKSPACE) /* backspace */
			{
				getyx(stdscr, currentY, currentX);
				move(currentY, currentX - 1);
				addch(' ');
				move(currentY, currentX - 1);
				if(i > 0)
					i--;
				addressBar[i] = '\0';
			}
			else
			{
				addch(ch);
				addressBar[i] = ch;
				i++;
			}
		}
		else if(state == 1)
		{
			printWebpage(displayingPage);
			ch = getch();

			if(ch == 13) /* enter */
			{
				state = 0;
				clear();
				addstr("Type an address, then press enter:");
				move(1, 0);
				free(addressBar);
				addressBar = (char *)malloc(sizeof(char) * 4096);
				bzero(addressBar, 4096);
				i = 0;
			}
		}

		
	}


	printWebpage(webRequest(argv[1]));
	echo();
	endwin();
	exit(0);
}
