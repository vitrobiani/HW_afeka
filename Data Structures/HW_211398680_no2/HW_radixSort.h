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
    tailLinkedList* arr[b]; // the array we will use
    
    // finding the loop amount (d)
    int maxDig = findDigs(findMaxInLinkedList(list->head)); 
    int d = maxDig;
    while (maxDig > 0)
    {
        // initializing all the items in the array
        for (int i = 0; i < b; i++) arr[i] = initTailLinkedList();

        int p = (int)(pow(b,d-maxDig+1)); // the units (tens, thousnds etc.) 
        node* t = list->head;
        while(t != NULL)
        {
            // calculating where in the array should we put the number
            int temp = t->data % p;
            int sorter = (temp - (temp % (p/b)))/(p/b);

            addTailLinkedList(arr[sorter],t->data);

            t = t->next;
        }

        // connecting all the tails
        int i = 0, k = 0;
        while (arr[i]->head == NULL) i++;
        k = i;
        list->head = arr[k]->head;
        for (; i < b; i++)
        {   
            if (arr[i]->head != NULL && i != k)
            {
                arr[k]->tail->next = arr[i]->head;
                k=i;
            }
        }
        list->tail = arr[k]->tail;
        /*
        uncomment this if you want to see the steps!
        printf("%d) %*s", p/b, maxDig, "");
        printList(list->head);
        */
        maxDig--;
    }
    return list;
}


#endif