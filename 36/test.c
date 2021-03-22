#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX_LEN 100000

#define true 1
#define false 0
typedef int bool;


typedef struct Node {
    int val;
    struct Node* neighbor[2];
    int prev ;
    int next ;
    bool isReverse;
}Node;

typedef struct DList{
    Node *head;
    Node *tail;
    int size;
}DList;

DList* createDList(){
    DList *D = (DList*)malloc(sizeof(DList));
    D->head = D->tail = NULL;
    D->size = 0;
    return D;
}

void insert(DList* D, int val){
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->prev = 0;
    node->next = 1;
    node->neighbor[0] = node->neighbor[1] = NULL;
    node->isReverse = false;

    if (D->size == 0) 
    {
        D->head = D->tail = node;
    }
    else
    {
        if (D->tail->neighbor[D->tail->next] = NULL){
            D->tail->neighbor[D->tail->next] = node;   '''next 不一定是下一個'''
            node->neighbor[node->prev] = D->tail;
            // D->tail->isEdge = false;
            D->tail = node;
            // node->isEdge = true;
        }
        else if ( D->tail->neighbor[D->tail->prev] = NULL){
            D->tail->neighbor[D->tail->prev] = node;
            node->neighbor[node->next] = D->tail;
            D->tail = node;
        }
    }
    ++D->size;
}


void message(char* message){
    printf("%s\n", message);
}

void swap(Node *node){
    int temp = node->prev;
    node->prev = node->next;
    node->next = temp;
    message("swap");
}

void pop_back(DList* D){
    if (D->size == 0)
        return;
    else if (D->size == 1)  //only one node
    {
        free(D->tail);
        D->tail = D->head = NULL;
        D->size = 0;
    }
    else
    {
        Node *ptr = D->tail;
        if (D->tail->neighbor[D->tail->next] = NULL){
            ptr = ptr->neighbor[ptr->prev];
            ptr->neighbor[ptr->next] = NULL;
            free(D->tail);
            D->tail = ptr;
        }
        else if (D->tail->neighbor[D->tail->prev] = NULL){
            ptr = ptr->neighbor[ptr->next];
            ptr->neighbor[ptr->prev] = NULL;
            free(D->tail);
            D->tail = ptr;
        }
        --D->size;
    }
}



void reverse(DList* D){
    // if (D->isReverse == true)
    //     D->isReverse = false;
    // else D->isReverse = true;

    Node *temp = D->head;
    D->head = D->tail;
    D->tail = temp;
    D->head->isReverse = true;
    D->tail->isReverse = true;
}


void migrate(DList* a, DList* b) // ra-th rail is shut down, and all its cabins is migrated into the rb-th
{
    if (a->size == 0)  //a has no node
        return ;
        // message("text");
    
    reverse(a);
    if (b->size == 0)   // b has no node
    {
        b->head = a->tail;
        b->tail = a->head;
        a->tail = a->head = NULL;
        b->size = a->size;
        a->size = 0;
    }
    else
    {
        // check(b->tail);
        b->tail->neighbor[b->tail->next] = a->head;
        b->tail = a->tail;
        a->head = a->tail = NULL;
        b->size += a->size;
        // printf("tail %d\n", b->tail->val);
        a->size = 0;
    }
    // assert(b->tail != NULL);
}


void print(DList* D){
    if (D->size == 0)
    {
        printf("\n");
        return;
    }
    Node *curNode = D->head;
    // printf("hi %d\n", D->tail->val);
    // printf("%d ", D->tail->val);
    while (true)
    {   
        if (curNode == NULL || curNode == D->tail)
            break;
        // printf("sdf%d", NULL!=D->tail);
        printf("sdf ");
        Node* nextNode = curNode->neighbor[curNode->next];
        if (nextNode == NULL )
        {
            if ( curNode->neighbor[curNode->prev] == NULL)
            {
                message("@@@@@@@@");
                abort();
            }
            else swap(curNode);
        }
        else if (nextNode->neighbor[nextNode->next] == curNode)
        {
            message("no way");
            // swap(nex)
            abort();
        }
        
  
        printf("%d ", curNode->val);
        curNode = nextNode;
        // if (curNode == NULL) break;
        // printf("next %d\n ", nextNode);
    }
    // message("test");
    // assert(curNode != NULL);

    printf("%d\n", curNode->val);

}

char cmd[10];
int r, l, ra, rb;
int main()
{
    int numOfRail_k, numOfRec_n;
    scanf("%d %d", &numOfRail_k, &numOfRec_n);
    // printf("%d %d", numOfRail_k, numOfRec_n);
    DList **dl = malloc(sizeof(DList*) * numOfRail_k);
    for(int i = 0; i < numOfRail_k; ++i)
    {    
        int temp;
        dl[i] = createDList();
        // while (scanf("%d", &temp) != EOF)
        //     insert(dl[i], temp);
    }
    // for(int i = 0; i < numOfRail_k; ++i)
    // {    
    //     reverse(dl[i]);
    //     print(dl[i]);
    // }
    // reverse(dl[0]);
    // migrate(dl[1], dl[0]);    
    // // print(dl[0]);
    // print(dl[1]);
    // pop_back(dl[1]);
    // // print(dl[0]);
    // print(dl[1]);

    while(numOfRec_n > 0)
    {
        --numOfRec_n;
        scanf("%s", cmd);
        // message(cmd);
        if (strcmp(cmd, "enter") == 0)
        {
            scanf("%d %d", &r, &l);
            // printf("%d %d\n", r, l);
            insert(dl[r], l);
        }
        else if (strcmp(cmd, "leave") == 0)
        {
            scanf("%d", &r);
            // printf("%d\n", r);
            pop_back(dl[r]);
        }
        else if (strcmp(cmd, "migrate") == 0)
        {
            scanf("%d %d", &ra, &rb);
            // printf("%d %d\n", ra, rb);
            // reverse(dl[ra]);
            migrate(dl[ra], dl[rb]);
            // message("test");
        }
        for(int i = 0; i < numOfRail_k; ++i)
        {    
            // reverse(dl[i]);
            printf("rail %d , size = %d: ", i, dl[i]->size);
            print(dl[i]);
        // message("tes");
        }
            printf("\n");
    }
    for(int i = 0; i < numOfRail_k; ++i)
    {    
        // reverse(dl[i]);
        print(dl[i]);
    }

    return 0;
}

