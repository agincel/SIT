#include "mylist.h"

void print_int(struct s_node* node)
{
	assert(node != NULL);
	if(node != NULL)
	{
		int returner = (int)*(int *)(node->elem);
		my_int(returner);
	}
}