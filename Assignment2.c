/*
---------------------------------------Assignment-2------------------------------------------------
Aim : To create a program to read data from files and to store it in a corresponding matrix as per
      the conditions specified,check the matrix for symmetricity and other such properties.
Code by : Anibrata.
*/

#include <stdio.h>
#include <stdlib.h>

struct row//structure to store rows of the matrix
{
    int id;//row number
    struct column* across;
    struct row* next;
};

struct column//Structure to store columns of the matrix
{
    int id;//column number
    int data;//value stored in column
    struct column* across;
};

void appenRow(struct row** head){//Function to add a row to 'head'
    struct row* n = (struct row*) malloc(sizeof(struct row));
    n->next = NULL;
    n->across = NULL;
    if(*head==NULL){//If 'head' is empty
        n->id = 1;
        *head = n;
        return;
    }
    int i=2;
    struct row* temp = *head;
    while (temp->next!=NULL){//Finding the place where row is to be entered
        temp = temp->next;
        i++;
    }
    n->id = i;
    temp->next = n;
}

void insert(struct row** head,int r,int value){//function to insert column in a matrix
    struct row* temp = *head;
    while(temp->id!=r) temp = temp->next;//Finding the row at which a column is to be entered
    struct column* n = (struct column*) malloc(sizeof(struct column));
    n->across = NULL;
    n->data = value;
    if(temp->across==NULL){//If column field is empty
        n->id = 1;
        temp->across = n;
        return;
    }
    struct column* c = temp->across;
    int i=2;
    while(c->across!=NULL) {//Finding the location after which the column is entered
        c = c->across;
        i++;
    }
    n->id = i;
    c->across = n;
}

int cellValue(struct row** head,int r,int c){//Function to return the value stored at row 'r' and column 'j'
    struct row* n = *head;
    while(n->id!=r) n = n->next;//finding the row
    struct column* m = n->across;
    while(m->id!=c) m = m->across;//finding the column
    return (m->data);
}

void symmetric(struct row** head,int l){//function to check whether a square matrix is symmetric 
    struct row* n = *head;
    l++;
    for(int i=1;i<l;i++){
        for(int j=1;j<l;j++){
            if(cellValue(&n,i,j)!=cellValue(&n,j,i)){//checking the values of the matrix
                printf("The matrix is not symmetric\n");
                return;
            }
        }
    }
    printf("The matrix is symmetric\n");
}

void multiply(){//Function to multiply two matrices
    struct row* X = NULL;//The first matrix
    struct row* Y = NULL;//The second matrix
    int value;
    char s,t;
    FILE *fptr;
    fptr=fopen("Matrix2.txt","r");//The file from which the values are to be read
    int xr=1,xc=1;t='a';
    appenRow(&X);//Appending a row at the end
    while(fscanf(fptr,"%d%c",&value,&s)!=EOF){
        if(t==';'){//To add a new row to the matrix
            xr++;
            appenRow(&X);
            xc=1;
        }
        xc++;//Increasing column count by 1;
        insert(&X,xr,value);
        t = s;
    }
    xc--;//The number of columns in the matrix 'X'
    fclose(fptr);
    fptr=fopen("Matrix3.txt","r");//The file which holds the data for matrix 'Y'
    int yr=1,yc=1;t='a';
    appenRow(&Y);
    while(fscanf(fptr,"%d%c",&value,&s)!=EOF){
        if(t==';'){
            yr++;
            appenRow(&Y);
            yc=1;
        }
        yc++;
        insert(&Y,yr,value);
        t = s;
    }
    yc--;//The number of columns in 'Y'
    fclose(fptr);
    if(xc!=yr){//When the number of rows of 'Y' is not equal to the number of columns of 'X'
        printf("Matrix Multiplication not possible");
        return;
    }
    fptr=fopen("MOutput.txt","w");//The file to which the output is written
    int sum=0;
    for(int i=1;i<=xr;i++){
        for(int j=1;j<=yc;j++){
            for(int k=1;k<=yr;k++){
                sum = sum + cellValue(&X,i,k)*cellValue(&Y,k,j);//finding the multiplication
            }
            fprintf(fptr,"%d",sum);//Writing the output to the file
            if(j!=yc) fprintf(fptr,",");
            sum=0;
        }
        if(i!=xr) fprintf(fptr,";");
    }
    fclose(fptr);
}

void check(){//Function to check whether the following matrix is square and symmetric 
    struct row* X = NULL;
    int value;//The value of the matrix
    char s,t;
    FILE *fptr;
    fptr=fopen("Matrix1.txt","r");//File from which the values are read
    int i=1,j=1,max =0,min = 100000;t='a';
    appenRow(&X);
    while(fscanf(fptr,"%d%c",&value,&s)!=EOF){
        if(t==';'){
            i++;
            appenRow(&X);
            if(j>max) max=j;
            if(j<min) min=j;
            j=1;
        }
        j++;
        insert(&X,i,value);
        t = s;
    }
    max--;
    min--;
    fclose(fptr);
    if(max!=min){//To ensure that all the rows have the same number of columns
        printf("The given data is not a matrix");
    }
    else if(i==max){
        printf("Its a square matrix\n");
        symmetric(&X,i);
    }
    else printf("Its not a square matrix\n");
}

int main()//main function
{
    int ch;//To store the choice of the user
    do{
         printf("Menu :\n1.To check whether a matrix is square and symmetric\n2.To multiply two matrices\n3.Quit\nEnter your Choice : ");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            check();
            break;
        case 2:
            multiply();
            break;
        case 3:
            printf("Exiting the program");
            break;
        default://for wrong choice
            printf("Wrong choice.Try again\n");
            break;
        }

    }while(ch!=3);
    return 0;
}

