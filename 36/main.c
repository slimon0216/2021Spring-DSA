#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX_LEN 100000
 
typedef struct Stack {
    int top;  // arr index of the top element
    int capacity;  //
    int size;  // # of elements
    int *arr;  // array of elements
}Stack;

struct Stack *createStack() {
    struct Stack *S = malloc(sizeof(struct Stack));
    S->capacity = MAX_LEN;
    S->top = -1;
    S->arr = (int*)malloc(S->capacity * sizeof(int));
    return S;
};

inline int isFullStack(struct Stack *S);
inline void push(struct Stack *S, int data);
inline void pop(struct Stack *S);
inline int peek(struct Stack *S);
inline int isEmpty(struct Stack *S);
inline void clear(struct Stack *S);


typedef struct Node {
    int val;
    struct Node *prev, *next;

}Node;

typedef struct DList{
    Node *head;
    Node *tail;
    int size;
    // int size;
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
    node->prev = node->next = NULL;

    if (D->size == 0) 
        D->head = D->tail = node;
    else
    {
        D->tail->next = node;
        node->prev = D->tail;
        D->tail = node; 
    }
    ++D->size;
}


void message(char* message){
    printf("%s\n", message);
}
void print(DList* D){
    if (D->size == 0)
    {
        printf("\n");
        return;
    }
    Node *ptr = D->head;
    // printf("hi %d\n", D->tail->val);
    // printf("%d ", D->tail->val);
    while (ptr != D->tail)
    {
        printf("%d ", ptr->val);
        ptr = ptr->next;
        // message("test");
    }
    assert(ptr != NULL);
    // if (ptr != NULL)
        printf("%d\n", ptr->val);
    // else printf("\n");
    
    // for (int i = 0; i < D->size; ++i)
    // {
    //     printf("%d ", ptr->val);
    //     ptr = ptr->next;
    //     assert(ptr != NULL);
    //     if (i == D->size-1)
    //         printf("\n");
    // }
}



void pop_back(DList* D){
    if (D->size == 0)
        return;
    else if (D->size == 1)  //only one node
    {
        free(D->tail);
    // message("'test'");
        D->tail = D->head = NULL;
        D->size = 0;
        // return;
    }
    else
    {
        Node *ptr = D->tail;
        ptr = ptr->prev;
        // printf("next: %d\n", ptr->next->val);
        ptr->next = NULL;
        free(D->tail);
        D->tail = ptr;
        --D->size;
    }
}

void reverse(DList* D){
    // printf("%d\n", D->size);
    if (D->size <= 1) // # of node <= 1 do nothing
        return;

    Node* ptr = D->head;
    // turn head into tail
        // printf("%d\n", ptr->val);
    ptr->prev = ptr->next;
    ptr->next = NULL;
    ptr = ptr->prev;
    Node *temp;
    // print(D);
    // message("test");
    while (ptr != D->tail)
    {
        // printf("%d\n", ptr->val);
        temp = ptr->prev;
        ptr->prev = ptr->next;
        ptr->next = temp;
        ptr = ptr->prev;
    }
    //now ptr is tail
    // printf("sdf %d\n", D->tail);

    // ptr is tail
    if (ptr != NULL)
    {
        ptr->next = ptr->prev;
        ptr->prev = NULL;
    }
    
    temp = D->head;
    D->head = D->tail;
    D->tail = temp;
    // print(D);
}
void migrate(DList* a, DList* b) // ra-th rail is shut down, and all its cabins is migrated into the rb-th
{
    if (a->size == 0)  //a has no node
        return ;
        // message("text");
    
    else if (b->size == 0)   // b has no node
    {
        reverse(a);
        b->head = a->head;
        b->tail = a->tail;
        a->tail = a->head = NULL;
        b->size = a->size;
        a->size = 0;
    }
    else
    {
        reverse(a);
        // print(a);
        b->tail->next = a->head;
        b->tail = a->tail;
        a->head = a->tail = NULL;
        b->size += a->size;
        // printf("tail %d\n", b->tail->val);
        a->size = 0;
    }
    assert(b->tail != NULL);
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
            // migrate(dl[ra], dl[rb]);
            // message("test");
        }
        // for(int i = 0; i < numOfRail_k; ++i)
        // {    
        //     // reverse(dl[i]);
        //     // printf("rail %d , size = %d: ", i, dl[i]->size);
        //     print(dl[i]);
        // // message("tes");
        // }
        //     printf("\n");
    }
    for(int i = 0; i < numOfRail_k; ++i)
    {    
        // reverse(dl[i]);
        print(dl[i]);
    }

    return 0;
}


void push(struct Stack *S, int data) {
    S->arr[++S->top] = data;
    // if (isFullStack(S))
    // enlarge(S);
};

void pop(struct Stack *S){
    --S->top;
}

int peek(struct Stack *S){
    return S->arr[S->top];
}



int isFullStack(struct Stack *S) {
    return (S->top == S->capacity-1);
};

int isEmpty(struct Stack *S){
    return (S->top == -1)? 1 : 0;
}

void clear(struct Stack *S){
    S->top = -1;
}