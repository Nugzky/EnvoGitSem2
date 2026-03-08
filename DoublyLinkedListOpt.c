#include <stdio.h>
#include <stdlib.h>

#define MAX_LISTS 5

// 1. Struct for the Node (Same as before)
typedef struct Node {
    int num;
    struct Node* next;
    struct Node* prev;
} Node;

// 2. NEW: Struct to hold the head and tail of a specific list
typedef struct List {
    Node* head;
    Node* tail;
} List;

// Initialize an empty list
void initList(List* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Create a new node with memory allocation check
Node* createNode(int number) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // Stop the program if we run out of memory
    }
    newNode->num = number;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Push to the head of a specific list
void pushHead(List* list, int number) {
    Node* newNode = createNode(number);
    if (list->head == NULL) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

// Push to the tail of a specific list
void pushTail(List* list, int number) {
    Node* newNode = createNode(number);
    if (list->head == NULL) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

// Pop from the head of a specific list
void popHead(List* list) {
    if (list->head == NULL) {
        printf("Empty list\n");
    } else if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        Node* temp = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);
    }
}

// Pop from the tail of a specific list
void popTail(List* list) {
    if (list->head == NULL) {
        printf("Empty list\n");
    } else if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        Node* temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
    }
}

// Merge list B into list A
void mergeList(List* listA, List* listB) {
    if (listB->head == NULL) {
        printf("Tidak perlu dilakukan apa2 karena list yang ingin ditambahkan kosong\n");
        return;
    }
    if (listA->head == NULL) {
        listA->head = listB->head;
        listA->tail = listB->tail;
    } else {
        listA->tail->next = listB->head;
        listB->head->prev = listA->tail;
        listA->tail = listB->tail;
    }
    // Clear list B since its nodes now belong to list A
    listB->head = listB->tail = NULL;
}

// Pop all nodes to free memory
void popAll(List* list) {
    while (list->head != NULL) {
        popHead(list);
    }
}

// Print a specific list
void printList(List* list, int listNumber) {
    Node* temp = list->head;
    if (temp == NULL) {
        printf("List %d is Empty\n", listNumber);
        return;
    }
    printf("List %d: ", listNumber);
    while (temp != NULL) {
        printf("%d ", temp->num);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    // Create an array of List structs instead of global pointers
    List myLists[MAX_LISTS];
    
    // Initialize all lists to NULL
    for(int i = 0; i < MAX_LISTS; i++) {
        initList(&myLists[i]);
    }

    // List 0 operations (Notice we pass the address of the specific list)
    pushHead(&myLists[0], 1);
    pushHead(&myLists[0], 2);
    pushHead(&myLists[0], 3);
    pushHead(&myLists[0], 4);
    pushTail(&myLists[0], 10);
    pushTail(&myLists[0], 20);
    popHead(&myLists[0]);
    popTail(&myLists[0]);

    // List 1 operations
    pushHead(&myLists[1], 11);
    pushHead(&myLists[1], 12);
    pushHead(&myLists[1], 13);
    pushHead(&myLists[1], 14);
    pushHead(&myLists[1], 15);
    pushTail(&myLists[1], 20);
    pushTail(&myLists[1], 30);
    popHead(&myLists[1]);
    popTail(&myLists[1]);
    
    printList(&myLists[0], 0);
    printList(&myLists[1], 1);
    
    // Merge list 1 into list 0
    mergeList(&myLists[0], &myLists[1]);
    printf("Setelah hasil merge:\n");
    printList(&myLists[0], 0);
    printList(&myLists[1], 1); // This will now be empty
    
    // Clean up memory
    popAll(&myLists[0]);
    popAll(&myLists[1]);

    return 0;
}