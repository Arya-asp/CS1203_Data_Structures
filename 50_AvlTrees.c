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

/*================================================*/
/*==============New code starts here==============*/
/*================================================*/

//Actually no Insertnode fuction is the same as the one used in BST
void BSTinsertnode(int val)
{
    struct node *newNode = createNode(val);
    if (root == NULL) 
    {
        root = newNode;
        //printf("The root node is %d, and it has no parent node\n", root->val);
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
                    //printf("The parent node of %d is %d, and it is on the left side\n", newNode->val, parent->val);
                }
            }
            else 
            {
                current = current->right;
                if (current == NULL) 
                {
                    parent->right = newNode;
                    //printf("The parent node of %d is %d, and it is on the right side\n", newNode->val, parent->val);
                }
            }
        }
    }
}

//We will also need a function to determine the height of the tree

int height(struct node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}

//We will also need a function to determine the balance factor of the tree, denoted by k

int balanceFactor(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int k = height(root->left) - height(root->right);
        return k;
    }
}

//Left rotation function

struct node *leftRotate(struct node *root)
{
    struct node *newRoot = root->right;
    struct node *temp = newRoot->left;
    newRoot->left = root;
    root->right = temp;
    return newRoot;
}

//Right rotation function

struct node *rightRotate(struct node *root)
{
    struct node *newRoot = root->left;
    struct node *temp = newRoot->right;
    newRoot->right = root;
    root->left = temp;
    return newRoot;
}

//Function to insert a node in the AVL tree while balancing the tree

void BalanceInsertNode(int val)
{
    struct node *newNode = createNode(val);
    if (root==NULL)
    {
        root = newNode;
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
                }
            }
            else
            {
                current = current->right;
                if (current == NULL)
                {
                    parent->right = newNode;
                }
            }
        }
    }
    int k = balanceFactor(root);
    if (k>1 && val < root->left->val) //if the tree is left heavy perfrom a right rotation
    {
        root = rightRotate(root);
    }
    else if (k<-1 && val > root->right->val) //if the tree is right heavy perform a left rotation
    {
        root = leftRotate(root);
    }
    else if (k>1 && val > root->left->val) //if the tree is left heavy and the new node is on the right side of the left child, perform a left rotation on the left child and then a right rotation on the root
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }
    else if (k<-1 && val < root->right->val) //if the tree is right heavy and the new node is on the left side of the right child, perform a right rotation on the right child and then a left rotation on the root
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
    else
    {
        /* code */
    }    
}

//Function to output the AVL tree in order (simmilar to BST)

void printInOrder(struct node *root)
{
    if (root != NULL)
    {
        printInOrder(root->left);
        printf("%d ", root->val);
        printInOrder(root->right);
    }
}

//Main function to ask for user input to generate a random array and print it
//then insert the array into the AVL tree and print the tree in order

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int *A = generateArray(size);
    printf("The array is: ");
    printArray(A, size);
    printf("The AVL tree is: ");
    for (int i = 0; i < size; i++)
    {
        BalanceInsertNode(A[i]);
    }
    printInOrder(root);
    printf("\n");
    return 0;
}