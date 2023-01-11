/*
---------------------------------------Assignment-1------------------------------------------------
Aim : To create a menu driven program to add, delete, split, or configure virtual DNA chains.
Code by : Anibrata.
*/

#include <stdio.h>
#include <stdlib.h>

struct DNA//Structure holding information about a single DNA molecule
{
    int ID;
    struct chain* alpha;
    struct chain* beta;
    struct DNA* next;
};

struct chain//Structure holding information about the nucleotides of each DNA molecule
{
    char nucleotide;
    struct chain* next;
    struct chain* across;
};

void createMolecule(struct DNA** head){//function to create a new molecule
    struct DNA *temp = *head;
    struct DNA* X = (struct DNA*)malloc(sizeof(struct DNA));
    X->next = NULL;
    int j=1;//To find the ID number of the molecule
    if(*head==NULL){//if the list is empty
        X->ID = j;
        *head = X;
    }
    else{
        while(temp->next!=NULL){
            temp = temp->next;
            ++j;
        }
        X->ID = ++j;
        temp->next = X;
    }
    printf("Enter the number of nucleotides to enter : ");
    int l;
    scanf("%d",&l);
    struct chain* m = (struct chain*) malloc(sizeof(struct chain));
    struct chain* n = (struct chain*) malloc(sizeof(struct chain));
    X->alpha = m;
    X->beta = n;
    int i=0;
    while(i<l){//filling the chain with the desired number of nucleotides
        if(i!=0){
            m->next = malloc(sizeof(struct DNA));
            n->next = malloc(sizeof(struct DNA));
            m = m->next;
            n = n->next;
        }
        printf("Insert nucleotide number %d : ",i+1);
        scanf(" %c",&m->nucleotide);//filling the opposite nucleotide
        if(m->nucleotide=='A') n->nucleotide = 'T';
        else if(m->nucleotide=='T') n->nucleotide = 'A';
        else if(m->nucleotide=='G') n->nucleotide = 'C';
        else n->nucleotide = 'G';
        m->across = n;
        n->across = m;
        m->next = NULL;
        n->next = NULL;
        i++;
    }
    printf("Molecule with ID %d has been created \n",j);
}

void printAll(struct DNA** head){//function to print all the molecules
    struct DNA* n = *head;
    struct chain* a = NULL;
    if(n==NULL){
        printf("The list is empty\n");
        return;
    }
    while(n!=NULL){
        a = n->alpha;
        int i=1;//to find the number of nucleotides each molecule has
        while(a->next!=NULL){//printing the alpha chain
            printf("%c-",a->nucleotide);
            a = a->next;
            i++;
        }
        printf("%c \n",a->nucleotide);
        while(i-->0) printf("| ");
        printf("\n");
        a=n->beta;
         while(a->next!=NULL){//printing the beta chain
            printf("%c-",a->nucleotide);
            a = a->next;
            i++;
        }
        printf("%c \n",a->nucleotide);
        n = n->next;
    }
}

void printChain(struct DNA** head,int id){//function to print a particular chain
    struct DNA* n = *head;
    if(n==NULL){//if the list is empty
        printf("Empty database\n");
        return;
    }
    while(n!=NULL && n->ID!= id) n = n->next;
    if(n==NULL){//when molecule with id specified by the user does not exist
        printf("No molecule with any such ID exists\n");
        return;
    }
    struct chain* a = n->alpha;
    int i=1;//to find the number of nucleotides each chain has
    while(a->next!=NULL){//printing the alpha chain
        printf("%c-",a->nucleotide);
        a = a->next;
        i++;
    }
    printf("%c \n",a->nucleotide);
    while(i-->0) printf("| ");
    printf("\n");
    a=n->beta;
    while(a->next!=NULL){//printing the beta chain
        printf("%c-",a->nucleotide);
        a = a->next;
        i++;
    }
    printf("%c \n",a->nucleotide);
}

void delete(struct DNA** head,int id,int pos){//function to delete a particular nucleotide
    struct DNA* n = *head;
    if(n==NULL){
        printf("Empty database\n");
        return;
    }
    while(n!=NULL && n->ID!= id) n = n->next;
    if(n==NULL){//to ensure no wrong molecule ID is entered
        printf("No molecule with any such ID exists\n");
        return;
    }
    struct chain* a = n->alpha;
    struct chain* b = n->beta;
    int i=1;
    if(pos==1){//If the first nucleotide is to be deleted
        n->alpha = a->next;
        n->beta = b->next;
        return;
    }
    while(a!=NULL && i<(pos-1)) {
        a = a->next;
        b = b->next;
        i++;
    }
    if(a==NULL){//If the position specified exceeds the chain length
        printf("No nucleotide exists at the specified position\n");
        return;
    }
    a->next = a->next->next;
    b->next = b->next->next;
}

