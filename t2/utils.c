#include <stdio.h>
#include <limits.h> // for INT_MAX
#include <stdlib.h> // for qsort

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

// // Example usage
// int main() {
//     int arr[] = {7, 6, 5, 4};
//     int n = sizeof(arr) / sizeof(arr[0]);

//     printf("Original array: ");
//     printArray(arr, n);

//     specialSort(arr, n);

//     printf("Sorted array: ");
//     printArray(arr, n);

//     return 0;
// }
