#include "mylist.h"

void print_char(struct s_node* node)
{
	assert(node != NULL);
	if(node != NULL)
	{
		char returner = (char)*(char *)(node->elem);
		my_char(returner);
	}
}