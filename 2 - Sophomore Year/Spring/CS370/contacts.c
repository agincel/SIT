/*
    contacts.c
    Matt Gomez, Adam Gincel, Alex Massenzio

    Takes an int as a number of arguments, then adds given strings to a Radix
    Tree (aka Trie), or finds how many added words have a given prefix.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie_node
{
    int count;
    struct trie_node* next[26];
} t_node;

t_node* root = NULL;

int main()
{
    //method declarations
    int find();
    void insert();
    t_node* create_t_node();

    int numOps, i;
    char arg1[4], arg2[21]; //"add" or "find"

    scanf("%d", &numOps); //get number of operations

    for(i = 0; i < numOps; i++)
    {
      scanf("%s %s", arg1, arg2);
      if(strcmp("add", arg1) == 0) //if "add", add the second word
        insert(arg2);
      else
        printf("%d%s", find(arg2), "\n"); //otherwise, find the prefix
    }
    return 0;
}

t_node* create_t_node() //create a new node, start count at 1 because it has been reached once
{
    t_node *node = (t_node*)malloc(sizeof(t_node)); //allocate memory for the node

    for(int x = 0; x < 26; x++) //set our array of 26 children to NULL
        node->next[x] = NULL;

    node->count = 1; //set our count to 1
    return node;
}

void insert(char word[]) //insert a word, incrementing counts or adding new nodes as you go
{
    if(root == NULL)
        root = create_t_node(); //root needs to get created if we haven't added anything

    int length = strlen(word), index, depth;
    t_node *node = root;

    for(depth = 0; depth < length; depth++)
    {
        index = word[depth] - 'a';

        if(node->next[index] == NULL) //if the next letter has never been reached, create a node with count 1
            node->next[index] = create_t_node();
        else
            node->next[index]->count += 1; //otherwise, it has been reached before, increment it

        node = node->next[index];
    }
}

int find(char word[]) //return how many added words have a given prefix
{
    if(root == NULL) //if we haven't added anything, the prefix definitely isn't there
        return 0;

    int length = strlen(word), depth, index;
    t_node *node = root;

    for(depth = 0; depth < length; depth++) 
    {
        index = word[depth] - 'a';
        if(node->next[index] != NULL) //if there is the next letter, go to it
            node = node->next[index];
        else
            break;
    }

    if(word[depth] == '\0') //we made it to the end of the word with a valid node
        return node->count; //return its count

    return 0; //we reached a NULL node before the end of the prefix, it wasn't found
}
