#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HW_linkedListFuncs.h"
#include "HW_radixSort.h"
#include "HW_circleLinkedList.h"
#define len(arr) sizeof(arr)/sizeod(arr[0])
#define SIZE 10

void radixImplementation()
{
    tailLinkedList* list = initTailLinkedList();

    for (int i = 0; i < 10; i++)
    {
        addTailLinkedList(list, rand());
    }
    printf("\nthe list before the sort: \n");
    printList(list->head);
    
    printf("\nafter:  \n");
    printList(radixSort(list, 10)->head);

}

void queueImplementation()
{
    node* q = initCircleLinkedList();

    // enqueue(&q, 10);
    isQueueEmpty(q) ? printf("queue is empty"):printf("queue is not empty");

    for (int i = 0; i < 6; i++) enqueue(&q, rand());
    
    while (!isQueueEmpty(q)) printf("\n%d", dequeue(&q));
}

void linkedListFuncsImplementation()
{
    // uncomment if you want to check anything

    node* head = initlinkedList();
    for (int i = 0; i < 6; i++) nodeAddLinkedList(&head, rand());

    printList(head);

    int x = 14;
    // 1) 
    // (isInList(head, x) == 1) ? printf("is in list") : printf("not in list");
    
    // 2) if x not in list then NULL error
    // node* firstInstance = getDataLinkedList(head, x);
    // printf("\n%d", firstInstance->data);

    // 3) 
    // for (int i = 0; i < 5; i++) nodeAddLinkedList(&head, x);
    // printList(head);
    // printf("%d", countAmountInLinkedList(head, x));

    // 4)
    // nodeAddLinkedList(&head, x);
    // delDataLinkedList(&head, x);
    // printList(head);

    // 5)
    // nodeAddLinkedList(&head, x);
    // printList(head);
    // delLastDataLinkedList(&head, x);
    // printList(head);

    // 6)
    // for (int i = 0; i < 5; i++) nodeAddLinkedList(&head, x);
    // printList(head);
    // delAllInstances(&head, x);
    // printList(head);

    // 7)
    // node* newHead = copyLinkedList(head);
    // printList(newHead);

    // 8) 
    // node* newHead = copyLinkedListRecursive(head);
    // printList(newHead);

}

// int arrayNumCheck(int arr1[], int arr2[])
// {   
//     node* head = initlinkedList();

//     for (int i = 0; i < SIZE ; i++) nodeAddLinkedList(&head, arr2[i]);

//     for (int i = 0; i < SIZE ; i++)
//     {
        
        
//     }
    
// }

// driver code
int main()
{
    
    
    
    // radix sort
    radixImplementation();

    // circle Linked List as Queue
    // queueImplementation();

    // linked list funcs
    // linkedListFuncsImplementation();


    // for exe file
    system("pause");
    return 0;
}
