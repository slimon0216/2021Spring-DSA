#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include <assert.h>

typedef struct Node {
    int val;
    struct Node *prev, *next;
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

inline void insert(DList *D, int *val);

inline void pop_back(DList *D);
inline void reverse(DList *D);
inline void migrate(DList *a, DList *b);
inline void print(DList *D);

char cmd[10];
int r, l, ra, rb, i, numOfRail_k, numOfRec_n, cnt;
DList *dl[1000];

int main()
{
    scanf("%d %d", &numOfRail_k, &numOfRec_n);
    // for(i = 0; i < numOfRail_k; ++i){    
    //     dl[i] = createDList();
    // }
    i = numOfRail_k;
    while (--i){
        dl[i] = createDList();
    }
    dl[0] = createDList();

    cnt = numOfRec_n;
    char flag;
    while(cnt){
        --cnt;
        scanf("%s", cmd);
        flag = cmd[0];
        switch(flag) {
        case 'e':
            scanf("%d %d", &r, &l);
            insert(dl[r], &l);
            break;
        case 'l':
            scanf("%d", &r);
            pop_back(dl[r]);
            break;
        case 'm':
            scanf("%d %d", &ra, &rb);
            migrate(dl[ra], dl[rb]);
            break;
        }
        // for(int i = 0; i < numOfRail_k; ++i)
        // {    
        //     printf("rail %d , size = %d: ", i, dl[i]->size);
        //     print(dl[i]);
        // // message("tes");
        //     if (dl[i]->size > 1 ){
        //     assert((dl[i]->head->next != NULL) || (dl[i]->head->prev != NULL));
        //     assert((dl[i]->tail->next != NULL) || (dl[i]->tail->prev != NULL));
        //     }
        // }
        // printf("\n");
    }
    for(i = 0; i < numOfRail_k; ++i)
        print(dl[i]);
    return 0;
}

void insert(DList* D, int *val){
    Node *node = malloc(sizeof(Node));
    node->val = *val;
    node->prev = node->next = NULL;

    if (!D->size) 
        D->head = D->tail = node;
    else
    {
        if (!D->tail->next){
            D->tail->next = node;   //'''next 不一定是下一個'''
            node->prev = D->tail;
            D->tail = node;
        }
        // else if (!D->tail->prev)
        else
        {
            D->tail->prev = node;
            node->next = D->tail;
            D->tail = node;
        }
    }
    ++D->size;
}

void print(DList* D){
    if (!D->size)
    {
        printf("\n");
        return;
    }
    Node *curNode = D->head;
    Node *prevNode = D->head;
    while (1)
    {   
        if (curNode == D->tail){
            printf("%d\n", curNode->val);
            break;
        }
        // printf("sdf ");
        Node *nextNode = NULL;   //你確定 next 真的是next?
        if (!curNode->prev ){  //如果curnode的prev是NULL，next就是下一個
            nextNode = curNode->next;
        }
        else if (!curNode->next){  //不然如果curnode的next是NULL，prev就是下一個
            nextNode = curNode->prev;
        }
        else if (curNode->next == prevNode){   //不然(prev, next都不是NULL)如果curnode的next是上一個node,prev就是下一個
            nextNode = curNode->prev;
        }
        else if (curNode->prev == prevNode){  //不然如果curnode的prev是上一個node,next就是下一個
            nextNode = curNode->next;
        }

        // now nextNode is the True nextNode
        printf("%d ", curNode->val);
        prevNode = curNode;
        curNode = nextNode;
    }
}


void migrate(DList* a, DList* b) // ra-th rail is shut down, and all its cabins is migrated into the rb-th
{
    if (!a->size)  //a has no node
        return ;
    
    else if (!b->size)   // b has no node
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
        if (!b->tail->next ){
            b->tail->next = a->head;
            if (!a->head->prev ){
                a->head->prev = b->tail;
            }
            // else if (!a->head->next )
            else
            {
                a->head->next = b->tail;
            }
        }
        // else if (!b->tail->prev )
        else
        {
            b->tail->prev = a->head;
            if (!a->head->next ){
                a->head->next = b->tail;
            }
            // else if (!a->head->prev )
            else
            {
                a->head->prev = b->tail;
            }
        }
        b->tail = a->tail;
        a->head = a->tail = NULL;
        b->size += a->size;
        a->size = 0;
    }
}

void reverse(DList* D){
    Node *temp = D->head;
    D->head = D->tail;
    D->tail = temp;
}


void pop_back(DList* D){

    if (D->size)
    {
        if (D->size == 1)  //only one node
        {
            // free(D->tail);
            D->tail = D->head = NULL;
            D->size = 0;
            return;
        }
        Node *ptr = D->tail;
        if (!D->tail->next ){
            ptr = ptr->prev;
            if (ptr->next == D->tail)
                ptr->next = NULL;
            else
                ptr->prev = NULL;
            // free(D->tail);
            D->tail = ptr;
            // message("not reverse");
        }
        // else if (!D->tail->prev )
        {
            ptr = ptr->next;
            if (ptr->prev == D->tail)
                ptr->prev = NULL;
            else
                ptr->next = NULL;

            // free(D->tail);
            D->tail = ptr;
            // message("reverse");
        }
        --D->size;
    }
    else
        return;
    
}