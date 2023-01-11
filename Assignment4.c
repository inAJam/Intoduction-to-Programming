/*
---------------------------------------Assignment-4------------------------------------------------
Aim : To simulate a round robin algorithm starting with a queue size of 100 and adding 64, 32,...1 
      new jobs after every 200μs, with the time quantum being 50μs, and printing the queue after 
      every time quantum passes.

Note : ->Output followed is the one specified by Supreet Singh and printed to the console.
       ->The output size and the adding of jobs can't be changed by the user and has to be changed
          from within the program.
       ->Change the values at int num(int time) for changing the size of the input. 
Code by : Anibrata.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node//Structure to hold the individual jobs
{
    int ID;//ID of the queue
    int time;//Time needed to complete the execution of the job
    struct node* next;//points to the next job in the queue
};

struct queue//Structure to hold the queue object
{
    struct node* head;//The head of the queue
    struct node* tail;//The tail of the queue
};

void printQueue(int time,struct queue** first){//Function to print the queue
    struct queue* s = *first;//temporary queue to hold the original queue 
    struct node* n = s->head;//temporary node
    if(time==0){//If time is zero
        printf("Initial queue:  ");
    }
    else{
        printf("Queue at the end of %d μs:  ",time);
    }
    if(*first==NULL || s->head==NULL){//When queue is empty
        printf(" Empty;\n\n");
        return;
    }
    while(n!=NULL){//Printing the queue
        printf(" J%d:%d;",n->ID,n->time);
        n= n->next;
    }
    printf("\n\n\n");
}

void addJob(struct queue* s,int index){//Function to add a new job at the end of the queue
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->next = NULL;//setting the default values
    n->ID  = index;//Storing the job ID
    n->time = (rand()%300)+1;//Allocating a random time value between 1 to 300
    if(s->head == NULL){//When the queue is empty
        s->head = n;
        s->tail = n;
    }
    else{
        s->tail->next = n;
        s->tail = n;
    }
}

void addBatch(int number,int lastIndex,struct queue** s){//Function to add a whole batch of jobs by forming a queue and appending it
    if(number==0) return;//If number of jobs to be appended is zero
    struct queue* temp = (struct queue*)malloc(sizeof(struct queue));//Alloctaing memory to a temporary queue
    temp->head=NULL;
    temp->tail = NULL;
    struct queue* first = *s;
    srand(time(0));
    for(int i=1;i<=number;i++){//Adding the jobs
        addJob(temp,lastIndex+i);
    }
    if (*s==NULL)//appending the queue
        *s = temp;
    else{
        first->tail->next = temp->head;
        first->tail = temp->tail;
    }
}

int num(int time){//function to generate the number of jobs to be added based on time
    if(time==0)//to add 100 jobs at the start
        return 100;
    time = time/200;
    int l=128;
    for(int i=0;i<time;i++)//Adding a multiple of 2 jobs based on the time
        l = l/2;
    return l; 
}

void roundRobin(){//Function for the round robin algorithm implementation
    int time = 0;//the total run time of the algorithm
    int length = 0;//length of the queue
    int temp = 0;
    struct queue* jobs = NULL;//The queue on which the round robin is to be implemented
    struct node* swap = NULL;
    int i=0;//to keep a track of time allocated to a job
    do{
        if(i==50){//when the time allocated is equal to the given quantum
            i=0;
            swap = jobs->head;
            if(jobs->head->time>0){//Appending head to the tail when the head job is not completed 
                jobs->tail->next = swap;
                jobs->tail = swap;
            }
            jobs->head = swap->next;//making the next in line the head
            swap->next = NULL;
        }
        if(time%200==0){
            temp= num(time);//finding the number of jobs to attach
            addBatch(temp,length,&jobs);//adding a batch of jobs
            if(length == 0){
                printf("Created 100 jobs:\n\n\n");
                printQueue(time,&jobs);//printing the queue
            }
            else if (temp!=0){
                printf("******%d μs passed, added %d jobs to the end\n\n\n",time,temp);
                printf("After addition:\n\n");
                printQueue(time,&jobs);
            }
            length = temp+length;//updating the length
        }
        i++;//incrementing individual job counter
        time++;//incrementingthe total time counter
        if(jobs->head->time==0){//If a job is completed then moving on to the next job
            jobs->head = jobs->head->next;
            i=1;//resetting the counter
        }
        if(jobs->head==NULL){//when queue is empty
            while(time%50!=0) time++;//rounding off time to the next 50
            printQueue(time,&jobs);
            return;
        }
        jobs->head->time--;
        if(time%50==0)
            printQueue(time,&jobs);
    }while(jobs!=NULL);
}

int main(){//Main function 
    roundRobin();//calling the roundRobin function
} 