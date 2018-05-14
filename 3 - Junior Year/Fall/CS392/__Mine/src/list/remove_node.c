#include "mylist.h"

void* remove_node(struct s_node** head)
{
	void *returner;
	struct s_node *newHead;

	assert(head != NULL);
	
	if(head != NULL)
	{
		if(*head == NULL)
			return NULL;

		returner = (*head)->elem;
		if((*head)->next != NULL) /* if there exists a next it should become new head */
		{
			(*head)->next->prev = (*head)->prev;

			if((*head)->prev != NULL)
				(*head)->prev->next = (*head)->next;

			newHead = (*head)->next;
			free(*head); /*free head*/
			*head = newHead;
		}
		else
		{
			free(*head); /*otherwise just free head, set it to NULL */
			*head = NULL;
		}

		return returner;
	}
	else
		return NULL;

}