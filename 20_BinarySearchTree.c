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

/*================================================*/
/*==============New code starts here==============*/
/*================================================*/
struct node
{
    int val;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;


struct node *createNode(int val) 
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Function to insert a node in the BST while outputting the value of the parent node relative to the new node as well as the side of the parent node

void BSTinsertnode(int val)
{
    struct node *newNode = createNode(val);
    if (root == NULL) 
    {
        root = newNode;
        printf("The root node is %d, and it has no parent node\n", root->val);
    }
    else 
    {
        struct node *current = root;
        struct node *parent = NULL;
        while (current != NULL) 
        {
            parent = current;
            if (val < current->val) 
            {
                current = current->left;
                if (current == NULL) 
                {
                    parent->left = newNode;
                    printf("The parent node of %d is %d, and it is on the left side\n", newNode->val, parent->val);
                }
            }
            else 
            {
                current = current->right;
                if (current == NULL) 
                {
                    parent->right = newNode;
                    printf("The parent node of %d is %d, and it is on the right side\n", newNode->val, parent->val);
                }
            }
        }
    }
}

//Function to print the preorder traversal of the BST
void preorder(struct node *root)
{
    if (root != NULL) 
    {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}


//main function

int main() 
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* A = generateArray(size);
    printf("The array is: ");
    printArray(A, size);
    for (int i = 0; i < size; i++) 
    {
        BSTinsertnode(A[i]);
    }
    printf("The preorder traversal of the BST is: ");
    preorder(root);
    return 0;
}