#include "mylist.h"

void traverse_string(struct s_node* head)
{
	assert(head != NULL);
	if(head != NULL)
	{
		while(head != NULL)
		{
			print_string(head);
			my_char(' ');
			head = head->next;
		}
	}
}