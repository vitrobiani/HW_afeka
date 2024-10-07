#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <threads.h>
#include <string.h>


#define TABLE_SIZE 10

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct HashSet {
    Node** table;
} HashSet;

// Function to create a new hash set
HashSet* createHashSet() {
    HashSet* set = malloc(sizeof(HashSet));
    set->table = malloc(sizeof(Node*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        set->table[i] = NULL;
    }
    return set;
}

// Hash function
unsigned int hash(int value) {
    return value % TABLE_SIZE;
}

// Function to add an element to the hash set
void add(HashSet* set, int value) {
    unsigned int index = hash(value);
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    // Check if the value already exists
    Node* current = set->table[index];
    while (current != NULL) {
        if (current->value == value) {
            free(newNode); // Free the new node if value already exists
            return;
        }
        current = current->next;
    }

    // Insert the new node at the beginning of the chain
    newNode->next = set->table[index];
    set->table[index] = newNode;
}

// Function to check if an element exists in the hash set
int contains(HashSet* set, int value) {
    unsigned int index = hash(value);
    Node* current = set->table[index];
    while (current != NULL) {
        if (current->value == value) {
            return 1; // Value exists
        }
        current = current->next;
    }
    return 0; // Value does not exist
}

// Function to remove an element from the hash set
void removeValue(HashSet* set, int value) {
    unsigned int index = hash(value);
    Node* current = set->table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (current->value == value) {
            if (prev == NULL) {
                set->table[index] = current->next; // Remove head
            } else {
                prev->next = current->next; // Bypass the node
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to free the hash set
void freeHashSet(HashSet* set) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = set->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(set->table);
    free(set);
}

void printHashSet(HashSet* set) {
    printf("HashSet contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = set->table[i];
        if (current) {
            printf("Bucket %d: ", i);
            while (current != NULL) {
                printf("%d ", current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}


int main() {
    HashSet *set = createHashSet();
    for (int i = 0; i < 100; i++) {
        int pid = fork();
        add(set, pid);
        switch (pid) { /* Parent and child share mapping */
            case -1:
                exit(-1);

            case 0: /* Child: increment shared integer and exit */
                exit(EXIT_SUCCESS);
        }
    }
    while (wait(NULL) != -1);

    printHashSet(set);
    return 0;
}
