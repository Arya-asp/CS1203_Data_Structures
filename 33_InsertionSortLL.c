//Look for new code starts here, explanation for previous code is in 31_SelectionSortll.c
//Objective: Selection Sort Algorithm: Given an LinkedList, use insertion sort to sort them in ascending or descending order


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

//For insertion sort we need a swap function to swap the values of two nodes
void swap(my_node* a, my_node* b) {
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}



//function InsertionSortasc() takes in a pointer to the head node of the linked list and sorts the linked list in ascending order while declaring a pointer to the current node and a pointer to the temp node
void insertionSortasc(my_node* head) {
    my_node* current = head->next; //current is a pointer to the current node
    my_node* temp = head; //temp is a pointer to the temp node
    while (current != NULL) {
        temp = head;
        while (temp != current) {
            if (temp->val > current->val) {
                swap(temp, current);
            }
            temp = temp->next;
        }
        current = current->next;
    }
}

//function InsertionSortdesc() takes in a pointer to the first node of the linked list and sorts the linked list in descending order
void insertionSortdesc(my_node* head) {
    my_node* current = head->next; //current is a pointer to the current node
    my_node* temp = head; //temp is a pointer to the temp node
    while (current != NULL) {
        temp = head;
        while (temp != current) {
            if (temp->val < current->val) {
                swap(temp, current);
            }
            temp = temp->next;
        }
        current = current->next;
    }
}

//main() function asks the user for a size of array and prints it, then creates a linked list from the array and prints it
//Then it asks the user to choose between ascending and descending order and then sorts the linked list in the specified order and prints it
int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* A = generateArray(size);
    printf("The array is: ");
    printArray(A, size);
    my_node* head = arrayToList(A, size);
    printf("The linked list is: ");
    printList(head);
    printf("Enter 0 for ascending order and 1 for descending order: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 0) {
        insertionSortasc(head);
    }
    else if (choice == 1) {
        insertionSortdesc(head);
    }
    else {
        printf("Invalid choice\n Defaulting to ascending order\n");
        insertionSortasc(head);
    }
    printf("The sorted linked list is: ");
    printList(head);
    return 0;
}