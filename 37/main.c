#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int MAX_LEN = 4;

#define isReverse 0
#define isNotReverse 1

typedef struct Node
{
    struct Node *prev, *next;
    int *array;
    int array_size;
    int tag;
} Node;

typedef struct DList
{
    Node *head;
    Node *tail;
    int list_size;
    int total_element;
} DList;

DList *createDList()
{
    DList *D = (DList *)malloc(sizeof(DList));
    D->head = D->tail = NULL;
    D->total_element = D->list_size = 0;
    return D;
}

void text(char *s)
{
    printf("%s\n", s);
}

Node *createNode()
{
    Node *node = malloc(sizeof(Node));
    node->next = node->prev = NULL;
    node->array_size = 0;
    node->array = malloc(sizeof(int) * MAX_LEN);
    node->tag = isNotReverse;
    return node;
}

// void insert(int val){

// }

void changeTag(Node *node)
{
    node->tag = (node->tag == isReverse) ? isNotReverse : isReverse;
}

int readInt()
{
    int num = 0;
    int flag = 0;
    char c = getchar();
    while ((c < '0' || c > '9'))
    {
        if (c == '-')
            flag = 1;
        c = getchar();
    }
    while (c > ('0' - 1) && c < ('9' + 1))
        num = num * 10 + (c - '0'), c = getchar();
    if (flag == 0)
        return num;
    else
        return num * (-1);
}

void print(DList *list)
{
    Node *curNode = list->head;
    while (curNode != NULL)
    {
        for (int i = 0; i < curNode->array_size; ++i)
            printf("%d ", curNode->array[i]);
        printf(" || ");
        curNode = curNode->next;
    }
    printf("\n");
}

int n_len_int_seq, q_num_query, len, temp, i, x, l, r, k;
char cmd[10], c;
Node *curNode;

