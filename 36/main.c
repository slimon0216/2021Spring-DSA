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
    S->size = 0;
    return S;
};

inline int isFullStack(struct Stack *S);
inline void push(struct Stack *S, int data);
inline void pop(struct Stack *S);
inline int peek(struct Stack *S);
inline int isEmpty(struct Stack *S);
inline void clear(struct Stack *S);

inline void print(Stack *s);

char cmd[10];
int r, l, ra, rb;
int main()
{
    int numOfRail_k, numOfRec_n;
    scanf("%d %d", &numOfRail_k, &numOfRec_n);
    // printf("%d %d", numOfRail_k, numOfRec_n);
    Stack **stack_arr = malloc(sizeof(Stack*) * numOfRail_k);
    for(int i = 0; i < numOfRail_k; ++i)
    {    
        // int temp;
        stack_arr[i] = createStack();
    }
 
    while(numOfRec_n > 0)
    {
        --numOfRec_n;
        scanf("%s", cmd);
        // message(cmd);
        if (cmd[0] == 'e')  //enter
        {
            scanf("%d %d", &r, &l);
            push(stack_arr[r], l);
        }
        else if (cmd[0] == 'l') //leave
        {
            scanf("%d", &r);
            pop(stack_arr[r]);
        }
        else  //migrate
        {
            scanf("%d %d", &ra, &rb);
            while(!isEmpty(stack_arr[ra]))
            {
                push(stack_arr[rb], peek(stack_arr[ra]));
                pop(stack_arr[ra]);
            }
        }
            // printf("\n");
        // for(int i = 0; i < numOfRail_k; ++i)
        // {    
        //     // reverse(stack_arr[i]);
        //     printf("rail %d: ", i);
        //     print(stack_arr[i]);
        // // message("tes");
        // }
        //     printf("\n");
            // printf("\n");
    }
    for(int i = 0; i < numOfRail_k; ++i)
    {    
        // reverse(stack_arr[i]);
        print(stack_arr[i]);
    }

    return 0;
}


void push(struct Stack *S, int data) {
    S->arr[++S->top] = data;
    ++S->size;
    // if (isFullStack(S))
    // enlarge(S);
};

void pop(struct Stack *S){
    if (isEmpty(S))
        return;
    --S->top;
    --S->size;
}

int peek(struct Stack *S){
    return S->arr[S->top];
}



int isFullStack(struct Stack *S) {
    return (S->top == S->capacity-1);
};

int isEmpty(struct Stack *S){
    return S->size == 0;
}

void clear(struct Stack *S){
    S->top = -1;
    S->size = 0;
}

void print(Stack *s){
    if (isEmpty(s))
    {
        printf("\n");
        return;
    }
    int len = s->size;
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", s->arr[i]);
        if (i == len-1)
            printf("\n");
    }
    // printf("\n");
}