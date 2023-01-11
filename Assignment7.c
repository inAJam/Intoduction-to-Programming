/*
-----------------------------------------Assignment-7--------------------------------------------------
Aim : To create a program to implement BST and perform input and delete operations on it based on the 
      user input.
      *Assuming that the given file from which input is to be read exists.
      *The program is just the same as assignment 6 with changes in the insert and delete function
Code by : Anibrata.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tree //Structure corresponding to the binary search tree
{
    int id;              //The ID of the node (the ID is unique and non-negative)
    struct tree *parent; //points to the parent of the node
    struct tree *left;   //Points to the left child of the node
    struct tree *right;  //points to the right child of the node
};

void output(char s[])
{                      //Function to write to the file
    int l = strlen(s); //the length of the string
    FILE *fptr;
    fptr = fopen("output7.txt", "a"); //Appending to the file
    for (int i = 0; i < l; i++)
    {
        fprintf(fptr, "%c", s[i]);
    }
    fclose(fptr); //closing the file
}

int Imbalance(struct tree *head)
{ //function to calculate the no. of nodes on one side of a given node
    if (head == NULL)
        return 0;
    struct tree *n = head;
    return (1 + Imbalance(n->left) + Imbalance(n->right));
}

int size(struct tree *n)
{ //function to calculate the number of children of a node
    struct tree *t = n;
    return Imbalance(t) - 1;
}

void findNode(struct tree **start, int key)
{ //function which returns the node containing the key or it's parent
    struct tree *temp = *start;
    if (key < 0)
    {                  //if the key is non-negative
        *start = NULL; //setting the pointer to null
        return;
    }
    while (temp->id != key)
    { //traversing through the tree
        if (temp->id > key && temp->left == NULL)
            break;
        else if (temp->id < key && temp->right == NULL)
            break;
        if (temp->id > key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    *start = temp; //overwriting the given pointer with the new pointer
}

void add(struct tree **head, int key)
{                                                                //function to insert a node normally
    struct tree *n = (struct tree *)malloc(sizeof(struct tree)); //creating a temporary node
    n->id = key;                                                 //setting the values of the node
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    if (*head == NULL)
    { //If the tree is empty
        *head = n;
        return;
    }
    struct tree *temp = *head;
    findNode(&temp, key); //finding the parent node
    n->parent = temp;     //connecting the parent to the child
    if (temp->id > key)
        temp->left = n;
    else
        temp->right = n;
}

void copy(struct tree **new, struct tree *old)
{ //function to transfer the old tree onto a new tree
    if (old == NULL)
        return;
    add(new, old->id);
    copy(new, old->left);
    copy(new, old->right);
}

void Insert(struct tree **head, int key)
{ //function to insert a node into the tree
    if (*head == NULL)
    {
        add(head, key);
        output("true\n"); //returning true to the file
        return;
    }
    struct tree *temp = *head;
    findNode(&temp, key); //finding the parent node
    if (temp == NULL || temp->id == key)
    {                      //if a node with the given key already exists or undefined key is used
        output("false\n"); //returning error
        return;
    }
    temp = *head;
    int num = rand() % (size(temp) + 1);
    if (num == 0)
    {
        struct tree *t = NULL;
        struct tree *s = *head;
        add(&t, key);
        copy(&t, s);
        *head = t;
    }
    else
    {
        add(head, key);
    }
    output("true\n"); //returning true to the file
}

void Find(struct tree **head, int key)
{ //Function to find a node based on the key and returning its depth
    struct tree *temp = *head;
    findNode(&temp, key); //finding the loction of the node
    if (temp == NULL || temp->id != key)
    { //if the given node doesn't exist
        output("false\n");
        return;
    }
    int i = 0;
    while (temp->parent != NULL)
    { //finding the depth
        i++;
        temp = temp->parent;
    }
    char s[20];
    snprintf(s, 20, "true, depth: %d\n", i);
    output(s); //printing the depth
}

struct tree *join(struct tree *L, struct tree *R)
{ //the function used to join the wo parts
    int m, n, r, total;
    m = size(L) + 1;
    n = size(R) + 1;
    total = m + n;
    if (total == 0)
        return NULL;
    r = rand() % total;
    if (r < m)
    {
        L->right = join(L->right, R);
        return L;
    }
    else
    {
        R->left = join(L, R->left);
        return R;
    }
}

struct tree *Delete(struct tree *n, int key)
{ //Function to delete a node from a tree
    struct tree *temp;
    if (n == NULL) //searching for the key
        return NULL;
    if (key < n->id)
        n->left = Delete(n->left, key);
    else if (key > n->id)
        n->right = Delete(n->right, key);
    else if (key == n->id)
    { //when thekey is found
        temp = join(n->left, n->right);
        output("true\n");
        free(n);
        n = temp;
    }
    else
        output("false\n"); //in case the key searche for is not present
    return n;
}

void inorder(struct tree *head)
{ //to print the inorder traversal of the given subtree
    if (head == NULL)
        return;
    struct tree *n = head;
    inorder(n->left); //printing the left subtree
    char s[6];
    snprintf(s, 6, " %d", n->id);
    output(s);         //printing the root
    inorder(n->right); //printing the right subtree
}

void preorder(struct tree *head)
{ //to print the pre-order traversal
    if (head == NULL)
        return;
    struct tree *n = head;
    char s[6];
    snprintf(s, 6, " %d", n->id); //printing the root
    output(s);
    preorder(n->left);  //printing the left sub-tree
    preorder(n->right); //printing the right sub-tree
}

void postorder(struct tree *head)
{ //printing the postorder traversal
    if (head == NULL)
        return;
    struct tree *n = head;
    postorder(n->left);  //printing the left subtree
    postorder(n->right); //printing the right subtree
    char s[6];
    snprintf(s, 6, " %d", n->id);
    output(s); //printing the root
}

void PrintTree(struct tree **head)
{ //function to print the traversal of a tree
    struct tree *n = *head;
    output("In-order Traversal:");
    inorder(n);
    output("\nPre-order Traversal:");
    preorder(n);
    output("\nPost-order Traversal:");
    postorder(n);
    output("\n");
}

void PrintSubTree(struct tree **head, int key)
{ //function to print the traversal of the sub tree
    struct tree *n = *head;
    findNode(&n, key); //finding the required node (assuming that a valid id is used)
    PrintTree(&n);     //printing the subtree
}

void CalculateImbalance(struct tree **head, int key)
{ //function to calculate the imbalance
    struct tree *n = *head;
    findNode(&n, key);                                //finding the node for which imbalance is to be calculated
    int a = Imbalance(n->left) - Imbalance(n->right); //calculating the imbalance
    char s[6];
    snprintf(s, 6, "%d\n", a);
    output(s); //printing the imbalance
}

void input()
{ //function to read input from a file
    FILE *fptr;
    fptr = fopen("Input7.txt", "r"); //opening the file
    struct tree *t = NULL;
    int n, ch, key;
    fscanf(fptr, "%d", &n); //the number of commands
    while (n-- > 0 && fscanf(fptr, "%d", &ch) != EOF)
    {
        switch (ch) //choice of the user
        {
        case 1: //to insert a node
            fscanf(fptr, "%d", &key);
            Insert(&t, key);
            break;
        case 2: //to delete a node
            fscanf(fptr, "%d", &key);
            t = Delete(t, key);
            break;
        case 3: //to find a node
            fscanf(fptr, "%d", &key);
            Find(&t, key);
            break;
        case 4: //to print the tree
            PrintTree(&t);
            break;
        case 5: //to print the subtree
            fscanf(fptr, "%d", &key);
            PrintSubTree(&t, key);
            break;
        case 6: //to calculate imbalance
            fscanf(fptr, "%d", &key);
            CalculateImbalance(&t, key);
            break;
        default: //default case
            output("false\n");
            break;
        }
    }
    fclose(fptr); //closing the file
}

int main()
{
    FILE *fptr;
    fptr = fopen("output7.txt", "w");
    fprintf(fptr, "");
    fclose(fptr); //clearing the output file
    srand(time(0));
    input(); //starting the input
}
