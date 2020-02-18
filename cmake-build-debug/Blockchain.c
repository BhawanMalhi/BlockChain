#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Block {
    char data[256];
    int prevHash;
    int hash;
    int nonce;
    struct Block *next;
}block;


int calculateHash(char Data[], long currentTime, int previousHash) {
    char dataToHash[256];
    sprintf(dataToHash,"%s%ld%d",Data,currentTime,previousHash);

    int hash = 0;
    int c;
    for(int i=0;i<strlen(dataToHash);i++){
        hash = hash ^ dataToHash[i];
        hash = hash *0x123456789;
    }

    return hash;
}

//print the linked list
void displayList(block *node){

    //if empty list
    if(node==NULL)
        printf("Empty chain");

    //traverse the list and print it
    printf(" Chain is \n");
    printf("----------\n");
    while (node != NULL)
    {
        printf(" Block data: %s\n Previous Hash: %d\n Hash: %d\n ",node->data,node->prevHash,node->hash);
        node = node->next;
        printf("----------\n");
    }

}

void displaySearch(block *node){

    //if empty list
    if(node==NULL)
        printf("Empty chain");

    //traverse the list and print it
    printf("----------\n");

        printf(" Block data: %s\n Previous Hash: %d\n Hash: %d\n ",node->data,node->prevHash,node->hash);
        node = node->next;
        printf("----------\n");

}



void insertLast(struct Block** head_ref, char new_data[256],long currentTime)
{// allocate node
    struct Block* new_block = (struct Block*) malloc(sizeof(struct Block));

    struct Block *last = *head_ref;

    // put in the data
    strcpy(new_block->data,new_data);


    new_block->hash = calculateHash(new_block->data, currentTime, new_block->hash);

    //make new node's last null
    new_block->next = NULL;

    // If empty, then make the new node as head
    if (*head_ref == NULL)
    {
        *head_ref = new_block;
        new_block->prevHash = 0;
        return;
    }

    // Else traverse till the last node
    while (last->next != NULL)
        last = last->next;

    // Change the next of last node
    last->next = new_block;
    new_block->prevHash = last->hash;
    return;
}

void valid(block  *ptr)
{
    if (ptr==NULL) //Reached end of the list
    {
        printf("\n  Empty Chain \n");

    }
     if(ptr->hash = ptr->next->prevHash) { //found the element
         printf("CHAIN IS VALID!\n");
    } else { //search next element
        return valid(ptr->next);   //this will call your function again for the next element on the list
    }
}


int mine_block(char data[],long time,int prevHash){
    int nonce  =0;
    int hash;
    char dataTohash[256];
    while(1){
        sprintf(dataTohash,"%s%d%d",data,nonce);
        hash = calculateHash(dataTohash,time,prevHash);

        while (hash >= 10)
            hash /= 10;

        if(hash == 00){
            return nonce;
        }
        nonce++;
        printf("%d",hash);
    }
    return nonce;
}


void insertMineBlock(struct Block** head_ref, char new_data[256],long currentTime)
{// allocate node
    struct Block* new_block = (struct Block*) malloc(sizeof(struct Block));

    struct Block *last = *head_ref;
    // put in the data
    strcpy(new_block->data,new_data);

    char dataToHasho[256];
    sprintf(dataToHasho,"%s%ld%d",new_block->data,currentTime,new_block->hash);

    new_block->nonce=mine_block(dataToHasho,currentTime,new_block->prevHash);
    new_block->hash = calculateHash(new_block->data, currentTime, new_block->hash);

    //make new node's last null
    new_block->next = NULL;

    // If empty, then make the new node as head
    if (*head_ref == NULL)
    {
        *head_ref = new_block;
        new_block->prevHash = 0;
        return;
    }

    // Else traverse till the last node
    while (last->next != NULL)
        last = last->next;

    // Change the next of last node
    last->next = new_block;
    new_block->prevHash = last->hash;
    return;
}


struct block *searchname(block  *ptr, char *name)
{
    if (ptr==NULL) //Reached end of the list
    {
        printf("\n  not found \n");
        return NULL;
    }
    if (strcmp(name, ptr->data) == 0) { //found the element
        printf("\n name found \n");
        printf("\n details are -\n");
        displaySearch(ptr);
        return ptr;
    } else { //search next element
        return searchname(ptr->next,name);   //this will call your function again for the next element on the list
    }
}


void exitLoop(block * head)
{
    while(head)
    {
        struct Node *t = head;
        head = head->next;
        free(t);
    }
}

int main() {

    time_t currentTime;
    // Get the current time (epoch time)
    // Epoch time = number of seconds that have passed since the year 1970.
    currentTime = time(NULL);
    printf("Current epoch time is: %ld\n", currentTime);
    printf("----------\n");

     block* head = NULL;
     int op;
     char last[256];
     char key[256];
     block *ptr;

     do
     {
         printf("\n\n choose an option: \n");
         printf("\n 1. add a new block to the chain ");
         printf("\n 2. view the chain");
         printf("\n 3. check chain validity ");
         printf("\n 4. search for a block ");
         printf("\n 5. mine new block");
         printf("\n 0. exit");
         printf("\n select your option:\n");
         scanf("%d",&op);


         switch(op)
         {
             case 1:     // display link list
                 last[256];
                 printf("\nEnter data :");
                 scanf("%s",&last);
                 insertLast(&head,last,currentTime);
                 break;
             case 2:
                 displayList(head);
                 break;
             case 3:
                 valid(head);
                 break;
             case 4:
                 key[256];
                 printf("Enter name you want to search-- ");
                 scanf("%s", &key);
                 ptr = searchname(head, key);
                 break;
             case 5:
                 insertMineBlock(&head,last,currentTime);
                 break;
             case 0:
                 exit(head);
                 return 0;
         }

     } while (1);

    return 0;
}


