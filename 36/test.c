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
        if (D->tail->neighbor[D->tail->next] == NULL){
            D->tail->neighbor[D->tail->next] = node;   //'''next 不一定是下一個'''
            node->neighbor[node->prev] = D->tail;
            // D->tail->isEdge = false;
            D->tail = node;
            // node->isEdge = true;
        }
        else if ( D->tail->neighbor[D->tail->prev] == NULL){
            D->tail->neighbor[D->tail->prev] = node;
            node->neighbor[node->next] = D->tail;
            D->tail = node;
        }
        // assert(1 == 2);
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
        if (D->tail->neighbor[D->tail->next] == NULL){
            ptr = ptr->neighbor[ptr->prev];
            ptr->neighbor[ptr->next] = NULL;
            free(D->tail);
            D->tail = ptr;
        }
        else if (D->tail->neighbor[D->tail->prev] == NULL){
            ptr = ptr->neighbor[ptr->next];
            ptr->neighbor[ptr->prev] = NULL;
            free(D->tail);
            D->tail = ptr;
        }
        --D->size;
    }
}



void reverse(DList* D){
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
    
    
    if (b->size == 0)   // b has no node
    {
        b->head = a->tail;
        b->tail = a->head;
        a->tail = a->head = NULL;
        b->size = a->size;
        a->size = 0;
        // assert(2 == 3);
    }
    else  //  b has at least one node
    {
        reverse(a);
        if (b->tail->neighbor[b->tail->next] == NULL){
            b->tail->neighbor[b->tail->next] = a->head;
            if (a->head->neighbor[a->head->prev] == NULL){
                a->head->neighbor[a->head->prev] = b->tail;
            }
            else if (a->head->neighbor[a->head->next] == NULL){
                a->head->neighbor[a->head->next] = b->tail;
            }
            // else
            //     assert(3 == 4);
            b->tail = a->tail;
            a->head = a->tail = NULL;
            b->size += a->size;
            a->size = 0;
        }
        else if (b->tail->neighbor[b->tail->prev] == NULL){
            b->tail->neighbor[b->tail->prev] = a->head;
            b->tail = a->tail;
            if (a->head->neighbor[a->head->next] == NULL){
                a->head->neighbor[a->head->next] = b->tail;
            }
            else if (a->head->neighbor[a->head->prev] == NULL){
                a->head->neighbor[a->head->prev] = b->tail;
            }
        }
        // else{
        //     assert(2 == 3);
        // }
            a->head = a->tail = NULL;
            b->size += a->size;
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
    Node *prevNode = D->head;
    while (true)
    {   
        // if (curNode == NULL)
        //     assert(1==2);
        if (curNode == D->tail){
            printf("%d\n", curNode->val);
            // printf("end\n");
            break;
        }
        // printf("sdf ");
        Node *nextNode = NULL;   //你確定 next 真的是next?
        if (curNode->neighbor[curNode->prev] == NULL){  //如果curnode的prev是NULL，next就是下一個
            nextNode = curNode->neighbor[curNode->next];
        }
        else if (curNode->neighbor[curNode->next] == NULL){  //不然如果curnode的next是NULL，prev就是下一個
            nextNode = curNode->neighbor[curNode->prev];
        }
        else if (curNode->neighbor[curNode->next] == prevNode){   //不然如果curnode的next是上一個node,prev就是下一個
            nextNode = curNode->neighbor[curNode->prev];
        }
        else if (curNode->neighbor[curNode->prev] == prevNode){  //不然如果curnode的prev是上一個node,next就是下一個
            nextNode = curNode->neighbor[curNode->next];
        }
        // else
        //     assert(1==2);
        else
            printf("next node is %d  ",curNode->neighbor[curNode->next]->val);
        // now nextNode is the True nextNode

        printf("%d ", curNode->val);
        assert(nextNode!=NULL);
        prevNode = curNode;
        curNode = nextNode;

    }

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
            printf("rail %d , size = %d: ", i, dl[i]->size);
            print(dl[i]);
        // message("tes");
            if (dl[i]->size > 1 ){
            assert((dl[i]->head->neighbor[dl[i]->head->next] != NULL) || (dl[i]->head->neighbor[dl[i]->head->prev]!= NULL));
            assert((dl[i]->tail->neighbor[dl[i]->tail->next] != NULL) || (dl[i]->tail->neighbor[dl[i]->tail->prev] != NULL));
            }
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

