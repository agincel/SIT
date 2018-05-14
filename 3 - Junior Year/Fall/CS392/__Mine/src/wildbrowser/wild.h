#ifndef WILD_H_
#define WILD_H_

/* so many libraries lmao */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <curses.h>
#include <signal.h>
#include "my.h"

char *pageNotFound();
char *openingPage();

static inline void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int my_modified_strcmp(char *page, char *tagName);
int tagType(char *page);

int printTag(char *page, int tag);
void printWebpage(char *page);

char *webRequest(char *request);
char *getHostName(char *request);
char *getQuery(char *request);

#endif /* WILD_H_ */