int main()
{
    int z;
    // scanf("%d %d", &n_len_int_seq, &q_num_query);
    n_len_int_seq = readInt();
    q_num_query = readInt();
    MAX_LEN = (int)sqrt(n_len_int_seq);
    // printf("hello");
    DList *list = createDList();
    list->tail = list->head = createNode();
    ++list->list_size;
    curNode = list->head;
    for (i = 0; i < n_len_int_seq; ++i)
    {
        temp = readInt();

        if (!(curNode->array_size < MAX_LEN / 2))
        {
            Node *newNode = createNode();
            list->tail = newNode;
            curNode->next = newNode;
            newNode->prev = curNode;
            curNode = curNode->next;
            ++list->list_size;
        }
        curNode->array[curNode->array_size++] = temp;
        ++list->total_element;
    }
    // print(list);
    // curNode = list->head;
    // while (curNode != NULL){
    //     for (int i = 0; i < curNode->array_size; ++i)
    //         printf("%d ", curNode->array[i]);
    //     curNode = curNode->next;
    // }
    // printf("\n");

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            continue;

        Node *curNode = list->head;
        switch (c)
        {
        case 'I':
            // insert an integer x before the ith element of the sequence.
            // If i − 1 equals the length of the sequence, then insert x at the end of it.
            i = readInt();
            x = readInt();
            if (i == 1)
            {
                Node *newNode = createNode();
                newNode->array[newNode->array_size++] = x;
                newNode->next = list->head;
                list->head->prev = newNode;
                list->head = newNode;
                ++list->list_size;
                ++list->total_element;
            }
            else if (i == list->total_element)
            {
                Node *newNode = createNode();
                newNode->array[newNode->array_size++] = list->tail->array[list->tail->array_size - 1];
                list->tail->array[list->tail->array_size - 1] = x;
                list->tail->next = newNode;
                newNode->prev = list->tail;
                ++list->list_size;
                ++list->total_element;
                list->tail = newNode;
            }
            else if (i - 1 == list->total_element)
            {
                Node *newNode = createNode();
                newNode->array[newNode->array_size++] = x;
                list->tail->next = newNode;
                newNode->prev = list->tail;
                ++list->list_size;
                list->tail = newNode;
                ++list->total_element;
            }
            else
            {
                temp = 0;
                while (temp + curNode->array_size < i)
                {
                    // if (x-temp)
                    temp += curNode->array_size;
                    if (curNode->next == NULL)
                    {
                        Node *newNode = createNode();
                        newNode->prev = curNode;
                        curNode->next = newNode;
                    }
                    curNode = curNode->next;
                }

                //現在到了理論上要可以插入的點
                //但如果滿了，就新增一個newNode在後面
                //把要插入的地方的後面都放進newNode
                if (curNode->array_size == MAX_LEN)
                {
                    if (i - temp == 1)
                    { //滿了又要插在這個array的頭
                        if (curNode->prev->array_size < MAX_LEN)
                        {
                            curNode = curNode->prev;
                            curNode->array[curNode->array_size++] = x;
                            ++list->total_element;
                        }
                        else
                        {
                            Node *newNode = createNode();
                            newNode->array[newNode->array_size++] = x;
                            ++list->total_element;
                            // ++newNode->array_size;
                            newNode->next = curNode;
                            newNode->prev = curNode->prev;
                            curNode->prev->next = newNode;
                            curNode->prev = newNode;
                            ++list->list_size;
                        }
                    }
                    else
                    {
                        Node *newNode = createNode();
                        newNode->next = curNode->next;
                        curNode->next->prev = newNode;
                        newNode->prev = curNode;
                        curNode->next = newNode;
                        for (int index = 0; index <= MAX_LEN - (i - temp); ++index)
                        {
                            newNode->array[newNode->array_size++] = curNode->array[index + i - temp - 1];
                            --curNode->array_size;
                        }
                        curNode->array[i - temp - 1] = x;
                        ++curNode->array_size;
                        ++list->total_element;
                        ++list->list_size;
                    }
                }
                //沒滿還能放
                else
                {
                    if (i - temp == 1 && (curNode->prev->array_size < MAX_LEN))
                    { //滿了又要插在這個array的頭
                        {
                            curNode = curNode->prev;
                            curNode->array[curNode->array_size++] = x;
                            ++list->total_element;
                        }
                    }
                    else
                    {
                        for (int index = curNode->array_size; index > (i - temp - 1); index--)
                            curNode->array[index] = curNode->array[index - 1];
                        curNode->array[i - temp - 1] = x;
                        ++list->total_element;
                        curNode->array_size++;
                    }
                }
            }
            // print(list);

            break;
        case 'D':
            text("de");
            i = readInt();
            break;
        case 'R':
            l = readInt();
            r = readInt();
            temp = 0;
            // while (temp + curNode->array_size < l)
            // {
            //     // if (x-temp)
            //     temp += curNode->array_size;
            //     if (curNode->next == NULL)
            //     {
            //         Node *newNode = createNode();
            //         newNode->prev = curNode;
            //         curNode->next = newNode;
            //     }
            //     curNode = curNode->next;
            // }
            // //curNode 在l那個node
            // if (i - temp == i) //array[0]
            // {
            //     changeTag(curNode);
            // }
            // else
            // {
            //     Node *newNode = createNode();  //for reverse array
            //     newNode->prev = curNode;
            //     newNode->next = curNode->next;
            //     for (int index = i - temp - 1; index < curNode->array_size; ++index)
            //     {

            //     }
            // }

            // for (int i = 0; i < curNode->array_size; ++i)
            //     printf("%d ", curNode->array[i]);
            // curNode = curNode->next;
            // printf("%d\n", l - r);

            break;
        case 'Q':
            text("query");
            l = readInt();
            r = readInt();
            k = readInt();
            break;
        }
    }
    // Node *curNode = list->head;
    // while (curNode != NULL)
    // {
    //     for (int i = 0; i < curNode->array_size; ++i)
    //         printf("%d ", curNode->array[i]);
    //     curNode = curNode->next;
    // }
    // return 0;
    print(list);
}