#include "mylist.h"

void empty_list(struct s_node** head)
{
	while(head != NULL && *head != NULL)
		remove_last(head);
}