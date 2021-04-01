#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int MAX_LEN = 4;
typedef struct Node
{
    struct Node *prev, *next;
    int *array;
    int array_size;
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
    return node;
}

// void insert(int val){

// }

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
    Node *curnode = list->head;
    while (curnode != NULL)
    {
        for (int i = 0; i < curnode->array_size; ++i)
            printf("%d ", curnode->array[i]);
        printf(" || ");
        curnode = curnode->next;
    }
    printf("\n");
}

int n_len_int_seq, q_num_query, len, temp, i, x, l, r, k;
char cmd[10], c;
Node *curnode;

int main()
{
    int z;
    // scanf("%d %d", &n_len_int_seq, &q_num_query);
    n_len_int_seq = readInt();
    q_num_query = readInt();
    // MAX_LEN = (int)sqrt(n_len_int_seq);
    // printf("hello");
    DList *list = createDList();
    list->tail = list->head = createNode();
    ++list->list_size;
    curnode = list->head;
    for (i = 0; i < n_len_int_seq; ++i)
    {
        temp = readInt();

        if (!(curnode->array_size < MAX_LEN / 2))
        {
            Node *newNode = createNode();
            list->tail = newNode;
            curnode->next = newNode;
            newNode->prev = curnode;
            curnode = curnode->next;
            ++list->list_size;
        }
        curnode->array[curnode->array_size++] = temp;
        ++list->total_element;
    }
    // print(list);
    // curnode = list->head;
    // while (curnode != NULL){
    //     for (int i = 0; i < curnode->array_size; ++i)
    //         printf("%d ", curnode->array[i]);
    //     curnode = curnode->next;
    // }
    // printf("\n");

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            continue;

        switch (c)
        {
        case 'I':
            // insert an integer x before the ith element of the sequence.
            // If i − 1 equals the length of the sequence, then insert x at the end of it.
            i = readInt();
            x = readInt();
            Node *curnode = list->head;
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
                while (temp + curnode->array_size < i)
                {
                    // if (x-temp)
                    temp += curnode->array_size;
                    if (curnode->next == NULL)
                    {
                        Node *newNode = createNode();
                        newNode->prev = curnode;
                        curnode->next = newNode;
                    }
                    curnode = curnode->next;
                }

                //現在到了理論上要可以插入的點
                //但如果滿了，就新增一個newNode在後面
                //把要插入的地方的後面都放進newNode
                if (curnode->array_size == MAX_LEN)
                {
                    if (i - temp == 1)
                    { //滿了又要插在這個array的頭
                        if (curnode->prev->array_size < MAX_LEN)
                        {
                            curnode = curnode->prev;
                            curnode->array[curnode->array_size++] = x;
                            ++list->total_element;
                        }
                        else
                        {
                            Node *newNode = createNode();
                            newNode->array[newNode->array_size++] = x;
                            ++list->total_element;
                            // ++newNode->array_size;
                            newNode->next = curnode;
                            newNode->prev = curnode->prev;
                            curnode->prev->next = newNode;
                            curnode->prev = newNode;
                            ++list->list_size;
                        }
                    }
                    else
                    {
                        Node *newNode = createNode();
                        newNode->next = curnode->next;
                        curnode->next->prev = newNode;
                        newNode->prev = curnode;
                        curnode->next = newNode;
                        for (int index = 0; index <= MAX_LEN - (i - temp); ++index)
                        {
                            newNode->array[newNode->array_size++] = curnode->array[index + i - temp - 1];
                            --curnode->array_size;
                        }
                        curnode->array[i - temp - 1] = x;
                        ++curnode->array_size;
                        ++list->total_element;
                        ++list->list_size;
                    }
                }
                //沒滿還能放
                else
                {
                    if (i - temp == 1 && (curnode->prev->array_size < MAX_LEN))
                    { //滿了又要插在這個array的頭
                        {
                            curnode = curnode->prev;
                            curnode->array[curnode->array_size++] = x;
                            ++list->total_element;
                        }
                    }
                    else
                    {
                        for (int index = curnode->array_size; index > (i - temp - 1); index--)
                            curnode->array[index] = curnode->array[index - 1];
                        curnode->array[i - temp - 1] = x;
                        ++list->total_element;
                        curnode->array_size++;
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
            break;
        case 'Q':
            text("query");
            l = readInt();
            r = readInt();
            k = readInt();
            break;
        }
    }
    Node *curnode = list->head;
    while (curnode != NULL)
    {
        for (int i = 0; i < curnode->array_size; ++i)
            printf("%d ", curnode->array[i]);
        curnode = curnode->next;
    }
    return 0;
}