#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int MAX_LEN = 100000;

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
    if (node->array_size <= 1)
        node->tag = isNotReverse;
    else
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

void print(DList *list, int sep)
{

    Node *curNode = list->head;
    if (sep == 1)
    {
        printf("|| ");
        while (curNode != NULL)
        {
            if (curNode->tag == isNotReverse)
                for (int i = 0; i < curNode->array_size; ++i)
                    printf("%d ", curNode->array[i]);
            else
                for (int i = curNode->array_size - 1; i >= 0; --i)
                    printf("%d ", curNode->array[i]);
            printf(" || ");
            curNode = curNode->next;
        }
    }
    else
        while (curNode != NULL)
        {
            if (curNode->tag == isNotReverse)
                for (int i = 0; i < curNode->array_size; ++i)
                    printf("%d ", curNode->array[i]);
            else
                for (int i = curNode->array_size - 1; i >= 0; --i)
                    printf("%d ", curNode->array[i]);
            curNode = curNode->next;
        }
    printf("\n");
}
int temp;
int partition(int arr[], int l, int r)
{
    int x = arr[r], i = l;
    for (int j = l; j <= r; j++)
    {
        if (arr[j] <= x)
        {
            // swap(arr[i], arr[j]);
            temp = arr[i];
            arr[i] = arr[r];
            arr[r] = temp;
            i++;
        }
    }
    // swap(arr[i], arr[r]);
    temp = arr[i];
    arr[i] = arr[r];
    arr[r] = temp;

    return i;
}

int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of
    // elements in array
    if (l == r)
        return arr[l];
    if (k > 0 && k <= r - l + 1)
    {

        // Partition the array around last
        // element and get position of pivot
        // element in sorted array
        int index = partition(arr, l, r);

        // If position is same as k
        if (index - l == k - 1)
            return arr[index];

        // If position is more, recur
        // for left subarray
        if (index - l > k - 1)
            return kthSmallest(arr, l, index - 1, k);

        // Else recur for right subarray
        return kthSmallest(arr, index + 1, r,
                           k - index + l - 1);
    }
}

int n_len_int_seq, q_num_query, len, temp, i, x, l, r, k;
char cmd[10], c;
Node *curNode;

int main()
{
    int len = 0;
    n_len_int_seq = readInt();
    q_num_query = readInt();
    // MAX_LEN = (int)sqrt;
    int *array = malloc(sizeof(int) * MAX_LEN);
    for (i = 0; i < n_len_int_seq; ++i)
    {
        temp = readInt();
        array[i] = temp;
        ++len;
    }

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            continue;

        switch (c)
        {
        case 'I':
            // text("sdf");
            i = readInt();
            x = readInt();
            if (i == len)
            {
                array[len] = array[len - 1];
                array[len - 1] = x;
            }
            else if (i == len + 1)
            {
                array[len] = x;
                // text("sd");
            }
            else
            {
                int index = len - 1;
                for (; index >= i; --index)
                {
                    array[index + 1] = array[index];
                }
                array[index + 1] = array[index];
                array[index] = x;
            }
            ++len;
            break;
        case 'D':
            // text("de");
            i = readInt();
            // printf("%d\n", len);
            for (int index = i - 1; index < len - 1; ++index)
                array[index] = array[index + 1];
            --len;
            break;
        case 'R':
            l = readInt();
            r = readInt();

            for (; l < r; ++l, --r)
            {
                temp = array[l - 1];
                array[l - 1] = array[r - 1];
                array[r - 1] = temp;
            }
            break;
        case 'Q':
            // text("query");
            l = readInt();
            r = readInt();
            k = readInt();
            printf("%d\n", kthSmallest(array, l - 1, r - 1, k));
            break;
        }
        // for (int i = 0; i < len; ++i)
        //     printf("%d ", array[i]);
        // printf("\n");
    }
    // Node *curNode = list->head;
    // while (curNode != NULL)
    // {
    //     for (int i = 0; i < curNode->array_size; ++i)
    //         printf("%d ", curNode->array[i]);
    //     curNode = curNode->next;
    // }
    // return 0;
    // for (int i = 0; i < len; ++i)
    //     printf("%d ", array[i]);
}