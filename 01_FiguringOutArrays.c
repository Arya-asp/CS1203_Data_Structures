//A piece of code that generates and prints arrays using loops, pointers and malloc.
//An Array is generated using a heap(?) using the malloc() function for memory allocation
//this allocates memory in the heap and returns a pointer to the first element of the array.
//Soham said that this will be funny later: https://www.reddit.com/r/ProgrammerHumor/comments/v4ef50/see_you_later_allocator/

#include <stdio.h>
#include <stdlib.h>

//function generateArray() return an address, the begining of an array, stored in A, this function genrates an array with random values
int* generateArray(int size) {
    int* A = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        A[i] = rand() % 100;
    }
    return A;
}

//function printArray() takes in an array and its size and prints the array with a comma and a space between each element, starting the array with a '[' and ending it with a ']'
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


//function main() asks for the size of array and the inputs and then generates an array and prints it using generateArray() and printArray() functions
int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* A = generateArray(size);
    printArray(A, size);
    return 0;
}