#include "mylist.h"

void print_string(struct s_node* node)
{
	assert(node != NULL);
	if(node != NULL)
	{
		char *printing = (char *)node->elem;
		my_str(printing);
	}
}