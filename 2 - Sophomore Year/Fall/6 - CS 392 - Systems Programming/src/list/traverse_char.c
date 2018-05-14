#include "mylist.h"

void traverse_char(struct s_node* head)
{
	assert(head != NULL);
	if(head != NULL)
	{
		while(head != NULL)
		{
			print_char(head);
			my_char(' ');
			head = head->next;
		}
	}
}