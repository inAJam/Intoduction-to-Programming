/*
-----------------------------------------Assignment-6--------------------------------------------------
Aim : To create a program to implement BST and perform operations on it based on input via files and
      printing it on a file.
      *Assuming that the given file from which input is to be read exists.
Code by : Anibrata.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree//Structure corresponding to the binary search tree
{
    int id;//The ID of the node (the ID is unique and non-negative)
    struct tree* parent;//points to the parent of the node
    struct tree* left;//Points to the left child of the node
    struct tree* right;//points to the right child of the node
};

void output(char s[]){//Function to write to the file
    int l =strlen(s);//the length of the string
    FILE *fptr;
    fptr = fopen("output.txt","a");//Appending to the file
    for(int i=0;i<l;i++){
        fprintf(fptr,"%c",s[i]);
    }
    fclose(fptr);//closing the file
}

void findNode(struct tree** start,int key){//function which returns the node containing the key or it's parent
    struct tree* temp = *start;
    if(key<0){//if the key is non-negative
        *start = NULL;//setting the pointer to null
        return;
    }
    while (temp->id!=key){//traversing through the tree
        if(temp->id>key && temp->left==NULL)
            break;
        else if(temp->id<key && temp->right==NULL)
            break;
        if(temp->id>key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    *start = temp;//overwriting the given pointer with the new pointer
}

void Insert(struct tree** head,int key){//function to insert a node 
    struct tree* n = (struct tree*)malloc(sizeof(struct tree));//creating a temporary node
    n->id = key;//setting the values of the node
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    if(*head==NULL){//If the tree is empty
        *head = n;
        output("true\n");//returning true to the file
        return;
    }
    struct tree* temp = *head;
    findNode(&temp,key);//finding the parent node
    if(temp==NULL || temp->id==key){//if a node with the given key already exists or undefined key is used
        output("false\n");//returning error
        return;
    }
    n->parent = temp;//connecting the parent to the child
    if(temp->id>key)
        temp->left = n;
    else
        temp->right = n;
    output("true\n");//returning true to the file
}

void Find(struct tree** head,int key){//Function to find a node based on the key and returning its depth
    struct tree* temp = *head;
    findNode(&temp,key);//finding the loction of the node
    if(temp==NULL || temp->id!=key){//if the given node doesn't exist
        output("false\n");
        return;
    }
    int i=0;
    while(temp->parent!=NULL){//finding the depth
        i++;
        temp = temp->parent;
    }
    char s[20];
    snprintf(s,20,"true, depth: %d\n",i);
    output(s);//printing the depth
}

void Delete(struct tree** head,int key){//Function to delete a node
    struct tree* temp = *head;
    findNode(&temp,key);
    if(temp==NULL || temp->id!=key){//If the node to be deleted doesn't exist
        output("false\n");
        return;
    }
    struct tree* n = temp;//replacement to be done with greatest value from left subtree of the node to be deleted
    struct tree* m;
    if(n->left==NULL)
        n=n->right;
    else{
        n = n->left;
        while(n->right!=NULL)//finding the node to be replaced with
            n=n->right;
        if(temp->left!=n){
            if(n->left!=NULL){//connecting the child of the replacement node with it's parent node
                m = n->parent;
                m->right = n->left;
                m = n->left;
                m->parent = n->parent;
            }
            m=temp->left;//connecting the left subtree of the node to be replaced with its replacement node
            m->parent = n;
            n->left = m;
        }
        if(temp->right!=NULL){//connecting the right subtree of the node to be replaced with its replacement
            n->right = temp->right;
            m = temp->right;
            m->parent = n;
        }
    }
    n->parent = temp->parent;//connecting the parent of the deleted node with its replacement
    temp = temp->parent;
    if(temp->id>n->id)
        temp->left = n;
    else
        temp->right = n;
    output("true\n");
}

void inorder(struct tree* head){//to print the inorder traversal of the given subtree
    if(head==NULL)
        return;
    struct tree* n=head;
    inorder(n->left);//printing the left subtree
    char s[6];
    snprintf(s,6," %d",n->id);
    output(s);//printing the root
    inorder(n->right);//printing the right subtree
}

void preorder(struct tree* head){//to print the pre-order traversal
    if(head==NULL)
        return;
    struct tree* n=head;
    char s[6];
    snprintf(s,6," %d",n->id);//printing the root
    output(s);
    preorder(n->left);//printing the left sub-tree
    preorder(n->right);//printing the right sub-tree
}

void postorder(struct tree* head){//printing the postorder traversal 
    if(head==NULL)
        return;
    struct tree* n=head;
    postorder(n->left);//printing the left subtree
    postorder(n->right);//printing the right subtree
    char s[6];
    snprintf(s,6," %d",n->id);
    output(s);//printing the root
}

void PrintTree(struct tree** head){//function to print the traversal of a tree
    struct tree* n = *head;
    output("In-order Traversal:");
    inorder(n);
    output("\nPre-order Traversal:");
    preorder(n);
    output("\nPost-order Traversal:");
    postorder(n);
    output("\n");
}

void PrintSubTree(struct tree** head,int key){//function to print the traversal of the sub tree
    struct tree* n = *head;
    findNode(&n,key);//finding the required node (assuming that a valid id is used)
    PrintTree(&n);//printing the subtree
}

int Imbalance(struct tree* head){//function to calculate the no. of nodes on one side of a given node
    if(head==NULL)
        return 0;
    struct tree* n = head;
    return 1+Imbalance(n->left)+Imbalance(n->right);
}

void CalculateImbalance(struct tree** head,int key){//function to calculate the imbalance
    struct tree* n = *head;
    findNode(&n,key);//finding the node for which imbalance is to be calculated
    int a = Imbalance(n->left) - Imbalance(n->right);//calculating the imbalance
    char s[6];
    snprintf(s,6,"%d\n",a);
    output(s);//printing the imbalance
}

void input(){//function to read input from a file
    FILE *fptr;
    fptr = fopen("input.txt","r");//opening the file
    struct tree* t = NULL;
    int n,ch,key;
    fscanf(fptr,"%d",&n);//the number of commands
    while(n-->0 && fscanf(fptr,"%d",&ch)!=EOF){
        switch (ch)//choice of the user
        {
        case 1://to insert a node
            fscanf(fptr,"%d",&key);
            Insert(&t,key);
            break;
        case 2://to delete a node
            fscanf(fptr,"%d",&key);
            Delete(&t,key);
            break;
        case 3://to find a node
            fscanf(fptr,"%d",&key);
            Find(&t,key);
            break;
        case 4://to print the tree
            PrintTree(&t);
            break;
        case 5://to print the subtree
            fscanf(fptr,"%d",&key);
            PrintSubTree(&t,key);
            break;
        case 6://to calculate imbalance
            fscanf(fptr,"%d",&key);
            CalculateImbalance(&t,key);
            break;
        default://default case
            output("false\n");
            break;
        }
    }
    fclose(fptr);//closing the file
}

int main(){
    FILE *fptr;
    fptr = fopen("output.txt","w");
    fprintf(fptr,"");
    fclose(fptr);//clearing the output file
    input();//starting the input
}