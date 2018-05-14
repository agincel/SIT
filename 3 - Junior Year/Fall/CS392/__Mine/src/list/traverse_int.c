#include "mylist.h"

void traverse_int(struct s_node* head)
{
	assert(head != NULL);
	if(head != NULL)
	{
		while(head != NULL)
		{
			print_int(head);
			my_char(' ');
			head = head->next;
		}
	}
}