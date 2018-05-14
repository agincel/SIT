#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "my.h"

int MY_COL_LEN = 30;

void printOptions(int numOptions, char *options[], int selected, int *choices, int termRows, int termCols)
{
    int row = 0, col = 0, i = 0, j = 0;

    clear();

    for (i = 1; i < numOptions; i++) /* print menu options */
    {
        if (choices[i] > 0) /* menu item highlighted */
            attron(A_STANDOUT);
        else
            attroff(A_STANDOUT);

        if (i == selected) /*underline if selected*/
            attron(A_UNDERLINE);
        else
            attroff(A_UNDERLINE);

        for(j = 0; j < MY_COL_LEN - 1 && options[i][j] != '\0' && (col + MY_COL_LEN < termCols); j++)
        {
            addch(options[i][j]);
        }

        /* handle row/col stuff*/
        row++;
        if (row == termRows) /*reached bottom*/
        {
            row = 0;
            col += MY_COL_LEN;
            if (col + MY_COL_LEN >= termCols)
            {
                clear();
                move(0, 0);
                attroff(A_STANDOUT);
                attroff(A_UNDERLINE);
                addstr("Screen too small!");
            }
        }
        move(row, col);
    }
}

static void finish(int sig)
{
    endwin();
    if (sig == 1)
        my_str("USAGE: ./selector [items to select]\n");

    exit(0);
}

static void noquit(int sig)
{
    my_char('\0');
}

int main(int argc, char *argv[])
{
    int row = 0, i = 1, selected = 1, previouslySelected = 0, inKey = 0, termRows = 0, termCols = 0;
    if (argc <= 1)
        finish(1);

    int *choices = (int *)malloc(sizeof(int) * argc);
    for(i = 0; i < argc; i++)
        choices[i] = 0;

    signal(SIGINT, noquit);      /* ctrl-C cannot quit */

    initscr();              /* initialize the curses screen */
    keypad(stdscr, TRUE);   /* enable keyboard */
    raw();
    nonl();                 
    cbreak();               /* take input chars one at a time */
    noecho();               /* do not echo input */
    curs_set(0);            /* hide cursor */

    while(1)
    {
        getmaxyx(stdscr, termRows, termCols); /* update rows and columns */
        printOptions(argc, argv, selected, choices, termRows, termCols); /* print menu */

        /* keyboard input */
        inKey = getch();
        if(inKey == KEY_DOWN || inKey == KEY_UP) /* change rows */
        {
            if (inKey == KEY_DOWN)
                selected++;
            else
                selected--;

            /*handle vertical wrapping*/

            if(selected < 1)
            {
                selected = argc - 1;
            }else if(selected >= argc) 
            {
                selected = 1;
            }
        }
        else if(inKey == KEY_LEFT || inKey == KEY_RIGHT) /* change column */
        {
            previouslySelected = selected;
            if(inKey == KEY_LEFT)
                selected -= termRows;
            else
                selected += termRows;

            if(selected < 1 || selected >= argc)
                selected = previouslySelected;
        }
        else if(inKey == ' ') /* select option with spacebar */
        {
            if(choices[selected] == 0)
            {
                choices[selected] = 1;
                selected++;
                if(selected >= argc) 
                {
                    selected = 1;
                }
            }
            else
                choices[selected] = 0;
        }
        else if(inKey == 13 || inKey == '\n') /* hit enter */
        {
            endwin();
            for (i = 0; i < argc; i++)
            {
                if(choices[i] > 0) /* choice was selected */
                {
                    my_str(argv[i]); /* print it then a space */
                    my_char(' ');
                }
            }
            my_char('\n');
            exit(0);
        }
        else if(inKey == 27) /* hit escape, found via testing on linux lab and has a second delay */
        {
            finish(0);
        }
    }

    finish(0);
}