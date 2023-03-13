//Look for new code starts here, explanation for previous code is in 11_ReverseLinkedList.c
//Objective: Chunk Reversing a Linked List for any chunk size in range 1 to n (inclusive): Given a Linked List, and an integer k representing the chunk size, chunk-reverse the list



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

//Function RevList() takes a pointer from the first node of the linked list and reverses the linked list
my_node* RevList(my_node* head) {
    my_node* current = head;
    my_node* prev = NULL;
    my_node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

/*^code carried over from 11^*/
/*================================================*/
/*==============New code starts here==============*/
/*================================================*/

//function chunkReverseLL() takes in a pointer to the first node of the linked list and a number k and reverses the linked list in chunks of size k
my_node* chunkReverseLL(my_node* head, int k) {
    my_node* current = head;
    my_node* prev = NULL;
    my_node* next = NULL;
    int count = 0;
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    if (next != NULL) {
        head->next = chunkReverseLL(next, k);
    }
    return prev;
}

//function main() asks for the size of array and the inputs and then generates an array and prints it using generateArray() and printArray() functions
//then it creates a linked list from the array and prints it using arrayToList() and printList() functions
//then it asks for a chunk size k and chunk reverses the linked list with chunk size k and prints it using chunkReverseLL() and printList() functions

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
    int k;
    printf("Enter the chunk size: ");
    scanf("%d", &k);
    head = chunkReverseLL(head, k);
    printf("The chunk reversed linked list is: ");
    printList(head);
    return 0;
}

