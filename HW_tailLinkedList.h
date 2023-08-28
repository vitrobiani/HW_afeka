#include <stdio.h>
#include <stdlib.h>
#include "HW_node.h"
#ifndef TAILLINKEDLIST
#define TAILLINKEDLIST

typedef struct tailLinkedList
{
    node* head;
    node* tail;
}tailLinkedList;

tailLinkedList* initTailLinkedList()
{
    tailLinkedList* linkedList = malloc(sizeof(tailLinkedList));
    linkedList->head = NULL;
    linkedList->tail = NULL;
    return linkedList;
}

void addTailLinkedList(tailLinkedList* linkedList, int data)
{
    node* p = newNode(data);
    
    if (linkedList->head != NULL)
    {
        linkedList->tail->next = p;
        linkedList->tail = p;
    }else
    {
        linkedList->head = p;
        linkedList->tail = p;
    }
}
#endif