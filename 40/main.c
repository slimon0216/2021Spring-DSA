#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 100000
 

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
inline int isFullStack(struct Stack *S);



inline void push(struct Stack *S, double data);

inline void pop(struct Stack *S);

inline double peek(struct Stack *S);

inline int isEmpty(struct Stack *S);

inline void clear(struct Stack *S);
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

inline int isFullOperatorStack(struct operatorStack *S);


// void enlarge(struct Stack *S) {
//     int new_capacity = (S->capacity * 3);
//     S->capacity = new_capacity;
//     S->arr = (int*)realloc(S->arr, new_capacity * sizeof(int));
// };

inline void pushOperatorStack(struct operatorStack *S, char data);
inline void popOperatorStack(struct operatorStack *S);
inline char peekOperatorStack(struct operatorStack *S);

inline int isEmptyOperatorStack(struct operatorStack *S);

inline void clearOperatorStack(struct operatorStack *S);

inline int isPriorTO(char operator1,  char operator2);
inline double calculate(double left, double right, char op);

// void print(char* str){
//     printf("%s\n", str);
// }

inline double encode(const char c);
inline char decode(const double d);

char instr[MAX_LEN];
char integerStr[10];
double Y[MAX_LEN];
int lenOfY;
double right, left;
char temp;
char *integerStrPtr;
char* ptr ;
int main()
{
    operatorStack *operatorStack = createOperatorStack();      
    Stack *Stack = createStack();
    while (scanf("%s", &instr)!=EOF)
    {   

        integerStrPtr = integerStr;
        lenOfY = 0;
        pushOperatorStack(operatorStack, '(');
        *(instr + strlen(instr) + 1) = '\0';
        *(instr + strlen(instr) ) = ')';
        ptr = instr;
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
                    Y[lenOfY++] = atof(integerStr);
                    // lenOfY++;
  
                }
            }
            else if (temp == '(')
            {
                pushOperatorStack(operatorStack, '(');
            }
            else if(temp == ')')
            {
                while(peekOperatorStack(operatorStack) != '(')
                {   
 
                    Y[lenOfY++] = encode(peekOperatorStack(operatorStack));
                    // lenOfY++;
                    popOperatorStack(operatorStack);

                }
                popOperatorStack(operatorStack);
            }
            else  // an operator
            {
                while (peekOperatorStack(operatorStack) != '(')
                {
                    if(!isPriorTO(temp, peekOperatorStack(operatorStack)))  //壓不住
                    {
                        Y[lenOfY++] = encode(peekOperatorStack(operatorStack));
                        // lenOfY++;
                        popOperatorStack(operatorStack);
                    }
                    else 
                        break;
                }
                pushOperatorStack(operatorStack, temp);

            }
            ++ptr;   
        }
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
        printf("%.15f\n", peek(Stack));
        clearOperatorStack(operatorStack);
        clear(Stack);
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
    case '^':
        answer = pow(left, right);
        break;
    default:
        break;
    }
    return answer;
}


int isPriorTO(char operator1,  char operator2)  //operator1 絕對優先於 operator2 的話回傳 1 否則 0
{
    if (operator1 == '^')
    {
        if (operator2 != '^')
            return 1;
        else
            return 0;
    }
    else if (operator1 == '*' || operator1 == '/')
    {
        if (operator2 == '+' || operator2 == '-')
            return 1;
        else
            return 0;
    }
    else
        return 0;
}


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


double encode(const char c){

    if (c =='+')
        return -1.0;
    if (c =='-')
        return -2.0;
    if (c =='*')
        return -3.0;
    if (c =='/')
        return -4.0;
    if (c =='^')
        return -5.0;
    
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
    if (d == -5.0)
        return '^';
}

int isFullStack(struct Stack *S) {
    return (S->top == S->capacity-1);
};

int isEmptyOperatorStack(struct operatorStack *S){
    return (S->top == -1)? 1 : 0;
}

int isFullOperatorStack(struct operatorStack *S) {
    return (S->top == S->capacity-1);
}

void clearOperatorStack(struct operatorStack *S){
    S->top = -1;
}

int isEmpty(struct Stack *S){
    return (S->top == -1)? 1 : 0;
}

void clear(struct Stack *S){
    S->top = -1;
}