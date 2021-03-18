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

void print(char* str){
    printf("%s\n", str);
}

double encode(const char c){

    if (c =='+')
        return -1.0;
    if (c =='-')
        return -2.0;
    if (c =='*')
        return -3.0;
    if (c =='/')
        return -4.0;

    
}

char decode(const double d){

    if (d == -1.0)
        return '+';
    if (d == -2.0)
        return '-';
    if (d == -3.0)
        return '*';
    if (d == -4.0)
        return '/';
    
}

int main()
{
    // printf("%d", 100000000);
    char instr[MAX_LEN];
    // scanf("%s", &instr);
    while (scanf("%s", &instr)!=EOF)
    {   
        operatorStack *operatorStack = createOperatorStack();
        
        char temp;
        // char* prev = instr;
        char integerStr[10] ="";
        char *integerStrPtr = integerStr;
        // char Y[MAX_LEN];
        double Y[MAX_LEN];
        int lenOfY = 0;
        ////postfix algorithm///////
        pushOperatorStack(operatorStack, '(');
        *(instr + strlen(instr) + 1) = '\0';
        *(instr + strlen(instr) ) = ')';
        // print(instr);
        // printf("x: %s\n", instr);

        char* ptr = instr;
        while (*ptr != '\0')
        {   
            temp = *ptr;  
            if (!(temp < 48 || temp > 57))  // temp is a digit; 48~57 is the ASCII code of digits 0~9
            {
                *integerStrPtr = temp;
                ++integerStrPtr;
                if (*(ptr+1) < 48 || *(ptr+1) > 57 )
                {
                    *integerStrPtr = '\0';
                    integerStrPtr = integerStr;
                    // print(integerStr);

                    //''' add intergerStr to Y '''
                    // strcat(Y, integerStr);
                    Y[lenOfY] = atoi(integerStr);
                    lenOfY++;
                    // push(Stack, atof(integerStr)); 
                    // print(Y);
                }
            }
            else if (temp == '(')
            {
                pushOperatorStack(operatorStack, '(');
                // printf("successfully push %c\n", temp);    
            }
            else if(temp == ')')
            {
                while(peekOperatorStack(operatorStack) != '(')
                {   
                    // char topOperator[2] = "\0"; /* gives {\0, \0} */
                    // topOperator[0] = peekOperatorStack(operatorStack);
                    // strcat(Y, topOperator);
                    Y[lenOfY] = encode(peekOperatorStack(operatorStack));
                    lenOfY++;
                    popOperatorStack(operatorStack);
                    // print(Y);
                }
                popOperatorStack(operatorStack);
            }
            else  // an operator
            {
                // '''
                // Repeatedly pop from Stack and 
                // add to Y each operator (on the top of Stack) 
                // which has the same precedence as or higher precedence than operator.
                // 壓不住就pop出來
                // '''
                // char topOperator[2] = "\0"; /* gives {\0, \0} */
                while (peekOperatorStack(operatorStack) != '(')
                {
                    // topOperator[0] = peekOperatorStack(operatorStack);
                    if(!isPriorTO(temp, peekOperatorStack(operatorStack)))  //壓不住
                    {
                        Y[lenOfY] = encode(peekOperatorStack(operatorStack));
                        lenOfY++;
                        popOperatorStack(operatorStack);
                    }
                    else break;
                }
                pushOperatorStack(operatorStack, temp);

            }

            // if (isEmptyOperatorStack(operatorStack))
            //     pushOperatorStack(operatorStack, temp);
            // else
            // {
            //     if (isPriorTO(temp, peekOperatorStack(operatorStack)))
            //     {
            //         // printf("%c > %c, push '%c' into operatorStack\n", temp, peekOperatorStack(operatorStack), temp);
            //         pushOperatorStack(operatorStack, temp);
            //         // printf("%c\n",peekOperatorStack(operatorStack));
            //     }
            //     else   //壓不住
            //     {
            //         // printf("not\n");
            //         right = peek(Stack);
            //         pop(Stack);
            //         left = peek(Stack);
            //         pop(Stack);
            //         // printf("%f and %f\n", left, right);

            //         push(Stack, calculate(left, right, peekOperatorStack(operatorStack)));
            //         // printf("%f\n",peek(Stack));
            //         popOperatorStack(operatorStack);
            //         pushOperatorStack(operatorStack, temp);
            //     }
            // }
            ++ptr;   
        }
        Stack *Stack = createStack();
        for(int i = 0; i < lenOfY; ++i)
        {
            if (Y[i] >= 0)
            {
                push(Stack, Y[i]);
            }
            else
            {
                right = peek(Stack);
                pop(Stack);
                left = peek(Stack);
                pop(Stack);
                push(Stack, calculate(left, right, decode(Y[i])));
            }
        }
        printf("%f\n", peek(Stack));
    }

        // while (!isEmptyOperatorStack(operatorStack))
        // {
        //     right = peek(Stack);
        //     pop(Stack);
        //     left = peek(Stack);
        //     pop(Stack);

        //     push(Stack, calculate(left, right, peekOperatorStack(operatorStack)));
        //     popOperatorStack(operatorStack);
        // }
        // printf("%f\n", peek(Stack));
    
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