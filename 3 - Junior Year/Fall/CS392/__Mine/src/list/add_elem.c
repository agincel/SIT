#include "mylist.h"

void add_elem(void* elemIn, struct s_node** head)
{
	assert(elemIn != NULL && head != NULL);
	if(elemIn != NULL && head != NULL)
	{
		struct s_node* newNode = new_node(elemIn, NULL, NULL);

		add_node(newNode, head);
	}
}