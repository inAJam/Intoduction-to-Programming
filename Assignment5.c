/*
-----------------------------------------Assignment-5--------------------------------------------------
Aim : To create a program to check the validity of a given infix expression and if valid, to convert it
      into postfix and evaluate it using stacks(linked-list implementation).
Code by : Anibrata.
*/

//including the important libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct stack//structure to enable the stack/list
{
    int type;//type of value stored: 0-character;1-number
    char symbol;//to store the character: 
    int value;//to store the number
    struct stack* next;//pointer storing the address of the next stack link
};

void push(struct stack** head,int type,int value,char symbol,int place){//function to push a node into the stack or append a node
    struct stack* temp = (struct stack*)malloc(sizeof(struct stack));
    temp->next = NULL;
    temp->symbol = symbol;
    temp->value = value;
    temp->type = type;
    if(*head==NULL){
        *head = temp;
        return;
    }
    if(place==0){//pushes a node into the stack
        temp->next = *head;
        *head = temp;
        return;
    }
    struct stack* n = *head;
    while(n->next!=NULL)//to append a node at the end of the stack
        n=n->next;
    n->next = temp;
}

void pop(struct stack** head){//function to pop a node 
    if(*head==NULL){
        return;
    }
    struct stack* s = *head;
    s = s->next;
    *head = s;
}

int check(char* s){//to check the validity if the infix expression
    struct stack* brackets = NULL;//to check for validity of brackets
    int l = strlen(s);//the length of the string
    int j=1;//to keep count of the number of symbols 
    for(int i=0;i<l;i++){
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^'){
            j++;
            if(i==l-1||s[i+1]=='+'||s[i+1]=='-'||s[i+1]=='*'||s[i+1]=='/'||s[i+1]=='^'){
                printf("Invalid input: incorrect use of binary operators at symbol %d.\n",j);
                return -1;//to check for continuous operators or if the expressions end in an operator
            }
            if(i!=l-1 ){
                if(s[i+1]==']'||s[i+1]=='}'||s[i+1]==')'){
                    printf("Invalid input: absense of operand after symbol %d.\n",j-1);
                    return -1;//to check for operator followed by closing brackets : *],^},etc.
                }
            }
        }else if(isdigit(s[i])){
            if(i!=0 ){
                if(s[i-1]==']'||s[i-1]=='}'||s[i-1]==')'){
                    printf("Invalid input: absense of binary operators after symbol %d.\n",j-1);
                    return -1;//to check for absense of operators: ]7, }5, etc.
                }
            }
            j++;
        }
        else if(s[i]=='['||s[i]=='{'||s[i]=='('){
            if(i!=0 && isdigit(s[i-1])){
                printf("Invalid input: absense of binary operators after symbol %d.\n",j-1);
                return -1;//to check for absense of operators: 6[, 7{, etc.
            }
            if(i<l-1){
                if(s[i+1]=='+'||s[i+1]=='-'||s[i+1]=='*'||s[i+1]=='/'||s[i+1]=='^'){
                    printf("Invalid input: absense of operand at symbol %d.\n",j);
                    return -1;//to check for absense of operands: (+, [-, etc.
                }
            }
            push(&brackets,0,0,s[i],0);//pushing the braces into the brackets stack
        }
        else if(s[i]==']'||s[i]=='}'||s[i]==')'){//popping the brackets stack when an enclosing braces is found
            if(brackets->symbol=='(' && s[i]==')')
                pop(&brackets);
            else if(brackets->symbol=='{' && s[i]=='}')
                pop(&brackets);
            else if(brackets->symbol=='[' && s[i]==']')
                pop(&brackets);
            else {
                printf("Invalid input: unmatched '%c' found at symbol number %d.\n",brackets->symbol,j);
                return -1;
            }
        }
        else{//to check for the presense of unknown symbols: a, &, etc.
            printf("Invalid input: unknown symbol '%c' found at symbol number %d.\n",s[i],j);
            return -1;
        }
    }
    if(brackets!=NULL)//if unmatched brackets exist
        return -1;
    printf("Valid\n");
    return l;
}

