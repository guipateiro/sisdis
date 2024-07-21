#include <stdio.h>
#include <limits.h> // for INT_MAX
#include <stdlib.h> // for qsort
#include "utils.h"

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void specialSort(int arr[], int n) {
    if (n <= 1) return; // If array has 0 or 1 element, it's already sorted

    int first = arr[0];
    int veryLargeNumber = INT_MAX/2;

    // Transform the array according to the condition
    for (int i = 1; i < n; ++i) {
        if (arr[i] < first) {
            arr[i] += veryLargeNumber;
        }
    }

    // Sort the transformed array
    qsort(arr + 1, n - 1, sizeof(int), compare);

    // Reverse the transformation to get the final sorted array
    for (int i = 1; i < n; ++i) {
        if (arr[i] >= veryLargeNumber) {
            arr[i] -= veryLargeNumber;
        }
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// Function to create a new node with given data
list* create_list_node(int data) {
    list* newNode = (list*)malloc(sizeof(list));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

list* create_list(int data[], int size) {
    if (size < 1) return NULL;
    list* firstNode = create_list_node(data[0]);
    list* newNode = firstNode;
    for (int i = 1; i < size; i++) {
        newNode->next = create_list_node(data[i]);
        newNode = newNode->next;
    }
    return firstNode;
}

// Function to append a new node with given data at the end of the list
void append(list** headRef, int data) {
    list* newNode = create_list_node(data);
    if (*headRef == NULL) {
        // If the list is empty, make the new node as the head
        *headRef = newNode;
    } else {
        // Traverse to the last node
        list* current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        // Append the new node at the end
        current->next = newNode;
    }
}

// Function to print all elements in the linked list
void printList(list* head) {
    list* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to free memory allocated to the linked list
void freeList(list* head) {
    list* current = head;
    while (current != NULL) {
        list* temp = current;
        current = current->next;
        free(temp);
    }
}
