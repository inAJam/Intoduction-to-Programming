/*
---------------------------------------Assignment-3------------------------------------------------
Aim : To simulate the recursion stack for a randomized quicksort algorithm via a stack created by 
      using a singly linked list.
Code by : Anibrata.
*/

#include <stdio.h>
#include <stdlib.h>

struct sim//structure to simulate the way quicksort works on the stack 
{
    int low;//the index of the lowest element 
    int high;//the index of the highest element
    int line;//the line number to which the comman line returns after the escape from the recursion
    struct sim* next;
};

void printStack(struct sim** head){//function to print the current stack simulation
    struct sim* x = *head;
    while(x!=NULL){//to print the proper indentation
        printf("     ");
        x=x->next;
    }
    x = *head;
    printf("{");
    while(x!=NULL){//printing the members of the stack
        printf(" (%d, %d, %d)",x->low,x->high,x->line);
        x = x->next;
        if(x!=NULL)
            printf(",");
    }
    printf(" }\n");
}

void push(struct sim** head,int l, int h,int ln){//function to insert the current simulation into the stack 
    struct sim* x = (struct sim*)malloc(sizeof(struct sim));
    x->next = NULL;
    x->low = l;
    x->high = h;
    x->line = ln;
    if(*head==NULL){//when the simulation stack is empty
        *head = x;
    }
    else{
        x->next = *head;
        *head = x;
    }
    x = *head;
    printStack(&x);//to print the stack
}

void pop(struct sim** head){//function to pop an element from the stack
    if(*head == NULL)//If stack is empty
        return;
    struct sim* a = *head;
    *head = a->next;
    a = *head;
    printStack(&a);//printing the stack
}

int qSort(int A[],int p,int r) {//function for the arrangement of the elements around the pivot
	int i=p-1;//the index at which the stack will be further divided
	int j=p;
    int k = p + (rand()%(r-p+1));//choosing a random pivot for the function
	int temp;// a temporary variable to help in the swapping of values
    temp = A[k];//swapping the pivot with the element at index 'r'
	A[k] = A[r];
	A[r] = temp;
	while(j<r) {
		if(A[j]<A[r]) {
			i++;
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
		j++;
	}
	temp = A[++i];
	A[i] = A[j];
	A[j] = temp;
	return i;//returning i
}
	
void quickSort(struct sim** head,int A[],int p,int r) {//The driver code for the quicksort
    struct sim* x = *head;
	if(p<r) {//To ensurethat the stack is valid
		int i = qSort(A,p,r);//sortting the pivot
        push(&x,p,i-1,91);//pushing the entry for the next simulation
		quickSort(&x,A,p,i-1);//dividing the array and working on it
        pop(&x);//poping the simulation node after its completed
        push(&x,i+1,r,94);//entering the next simulation
		quickSort(&x,A,i+1,r);//working on the left over part of the array
        pop(&x);//poping the final simulation node
	}
}

int main(){//main function
    struct sim* head = NULL;//The head of the simulation
    printf("Enter the number of elements : ");
    int n;//holds the number of elements
    scanf("%d",&n);
    int A[n];//the array on which quicksort will be implemented 
    printf("Enter the elements : ");
    for(int i=0;i<n;i++){
        scanf("%d",&A[i]);
    }
    printStack(&head);//printing the empty stack
    push(&head,0,n-1,109);//Starting the simulation by entering the original stack
    quickSort(&head,A,0,n-1);//calling the stack function
    pop(&head);//poping the first simulation off to give a empty stack
    printf("The final sorted array : ");//printing the sorted array
    for(int i=0;i<n;i++){
        printf("%d ",A[i]);
    }
}