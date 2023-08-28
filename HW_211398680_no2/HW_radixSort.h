#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HW_tailLinkedList.h"
#ifndef SORTS
#define SORTS

int findDigs(int i)
{
    int count = 0;
    while (i != 0)
    {
        count++;
        i = i/10;
    }
    return count;
    
}

tailLinkedList* radixSort(tailLinkedList* list, int b)
{
    tailLinkedList* arr[b];
    
    int maxDig = findDigs(findMaxInLinkedList(list->head));
    int d = maxDig;
    while (maxDig > 0)
    {
        for (int i = 0; i < b; i++) arr[i] = initTailLinkedList();
        
        node* t = list->head;
        int p = (int)(pow(b,d-maxDig+1)); 
        while(t != NULL)
        {
            int temp = t->data % p;
            int sorter = (temp - (temp % (p/b)))/(p/b);

            addTailLinkedList(arr[sorter],t->data);

            t = t->next;
        }

        for (int i = 0, k = 0; i < b; i++)
        {   
            if (arr[i]->head != NULL )
            {
                arr[k]->tail->next = arr[i]->head;
                k=i;
            }
        }
        list->head = arr[0]->head;
        list->tail = arr[b]->tail;
        /*
        uncomment this if you want to see the steps!
        */
        printf("%d) %*s", p/b, maxDig, "");
        printList(list->head);
        maxDig--;
    }
    return list;
}


#endif