void insert(struct DNA** head,int id,int pos){//function to insert a nucleotide at a specified position in the chain
    struct DNA* n = *head;
    if(n==NULL){
        printf("Empty database\n");
        return;
    }
    while(n!=NULL && n->ID!= id) n = n->next;
    if(n==NULL){
        printf("No molecule with any such ID exists\n");
        return;
    }
    struct chain* a = n->alpha;
    struct chain* b = n->beta;
    struct chain* m = (struct chain*) malloc(sizeof(struct chain));
    struct chain* p = (struct chain*) malloc(sizeof(struct chain));
    int i=1;
    printf("Enter the chain to be entered at (0-alpha 1-beta): ");//finding the chain at which the value is to be entered
    int t;
    scanf(" %d",&t);
    if(t!=1 && t!=0){
        printf("Wrong Input.\n");
        return;
    }
    printf("Enter the nucleotide to be entered : ");
    char s,k;
    scanf(" %c",&s);
    if(s=='A') k = 'T';
    else if(s=='T') k = 'A';
    else if(s=='G') k = 'C';
    else k = 'G';
    if(t==0){//fitting the nucleotide in the appropriate chain
        m->nucleotide = s;
        p->nucleotide = k;
    }
    else{
        m->nucleotide = k;
        p->nucleotide = s;
    }
    m->across = p;
    p->across = m;
    if(pos==1){//if nucleotide is to be inserted at the beginning of the chain
        m->next = n->alpha;
        p->next=n->beta;
        n->alpha = m;
        n->beta = p;
        return;
    }
    while(a!=NULL && i<(pos-1)) {
        a = a->next;
        b = b->next;
        i++;
    }
    if(a==NULL){//If position specified exceeds the chain length
        printf("\nNo nucleotide exists at the specified position\n");
        return;
    }
    m->next = a->next;
    p->next = b->next;
    a->next = m;
    b->next = p;
}

void split(struct DNA** head,int id){//function to split the chain into two different chains
    struct DNA *temp = *head;
    struct DNA* X = (struct DNA*)malloc(sizeof(struct DNA));//the new chain created from splitting the previous chain
    struct DNA* Y = NULL;//To store the position of the original chain
    X->next = NULL;
    int j=1;
    if(*head==NULL){
        printf("No DNA molecule in database.\n");
        return;
    }
    if(id==1) Y=temp;//if the first chain is to be split
    while(temp->next!=NULL){
        if (temp->ID== id) Y=temp;
        temp = temp->next;
        j++;
    }
    X->ID = ++j;
    if(Y == NULL){
        printf("Molecule with the given ID does not exist in the database\n");
        return;
    }
    temp->next = X;//Adding storage to hold the new chain to the list 
    printf("Molecule with ID %d created by splitting molecule with ID %d \n",j,id);
    struct chain* m = (struct chain*) malloc(sizeof(struct chain));
    struct chain* n = (struct chain*) malloc(sizeof(struct chain));
    struct chain* a = Y->alpha;//To store the position of the nucleotides of the original molecule's alpha chain  
    struct chain* b = Y->beta;//To store the position of the nucleotides of the original molecule's beta chain
    X->alpha = m;//To create a alpha chain
    X->beta = n;//To create a beta chain
    int i=0; 
    while(a!=NULL){
        a->across = NULL;//destroying all interconnections between alpha and beta chains
        b->across = NULL;
        if(i!=0){
            m->next = malloc(sizeof(struct DNA));
            n->next = malloc(sizeof(struct DNA));
            m = m->next;
            n = n->next;
        }
        m->nucleotide = a->nucleotide;
        n->nucleotide = b->nucleotide;
        m->across = NULL;
        n->across = NULL;
        m->next = NULL;
        n->next = NULL;
        i++;
        a = a->next;//moving on to the next nucleotide
        b = b->next;
    }//repeating until all links between alpha and beta chains are destroyed
    a = Y->beta;//Interchanging the beta chains between the newly formed chain and the original chain
    Y->beta = X->beta;
    X->beta = a;
    m = X->alpha;
    n = X->beta;
    a = Y->alpha;
    b = Y->beta;
    while(a!=NULL){//forming the interconnections between the new chains
        a->across = b;
        b->across =a;
        m->across =n;
        n->across = m;
        a = a->next;
        b= b->next;
        m = m->next;
        n=n->next;
    }
}

int main(){//main function
    struct DNA* head = NULL;
    int a,id,pos;
    do{
        printf("Menu :\n1.Create Molecule\n2.Insert\n3.Delete\n4.Split\n5.Print Molecule\n6.Print All Molecule\n7.Quit\nEnter your Choice : ");
        scanf(" %d",&a);
        switch (a)//The menu
        {
        case 1://To create a new molecule
            createMolecule(&head);
            break;
        case 2://To insert a nucleotide
            printf("Enter molecule ID : ");
            scanf(" %d",&id);
            printf("Enter position to be inserted at : ");
            scanf(" %d",&pos);
            insert(&head,id,pos);
            break;
        case 3://To delete a nucleotide
            printf("Enter molecule ID : ");
            scanf(" %d",&id);
            printf("Enter position at which nucleotide is to be deleted : ");
            scanf(" %d",&pos);
            delete(&head,id,pos);
            break;
        case 4://TO split a chain
            printf("Enter molecule ID : ");
            scanf(" %d",&id);
            split(&head,id);
            break;
        case 5://To print a molecule
            printf("Enter molecule ID : ");
            scanf(" %d",&id);
            printChain(&head,id);
            break;
        case 6://To print all molecules
            printAll(&head);
            break;
        case 7://To exit the progrmam
            printf("Thank you");
            break;
        default:
            printf("Wrong Input");
            break;
        }
    }while(a!=7);
    return 0;
}