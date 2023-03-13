//Carrying over from section 1, we have the following code:

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

/*================================================*/
/*==============New code starts here==============*/
/*================================================*/

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
//main function asks user for size of array, generates array, prints array, calls minHeapify, and prints array again

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
    return 0;
}


