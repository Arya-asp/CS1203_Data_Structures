//Carrying over from section 20, we have the following code:

#include <stdio.h>
#include <stdlib.h>


int* generateArray(int size) {
    int* A = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        A[i] = rand() % 1000;
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
        printf("The root node is %d\n", root->val);
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
                    printf("%d is added to the BST with %d as its parent\n", newNode->val, parent->val);
                }
            }
            else 
            {
                current = current->right;
                if (current == NULL) 
                {
                    parent->right = newNode;
                    printf("%d is added to the BST with %d as its parent\n", newNode->val, parent->val);
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



/*================================================*/
/*==============New code starts here==============*/
/*================================================*/

//Function to delete a node from the BST
//After Checking for all the edge cases, we can delete a node from the BST in 5 steps:
//>Find the node to be deleted
//>Check if the node has any children
//>If the node has children, check if it has 1 or 2 children
//>If the node has 1 child, replace the node with its child
//>If the node has 2 children, find the smallest node in the right subtree and replace the node with it

void deleteNode(int val)
{
    struct node *current = root;
    struct node *parent = NULL;
    while (current != NULL && current->val != val) 
    {
        parent = current;
        if (val < current->val) 
        {
            current = current->left;
        }
        else 
        {
            current = current->right;
        }
    }
    if (current == NULL) 
    {
        printf("The node to be deleted is not found\n");
        return;
    }
    else 
    {
        //Case 1: If the node has no children
        if (current->left == NULL && current->right == NULL) 
        {
            //If the node to be deleted is the root node
            if (current == root) 
            {
                root = NULL;
            }
            //If the node to be deleted is a left child
            else if (parent->left == current) 
            {
                parent->left = NULL;
            }
            //If the node to be deleted is a right child
            else 
            {
                parent->right = NULL;
            }
            free(current);
        }
        //Case 2: If the node has 1 child
        else if (current->left == NULL || current->right == NULL) 
        {
            struct node *temp;
            //If the node to be deleted has a left child
            if (current->left != NULL) 
            {
                temp = current->left;
            }
            //If the node to be deleted has a right child
            else 
            {
                temp = current->right;
            }
            //If the node to be deleted is the root node
            if (current == root) 
            {
                root = temp;
            }
            //If the node to be deleted is a left child
            else if (parent->left == current) 
            {
                parent->left = temp;
            }
            //If the node to be deleted is a right child
            else 
            {
                parent->right = temp;
            }
            free(current);
        }
        //Case 3: If the node has 2 children
        else 
        {
            struct node *temp = current->right;
            struct node *tempParent = current;
            while (temp->left != NULL) 
            {
                tempParent = temp;
                temp = temp->left;
            }
            current->val = temp->val;
            if (tempParent->left == temp) 
            {
                tempParent->left = temp->right;
            }
            else 
            {
                tempParent->right = temp->right;
            }
            free(temp);
        }
    }
}

//main function generates an array of size n, where n is the user input, and then inserts the values of the array into the BST
//then the preorder traversal of the BST is printed, after that the user is asked to input a value to be deleted from the BST
//the preorder traversal of the BST is printed again after the node is deleted

int main()
{
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int *A = generateArray(n);
    printf("The array is: ");
    printArray(A, n);
    for (int i = 0; i < n; i++) 
    {
        BSTinsertnode(A[i]);
    }
    printf("The preorder traversal of the BST is: ");
    preorder(root);
    printf("\n");
    int val;
    printf("Enter the value of the node to be deleted: ");
    scanf("%d", &val);
    deleteNode(val);
    printf("The preorder traversal of the BST after deleting the node is: ");
    preorder(root);
    printf("\n");
    return 0;
}