#include "mylist.h"


void nullTest()
{
	my_str("\n------------\n");
	my_str("NULL TESTS\n");
	my_str("------------\n");

	my_str("new_node(NULL, NULL, NULL)\t");
	new_node(NULL, NULL, NULL);

	my_str("Good\nadd_node(NULL, NULL)\t\t");
	add_node(NULL, NULL);

	my_str("Good\nadd_elem(NULL, NULL)\t\t");
	add_elem(NULL, NULL);

	my_str("Good\nappend(NULL, NULL)\t\t");
	append(NULL, NULL);

	my_str("Good\nadd_node_at(NULL, NULL, -1)\t");
	add_node_at(NULL, NULL, -1);

	my_str("Good\nremove_node(NULL)\t\t");
	remove_node(NULL);

	my_str("Good\nremove_last(NULL)\t\t");
	remove_last(NULL);

	my_str("Good\nremove_node_at(NULL, -1)\t");
	remove_node_at(NULL, -1);

	my_str("Good\nmy_int(count_s_nodes(NULL))\tShould print 0:\t");
	my_int(count_s_nodes(NULL));

	my_str("\nempty_list(NULL)\t\t");
	empty_list(NULL);

	my_str("Good\nnode_at(NULL, -1)\t\t");
	node_at(NULL, -1);

	my_str("Good\nelem_at(NULL, -1)\t\t");
	elem_at(NULL, -1);

	my_str("Good\nprint_int(NULL)\t\t\t");
	print_int(NULL);

	my_str("Good\nprint_char(NULL)\t\t");
	print_char(NULL);

	my_str("Good\nprint_string(NULL)\t\t");
	print_string(NULL);

	my_str("Good\ntraverse_int(NULL)\t\t");
	traverse_int(NULL);

	my_str("Good\ntraverse_char(NULL)\t\t");
	traverse_char(NULL);

	my_str("Good\ntraverse_string(NULL)\t\t");
	traverse_string(NULL);

	my_str("Good\ndebug_int(NULL)\t\t\t");
	debug_int(NULL);

	my_str("Good\ndebug_char(NULL)\t\t");
	debug_char(NULL);

	my_str("Good\ndebug_string(NULL)\t\t");
	debug_string(NULL);
	my_str("Good\n");
}

void emptyListTests()
{
	struct s_node *head = NULL;
	struct s_node *node1 = new_node("Node1", NULL, NULL);

	my_str("\n------------------------\n");
	my_str("EMPTY LIST TESTS\n(assumes remove_node works)\n");
	my_str("head starts NULL, cleared after each method that adds things\n");
	my_str("node1 = new_node(\"Node1\", NULL, NULL)\n");
	my_str("------------------------\n");

	my_str("add_node(node1, &head)\t\t\t\t");
	add_node(node1, &head);
	remove_node(&head);

	my_str("Good\nadd_elem(string, &head)\t\t\t\t");
	add_elem("derp", &head);
	remove_node(&head);

	my_str("Good\nappend(node1, &head)\t\t\t\t");
	node1 = new_node("Node1", NULL, NULL);
	append(node1, &head);
	remove_node(&head);

	my_str("Good\nadd_node_at(node1, &head, 1)\t\t\t");
	add_node_at(node1, &head, 1);
	remove_node(&head);

	my_str("Good\nremove_node(&head (already empty))\t\t");
	remove_node(&head);

	my_str("Good\nremove_last(&head (already empty))\t\t");
	remove_last(&head);

	my_str("Good\nremove_node_at(&head (already empty), 1)\t");
	remove_node_at(&head, 1);

	my_str("Good\nmy_int(count_s_nodes(&head))\t\t\tShould print 0:\t");
	my_int(count_s_nodes(head));

	my_str("\nempty_list(&head (already empty))\t\t");
	empty_list(&head);

	my_str("Good\nnode_at(head, 0)\t\t\t\t");
	node_at(head, 0);

	my_str("Good\nelem_at(head, -1)\t\t\t\t");
	elem_at(head, -1);

	my_str("Good\nprint_int(head)\t\t\t\t\t");
	print_int(head);

	my_str("Good\nprint_char(head)\t\t\t\t");
	print_char(head);

	my_str("Good\nprint_string(head)\t\t\t\t");
	print_string(head);

	my_str("Good\ntraverse_int(head)\t\t\t\t");
	traverse_int(head);

	my_str("Good\ntraverse_char(head)\t\t\t\t");
	traverse_char(head);

	my_str("Good\ntraverse_string(head)\t\t\t\t");
	traverse_string(NULL);

	my_str("Good\ndebug_int(head)\t\t\t\t\t");
	debug_int(head);

	my_str("Good\ndebug_char(head)\t\t\t\t");
	debug_char(head);

	my_str("Good\ndebug_string(head)\t\t\t\t");
	debug_string(head);
	my_str("Good\n");
}

