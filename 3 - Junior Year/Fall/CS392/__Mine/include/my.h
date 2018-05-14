#ifndef MY_H_
#define MY_H_

#ifndef NULL
#define NULL ((void*)0)
#endif

#include <stdlib.h>

void my_char(char); 
void my_newline(); 

void my_str(char*); 
void my_int(int); 
void my_num_base(int, char*);
void my_alpha(); 
void my_digits(); 

int my_find(char*, char); 
int my_rfind(char*, char);
int my_strlen(char*); 
int my_revstr(char*); 


char *my_strindex(char *a, char b); 
char *my_strrindex(char*a, char b); 
char *my_strcat(char *a, char *b); 
int my_strcmp(char *a, char *b); 
int my_strncmp(char*a, char *b, int n); 

char *my_strconcat(char *a, char *b); 
char *my_strnconcat(char *a, char *b, int n);
char *my_strcpy(char *a, char *b); 
char *my_strncpy(char *a, char *b, int n); 
char *my_strdup(char *x); 
char *my_vect2str(char **x); 
char **my_str2vect(char*); 

int my_atoi(char *); 

#endif /* MY_H_ */
