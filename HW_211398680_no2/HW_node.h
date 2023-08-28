#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef NODE
#define NODE

typedef struct node
{
    int data;
    struct node* next;
}node;

node newStNode(int data)
{
    node n;
    n.data = data;
    n.next = NULL;
    return n;
}

node* newNode(int data)
{
    node* n = malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    return n;
}

#endif