void remainingTests()
{
	my_str("\n---------------\n");
	my_str("Remaining Tests\n");
	my_str("---------------\n");

	struct s_node *head = NULL;

	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("add_node() tests:");
	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("add_node(new_node(\"Node1\", NULL, NULL), &head)\t\t\t");
	add_node(new_node("Node1", NULL, NULL), &head);
	my_str("Good\n");

	my_str("add_node(new_node(\"Node2\", NULL, NULL), &head)\t\t\t");
	add_node(new_node("Node2", NULL, NULL), &head);
	my_str("Good\n");

	struct s_node *lol = node_at(head, 1);

	my_str("\nThis next one is using add_node on a node that isn't the head. Might break:\n");
	my_str("add_node(new_node(\"Node3\", NULL, NULL), &(node_at(head, 1))))\t");
	add_node(new_node("Node3", NULL, NULL), &lol);
	traverse_string(head);
	my_char('\n');


	my_str("add_node(NULL, &head)\t\t\t\t\t\t");
	add_node(NULL, &head);
	my_str("Good\n");

	my_str("add_node(new_node(\"Node1\", NULL, NULL), NULL)\t\t\t");
	add_node(new_node("Node1", NULL, NULL), NULL);
	my_str("Good\n\n");

	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("add_elem() tests:");
	my_str("\n~~~~~~~~~~~~~~~\n");

	my_str("add_elem(\"Elem3\", &head)\t\t\t\t");
	add_elem("Elem3", &head);
	my_str("Good\n");

	my_str("add_elem(NULL, &head)\t\t\t\t\t");
	add_elem(NULL, &head);
	my_str("Good\n");

	my_str("Traversing String: should print Elem3 Node2 Node3 Node 1\n");
	traverse_string(head);
	my_char('\n');

	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("remove_node() tests.");
	my_str("\n~~~~~~~~~~~~~~~\n");

	my_str("remove_node(&head)\t\t\t\t\t");
	remove_node(&head);
	my_str("Good\n");

	my_str("Traversing string.\t\t\t\t\t");
	traverse_string(head);
	my_char('\n');

	my_str("remove_node(&head)\t\t\t\t\t");
	remove_node(&head);
	my_str("Good\n");

	my_str("Traversing string.\t\t\t\t\t");
	traverse_string(head);
	my_char('\n');

	my_str("remove_node(&head)\t\t\t\t\t");
	remove_node(&head);
	my_str("Good\n");

	my_str("Traversing string.\t\t\t\t\t");
	traverse_string(head);
	my_char('\n');

	my_str("remove_node(&head)\t\t\t\t\t");
	remove_node(&head);
	my_str("Good\n");

	my_str("Traversing string.\t\t\t\t\t");
	traverse_string(head);
	my_char('\n');

	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("append()/add_node_at() tests.");
	my_str("\n~~~~~~~~~~~~~~~\n");

	my_str("append(new_node(\"Node1\", NULL, NULL), &head)\t\t");
	append(new_node("Node1", NULL, NULL), &head);
	my_str("Good\n");

	my_str("append(new_node(\"Node2\", NULL, NULL), &head)\t\t");
	append(new_node("Node2", NULL, NULL), &head);
	my_str("Good\n");

	my_str("add_node_at(new_node(\"Node3\", NULL, NULL), &head, 1)\t");
	add_node_at(new_node("Node3", NULL, NULL), &head, 1);
	my_str("Good\n");

	my_str("Traversing string. Should be Node1 Node3 Node2\t\t");
	traverse_string(head);
	my_char('\n');


	lol = node_at(head, 1);
	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("remove_node()/remove_node_at() tests.");
	my_str("\n~~~~~~~~~~~~~~~\n");

	my_str("Calling remove_node() with node at index 1\t\t");
	remove_node(&lol);
	my_str("Good.\n");

	my_str("Traversing. Should be Node1 Node2\t\t\t");
	traverse_string(head);
	my_char('\n');

	my_str("remove_node_at(&head, 1), prints Node1\t\t\t");
	remove_node_at(&head, 1);
	traverse_string(head);
	my_char('\n');

	my_str("remove_node_at(&head, 1), prints nothing\t\t\t");
	remove_node_at(&head, 1);
	traverse_string(head);	
	my_char('\n');

	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("count_s_nodes()/node_at() tests.");
	my_str("\n~~~~~~~~~~~~~~~\n");

	my_str("Should print Node1 Node2 Node3 Node4:\t\t\t");
	add_node_at(new_node("Node3", NULL, NULL), &head, -1);
	add_node_at(new_node("Node1", NULL, NULL), &head, -1);
	add_node_at(new_node("Node2", NULL, NULL), &head, 1);
	add_node_at(new_node("Node4", NULL, NULL), &head, 15);
	traverse_string(head);
	my_char('\n');

	my_str("count_s_nodes(head), should print 4:\t\t\t");
	my_int(count_s_nodes(head));
	my_char('\n');

	my_str("Should print Nodes... 1, 1, 2, 3, 4, 4\t\t\t");
	print_string(node_at(head, -1));
	my_char(' ');
	print_string(node_at(head, 0));
	my_char(' ');
	print_string(node_at(head, 1));
	my_char(' ');
	print_string(node_at(head, 2));
	my_char(' ');
	print_string(node_at(head, 3));
	my_char(' ');
	print_string(node_at(head, 10));
	my_char('\n');

	my_str("empty_list(&head), should print nothing:\t\t\t");
	empty_list(&head);
	traverse_string(head);
	my_char('\n');

	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("elem_at() test");
	my_str("\n~~~~~~~~~~~~~~~\n");

	add_elem("Elem1", &head);
	my_str("elem_at(head, 0), should print Elem1:\t\t\t");
	my_str(elem_at(head, 0));
	my_char('\n');

	empty_list(&head);

	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("traverse_char/int tests.");
	my_str("\n~~~~~~~~~~~~~~~\n");

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	add_elem(&d, &head);
	add_elem(&c, &head);
	add_elem(&b, &head);
	add_elem(&a, &head);
	my_str("traverse_int(head), should print 1 2 3 4:\t\t");
	traverse_int(head);
	my_char('\n');

	empty_list(&head);

	char e = 'a', f = 'b', g = 'c', h = 'd';
	add_elem(&h, &head);
	add_elem(&g, &head);
	add_elem(&f, &head);
	add_elem(&e, &head);
	my_str("traverse_char(head), should bring a b c d:\t\t");
	traverse_char(head);
	my_char('\n');


	my_str("\n~~~~~~~~~~~~~~~\n");
	my_str("debug method tests");
	my_str("\n~~~~~~~~~~~~~~~\n");

	my_str("Running debug_char on (a b c d):\n");
	debug_char(head);
	my_char('\n');

	empty_list(&head);
	add_elem(&d, &head);
	add_elem(&c, &head);
	add_elem(&b, &head);
	add_elem(&a, &head);

	my_str("Running debug_int on (1 2 3 4):\n");
	debug_int(head);
	my_char('\n');

	empty_list(&head);
	add_node_at(new_node("Node3", NULL, NULL), &head, -1);
	add_node_at(new_node("Node1", NULL, NULL), &head, -1);
	add_node_at(new_node("Node2", NULL, NULL), &head, 1);
	add_node_at(new_node("Node4", NULL, NULL), &head, 15);
	my_str("Running debug_string on (Node1 Node2 Node3 Node4)\n");
	debug_string(head);
	my_char('\n');
	my_char('\n');
	my_str("You did it! No segfaults! :D\n\n");

}


int main(int argc, char const *argv[])
{
	/* first tests: sending NULL everywhere */
	nullTest();

	/* second tests: sending empty list everywhere */
	emptyListTests();

	remainingTests();

	return 0;
}