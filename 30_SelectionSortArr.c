//Look for new code starts here, explanation for previous code is in 12_ChunkReverseLL.c
//Objective: Selection Sort Algorithm: Given an array of values (assume int), use selection sort to sort them in ascending or descending order


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
/*^code carried over from 01^*/
/*==============New code starts here==============*/


//IMP: Prof recommended to use typedef to make the code more understandable on the fly
struct node { //used to create a node and package several data fields into one. 
    int val;
    struct node* next; //All of the times we are dealing with addresses of the nodes. Pointers to the nodes. This is going to point to the next node
}; 

typedef struct node my_node; //setting my_node as an alias for struct node



//function arrayToList() takes in an array and its size and returns a pointer to the first node of the linked list and then creates a linked list from the array
my_node* arrayToList(int* A, int size) {
    my_node* head = malloc(sizeof(my_node)); //malloc() returns a pointer to the first element of the array
    my_node* current = head; //current is a pointer to the current node
    for (int i = 0; i < size; i++) {
        current->val = A[i]; //current->val is the same as (*current).val
        if (i != size - 1) {
            current->next = malloc(sizeof(my_node));
            current = current->next;
        }
    }
    return head;
}

//function printList() takes in a pointer to the first node of the linked list and prints the linked list with a space between each element
void printList(my_node* head) {
    my_node* current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

/*^code carried over from 12^*/
/*================================================*/
/*==============New code starts here==============*/
/*================================================*/

//For selection sorting the array we need a swap function to swap the values of two entries in the array
void swapArr(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//For selection sorting the Array we need a function to find the location of the minimum value in the array
int findMinArr(int* A, int size, int start) {
    int min = start;
    for (int i = start; i < size; i++) {
        if (A[i] < A[min]) {
            min = i;
        }
    }
    return min;
}


//For selection sorting the Array we need a function to find the location of the maximum value in the array
int findMaxArr(int* A, int size, int start) {
    int max = start;
    for (int i = start; i < size; i++) {
        if (A[i] > A[max]) {
            max = i;
        }
    }
    return max;
}


//function selectionSortasc() takes in the Array and sorts it in ascending order
void selectionSortascArr(int* A, int size) {
    for (int i = 0; i < size; i++) {
        int min = findMinArr(A, size, i);
        swapArr(&A[i], &A[min]);
    }
}


//function selectionSortasc() takes in the Array and sorts it in descending order
void selectionSortdescArr(int* A, int size) {
    for (int i = 0; i < size; i++) {
        int max = findMaxArr(A, size, i);
        swapArr(&A[i], &A[max]);
    }
}

//main() function asks the user for a size of array and prints it
//Then it asks the user to choose between ascending and descending order and then sorts the Array using the above functions in the specified order and prints it
int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* A = generateArray(size);
    printf("The array is: ");
    printArray(A, size);
    printf("Enter 0 for ascending order and 1 for descending order: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 0) {
        selectionSortascArr(A, size);
    }
    else if (choice == 1) {
        selectionSortdescArr(A, size);
    }
    else {
        printf("Invalid choice\n");
    }
    printf("The sorted array is: ");
    printArray(A, size);
    return 0;
}
