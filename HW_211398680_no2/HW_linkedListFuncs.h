#include <stdio.h>
#include <stdlib.h>
#include "HW_node.h"
#ifndef LINKEDLIST
#define LINKEDLIST

node* initlinkedList()
{
    node* n = malloc(sizeof(node));
    n = NULL;
    return n;
}

void freeList(node* head)
{
    node* p = head;
    while (p != NULL)
    {
        head = head->next;
        free(p);
        p = head;
    }   
}

void printList(node* head)
{
    node* t = head;
    if (t != NULL)
    {
        while (t->next != NULL)
        {
            printf("%d -> ", t->data);
            t = t->next;
        }
        printf("%d\n", t->data);
    }
}

void nodeAddLinkedList(node** headRef, int data)
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

void nodeInsertLinkedList(node** headRef, int data)
{
    node* p = newNode(data);
    if (*headRef != NULL)
    {
        p->next = *headRef;
        *headRef = p;    
    }else
    {
        *headRef = p;
    }
    
}

int findMaxInLinkedList(node* head)
{
    int king = head->next->data;
    node* t = head->next;
    while (t->next != NULL)
    {
        if (t->next->data > king)
        {
            king = t->next->data;
        }
        t = t->next;
    }
        return king;
    
}

void delNextNode(node** p)
{
    (*p)->next = (*p)->next->next;
}

// checks if in list
int isInList(node* head, int i)
{
    node *t = head;
    while(t != NULL)
    {
        if(t->data == i) return 1;
        t = t->next;
    }
    return 0;
}

// get a pointer to the node of the first instance 
node* getDataLinkedList(node* head, int data)
{
    node* p = head;
    while (p != NULL)
    {
        if (p->data == data) break;
        p = p->next;
    }
    // if it was found then its returning the right node
    // if not then the while loop ended and p is equal to NULL
    return p;
    
}

// count the amount if data recursively
int countAmountInLinkedList(node* head, int data)
{
    if (head == NULL) return 0;
    
    if (head->data == data)
    {
        return countAmountInLinkedList(head->next, data) + 1;
    }
    return countAmountInLinkedList(head->next, data);
}

// delete the first object in the list
void delFirstLinkedList(node** headRef)
{
    *headRef = (*headRef)->next;
}

// delete the first instance of data
void delDataLinkedList(node** headRef, int data)
{
    node* p = *headRef;
    if (p == NULL) return;
    if (p->data == data)
    {
        delFirstLinkedList(headRef);
        return;
    }
    while(p->next != NULL && p->next->data != data) p = p->next;
    if (p->next != NULL)
    {
        node* tmp = p->next;
        p->next = tmp->next;
        tmp->next = NULL;
    }
}

// delete the last instance of data
void delLastDataLinkedList(node** headRef, int data)
{
    node* p = *headRef;
    node* s = NULL;
    if (p != NULL && p->data == data) s=p;

    while(p->next != NULL)
    {
        if (p->next->data == data) s = p;
        p = p->next;
    }
    
    if (s == NULL) return;
    if (*headRef == s)
    {
        delFirstLinkedList(headRef);
        return;
    }
    delNextNode(&s);
}

void delAllInstances(node** headRef, int data)
{
    node* p = *headRef;

    while(p->next != NULL)
    {
        if (p->next->data == data)
            delNextNode(&p);
        else
            p = p->next;
    }
    
    if ((*headRef)->data == data) delFirstLinkedList(headRef);
}

node* copyLinkedList(node* head)
{
    node* newHead = initlinkedList();
    node* p = head;

    while (p != NULL)
    {
        nodeAddLinkedList(&newHead, p->data);
        p = p->next;
    }
    return newHead;
    
}

void copyLinkedListRecursiveInside(node* head, node** newHeadRef)
{
    if (head == NULL)
        return;

    copyLinkedListRecursiveInside(head->next, newHeadRef);
    nodeInsertLinkedList(newHeadRef, head->data);
    return;
}

node* copyLinkedListRecursive(node* head)
{
    node* newHead = initlinkedList();
    copyLinkedListRecursiveInside(head, &newHead);
    return newHead;
} 


#endif