int calc(int a,int b,char c){//function to calculate the result between a and b
    switch (c)
    {
    case '+':
        return (a+b);
    case '-':
        return(a-b);
    case '*':
        return (a*b);
    case '/':
        return(a/b);
    default:
        a = (int)(pow(a,b));
        return a;
    }
}

void result(struct stack **head){//function to find the result of the postfix expression
    struct stack* n = *head;//the postfix stack
    struct stack* r = NULL;//result stack
    int a,b;
    while(n!=NULL){
        if(n->type==1)
            push(&r,1,n->value,' ',0);//pushing the value into the result stack when it's a number
        else{//when a operator is found then popping two values and pushing in the result of them into the stack
            b = r->value;
            pop(&r);
            a = r->value;
            pop(&r);
            push(&r,1,calc(a,b,n->symbol),' ',0);
        }
        n = n->next;
    }
    printf("\n%d\n",r->value);//printing the final result
}

void print(struct stack** head){//function to print the stack
    struct stack* s = *head;
    while(s!=NULL){
        if(s->type==0)
            printf("%c ",s->symbol);
        else
            printf("%d ",s->value);
        s = s->next;
    }
}

void infixToPostfix(char* s,int l){//function to transform infix to postfix
    struct stack* operator = NULL;//the stack of operators
    push(&operator,0,0,'a',0);//pushing a default value into the stack to prevent empty stack
    struct stack* postfix = NULL;//the list storing the postfix value; values are appended to the list
    int j=0;//flag to ensure multidigit numbers are read properly
    int num=0;//to store the multi digit number
    for(int i=0;i<l;i++){
        if(j==1 && !(isdigit(s[i]))){//when the next char is not a digit
            push(&postfix,1,num,' ',1);
            num = 0;
            j = 0;
        }
        if(s[i]=='^')//if '^' is found then pushing it into the operator stack
            push(&operator,0,0,s[i],0);
        else if(s[i]=='/'){
            while(operator->symbol=='^'){
                push(&postfix,0,0,operator->symbol,1);//appending the '^' to the list
                pop(&operator);//popping out all '^' form the operator stack
            }
            push(&operator,0,0,s[i],0);//pushing the '/' into the stack
        }//doing it for the rest of the symbols
        else if(s[i]=='*'){
            while(operator->symbol=='^'||operator->symbol=='/'){
                push(&postfix,0,0,operator->symbol,1);
                pop(&operator);
            }
            push(&operator,0,0,s[i],0);
        }
        else if(s[i]=='+'){
            while(operator->symbol=='^'||operator->symbol=='/'||operator->symbol=='*'){
                push(&postfix,0,0,operator->symbol,1);
                pop(&operator);
            }
            push(&operator,0,0,s[i],0);
        }
        else if(s[i]=='-'){
            while(operator->symbol=='^'||operator->symbol=='/'||operator->symbol=='*'||operator->symbol=='+'){
                push(&postfix,0,0,operator->symbol,1);
                pop(&operator);
            }
            push(&operator,0,0,s[i],0);
        }
        else if(s[i]=='['||s[i]=='{'||s[i]=='('){
            push(&operator,0,0,s[i],0);
        }//if ending braces are found then popping the stack until the open brace is eliminated
        else if(s[i]==']'||s[i]=='}'||s[i]==')'){
            while(operator->symbol!='('&& operator->symbol!='{'&& operator->symbol!='['){
                push(&postfix,0,0,operator->symbol,1);
                pop(&operator);
            }
            pop(&operator);//popping the open brace
        }
        else{//when a digit is found after a char
            j=1;
            num = num*10 + (s[i]-'0');
        }
    }
    if (j==1){//to ensure all digits are stored
        push(&postfix,1,num,' ',1);
    }
    while(operator->symbol!='a'){//while the default operator stack node is not reached popping all values
        push(&postfix,0,0,operator->symbol,1);//appending the values to the list
        pop(&operator);
    }
    print(&postfix);//printing the postfix expression
    result(&postfix);//to find and print the result of the postfix expression
}

int main(){//main function
    char s[1000];//to store the infix expression
    printf("Enter the infix expression: "); 
    scanf("%s", s);
    int l = check(s);//checking the expression
    if(l==-1){//if invalid expression is entered
        return 0;
    }
    infixToPostfix(s,l);
}