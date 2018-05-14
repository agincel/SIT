#include "mylist.h"

void add_node(struct s_node* node, struct s_node** head)
{
	assert(node != NULL && head != NULL && node->elem != NULL);
	if(node != NULL && head != NULL && node->elem != NULL)
	{
		if(*head != NULL) /* if there already is a head */
		{
			node->prev = (*head)->prev;
			node->next = *head;

			if((*head)->prev != NULL)
				(*head)->prev->next = node;

			(*head)->prev = node; /* make current head's prev point to given node, then set head to node */
			*head = node;
		}
		else
		{
			*head = node;
			node->prev = NULL;
			node->next = NULL;
		}
	}
}