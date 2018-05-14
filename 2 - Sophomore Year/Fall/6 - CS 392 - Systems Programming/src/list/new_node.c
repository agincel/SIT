#include "mylist.h"

struct s_node* new_node(void* elemIn, struct s_node* nextIn, struct s_node* prevIn)
{
	struct s_node *returner = (struct s_node *)malloc(sizeof(struct s_node));

	returner->elem = elemIn;
	returner->next = nextIn;
	returner->prev = prevIn;

	return returner;
}