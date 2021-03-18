#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAX_LEN 100000
#define false 0  
#define true  1 
typedef int bool;  

typedef struct Stack Stack;
typedef struct operatorStack operatorStack;

struct Stack {
    int top;  // arr index of the top element
    int capacity; 
    int size;  // # of elements
    double *arr;  // array of elements
};

struct Stack *createStack() {
    struct Stack *S = malloc(sizeof(struct Stack));
    S->capacity = MAX_LEN;
    S->top = -1;
    S->arr = (double*)malloc(S->capacity * sizeof(double));
    return S;
};

bool isFullStack(struct Stack *S) {
    return (S->top == S->capacity-1);
};

// void enlarge(struct Stack *S) {
//     int new_capacity = (S->capacity * 3);
//     S->capacity = new_capacity;
//     S->arr = (int*)realloc(S->arr, new_capacity * sizeof(int));
// };

void push(struct Stack *S, double data) {
    S->arr[++S->top] = data;
    // if (isFullStack(S))
    // enlarge(S);
};

void pop(struct Stack *S){
    --S->top;
}

double peek(struct Stack *S){
    return S->arr[S->top];
}

bool isEmpty(struct Stack *S){
    return (S->top == -1)? true : false;
}

///////////////////////////////////////////////

struct operatorStack {
    int top;  // arr index of the top element
    int capacity; 
    int size;  // # of elements
    char *arr;  // array of elements
};

struct operatorStack *createOperatorStack() {
    struct operatorStack *S = malloc(sizeof(struct operatorStack));
    S->capacity = MAX_LEN;
    S->top = -1;
    S->arr = (char*)malloc(S->capacity * sizeof(char));
    return S;
};

int isFullOperatorStack(struct operatorStack *S) {
    return (S->top == S->capacity-1);
};

// void enlarge(struct Stack *S) {
//     int new_capacity = (S->capacity * 3);
//     S->capacity = new_capacity;
//     S->arr = (int*)realloc(S->arr, new_capacity * sizeof(int));
// };

void pushOperatorStack(struct operatorStack *S, char data) {
    S->arr[++S->top] = data;
    // if (isFullStack(S))
    // enlarge(S);
};

void popOperatorStack(struct operatorStack *S){
    --S->top;
}

char peekOperatorStack(struct operatorStack *S){
    return S->arr[S->top];
}

bool isEmptyOperatorStack(struct operatorStack *S){
    return (S->top == -1)? true : false;
}

bool isPriorTO(char operator1,  char operator2);
double calculate(double left, double right, char op);
double right, left;




int main()
{
    // printf("%d", 100000000);
    char instr[MAX_LEN];
    // scanf("%s", &instr);
    while (scanf("%s", &instr)!=EOF)
    {   
        operatorStack *operatorStack = createOperatorStack();
        Stack *Stack = createStack();
        char temp;
        char* ptr = instr;
        // char* prev = instr;
        char integerStr[10];
        char *integerStrPtr = integerStr;
        while (*ptr != '\0')
        {   
            temp = *ptr;
            // printf("%c ", temp);   
            
            if (!(temp < 48 || temp > 57))  // temp is a digit; 48~57 is the ASCII code of digits 0~9
            {
                // push(Stack, (double)(temp-48));
                *integerStrPtr = temp;
                ++integerStrPtr;
                if (*(ptr+1) < 48 || *(ptr+1) > 57 )
                {
                    *integerStrPtr = '\0';
                    integerStrPtr = integerStr;
                    push(Stack, atof(integerStr));
                }
            }
            else
            {
                if (isEmptyOperatorStack(operatorStack))
                    pushOperatorStack(operatorStack, temp);
                else
                {
                    if (isPriorTO(temp, peekOperatorStack(operatorStack)))
                    {
                        // printf("%c > %c, push '%c' into operatorStack\n", temp, peekOperatorStack(operatorStack), temp);
                        pushOperatorStack(operatorStack, temp);
                        // printf("%c\n",peekOperatorStack(operatorStack));
                    }
                    else   //壓不住
                    {
                        // printf("not\n");
                        right = peek(Stack);
                        pop(Stack);
                        left = peek(Stack);
                        pop(Stack);
                        printf("%f and %f\n", left, right);

                        push(Stack, calculate(left, right, peekOperatorStack(operatorStack)));
                        // printf("%f\n",peek(Stack));
                        popOperatorStack(operatorStack);
                        pushOperatorStack(operatorStack, temp);
                    }
                }
            }
            ++ptr;   
        }

        while (!isEmptyOperatorStack(operatorStack))
        {
            right = peek(Stack);
            pop(Stack);
            left = peek(Stack);
            pop(Stack);

            push(Stack, calculate(left, right, peekOperatorStack(operatorStack)));
            popOperatorStack(operatorStack);
        }
        printf("%f\n", peek(Stack));
    }
    return 0;
}

double calculate(double left, double right, char op) {
    double answer = 0.0;
    switch (op)
    {
    case '+':
        answer = left + right;
        break;
    case '-':
        answer = left - right;
        break;
    case '*':
        answer = left * right;
        break;
    case '/':
        answer = left / right;
        break;
    // case '^':
    //     answer = pow(left, right);
    //     break;
    default:
        break;
    }
    return answer;
}

bool isPriorTO(char operator1,  char operator2)  //operator1 絕對優先於 operator2 的話回傳 true 否則 false
{
    if (operator1 == '^')
    {
        if (operator2 != '^')
            return true;
        else
            return false;
    }
    else if (operator1 == '*' || operator1 == '/')
    {
        if (operator2 == '+' || operator2 == '-')
            return true;
        else
            return false;
    }
    else
        return false;
}