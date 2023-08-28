#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HW_node.h"
#ifndef CIRCLELINKEDLIST
#define CIRCLELINKEDLIST

node* initCircleLinkedList()
{
    node* n = malloc(sizeof(node));
    n = NULL;
    return n;
}

node* initQueue()
{
    return initCircleLinkedList();
}

void nodeAddCircleLinkedList(node** headRef, int data)
{
    node* p = newNode(data);

    if (*headRef != NULL){
        node* t = *headRef;
        while(t->next != NULL) t = t->next;
        t->next = p;
    }else{
        *headRef = p;
    }
}

int isQueueEmpty(node* q) {
    return q == NULL;
}

void enqueue(node** q, int data)
{
    node* p = newNode(data);
    
    if (!isQueueEmpty(*q))
    {
        node* tmp = (*q)->next;
        (*q)->next = p;
        (*q) = p;
        p->next = tmp;
    }else
    {
        (*q) = p;
        p->next = p;
    }
}

int dequeue(node** q)
{
    if (isQueueEmpty(*q)) return -1;
    
    node* tmp = (*q)->next;
    int data = tmp->data;
    if ((*q)->next != (*q))
    {
        (*q)->next = (*q)->next->next;
        free(tmp);
        return data;
    }else
    {
        (*q) = NULL;
    }
    free(tmp);
    return data;
}

#endif