#include "mylist.h"

void* remove_last(struct s_node** head)
{
	struct s_node *currentNode;
	void *returner;

	assert(head != NULL && *head != NULL);

	if(head != NULL && *head != NULL)
	{
		if((*head)->next == NULL)
		{
			returner = (*head)->elem;
			free(*head);
			*head = NULL;
			return returner;
		}
		else
		{
			currentNode = *head;
			while(currentNode->next != NULL)
				currentNode = currentNode->next;
			currentNode->prev->next = NULL;
			returner = currentNode->elem;
			free(currentNode);
		
			return returner;
		}
	}
	else
		return NULL;
}