//Carrying over from 40_MinHeap.c, we have the following code:

#include <stdio.h>
#include <stdlib.h>


int* generateArray(int size) {
    int* A = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        A[i] = rand() % 100;
    }
    return A;
}

void printArray(int* A, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", A[i]);
        if (i != size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void minHeapify(int* A, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && A[left] < A[smallest]) {
        smallest = left;
    }
    if (right < size && A[right] < A[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&A[i], &A[smallest]);
        minHeapify(A, size, smallest);
    }
}


/*================================================*/
/*==============New code starts here==============*/
/*================================================*/


//minHeapinsert function takes in an array, the size of the array, and the value to be inserted using the minHeap property and reallocates the array to be one larger and inserts the value in the correct position

int* minHeapinsert(int* A, int size, int value) {
    A = realloc(A, (size + 1) * sizeof(int));
    A[size] = value;
    int i = size;
    while (i > 0 && A[(i - 1) / 2] > A[i]) {
        swap(&A[i], &A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return A;
}


//main function asks user for size of array, generates array, prints array, calls minHeapify, and prints array again
//Then it asks the user for a value to insert into the array, calls minHeapinsert, and prints the array again

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* A = generateArray(size);
    printf("The array is: ");
    printArray(A, size);
    minHeapify(A, size, 0);
    printf("The array after minHeapify is: ");
    printArray(A, size);
    int value;
    printf("Enter the value to insert into the array: ");
    scanf("%d", &value);
    A = minHeapinsert(A, size, value);
    printf("The array after minHeapinsert is: ");
    printArray(A, size+1);
    return 0;
}


