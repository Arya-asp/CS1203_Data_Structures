//Look for new code starts here, explanation for previous code is in 10_LinkedList.c
//Objective: Develop an algorithm that prints the first half of a given linked list without knowing how many elements in the array


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



/*^code carried over from 11^*/
/*================================================*/
/*==============New code starts here==============*/
/*================================================*/

//function halfList() is a function that prints the first half of the linked list without using the size of the linked list, instead it uses hare and tortoise algorithm
//where the hare moves twice as fast as the tortoise, when the hare reaches the end of the linked list, the tortoise will be at the middle of the linked list
void halfList(my_node* head) {
    my_node* hare = head;
    my_node* tortoise = head;
    while (hare != NULL && hare->next != NULL) {
        hare = hare->next->next;
        tortoise = tortoise->next;
    }
    while (head != tortoise) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}





int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* A = generateArray(size);
    printArray(A, size);
    my_node* head = arrayToList(A, size);
    printList(head);
    halfList(head);
    return 0;
}

