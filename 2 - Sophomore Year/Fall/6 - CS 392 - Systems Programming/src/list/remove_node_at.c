#include "mylist.h"

void* remove_node_at(struct s_node** head, int n)
{
	int i = 0;
	struct s_node *currentNode;
	void *returner;

	assert(head != NULL && n >= 0 && n < count_s_nodes(*head));
	
	if(head != NULL)
	{
		if(*head == NULL || n <= 0)
			return remove_node(head);
		else if(n >= count_s_nodes(*head))
			return remove_last(head);
		else
		{

			currentNode = *head;
			for(i = 0; i < n && currentNode->next != NULL; i++)
				currentNode = currentNode->next;

			/* currentNode is now in location where new node needs to be */
			currentNode->prev->next = currentNode->next;
			if(currentNode->next != NULL) /* if there exists a next change its prev to our prev */
				currentNode->next->prev = currentNode->prev;

			returner = currentNode->elem;	
			free(currentNode);
			return returner;
		}
	}
	else
		return NULL;
}