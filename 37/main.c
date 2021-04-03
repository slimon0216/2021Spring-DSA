#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int MAX_LEN = 300;

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
    // print(list, 1);
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
            if (l == r)
                break;
            int temp_left = 0;
            Node *leftNode = list->head;
            while (temp_left + leftNode->array_size < l)
            {
                // if (leftNode->array_size == 0 && leftNode->prev != NULL)
                // {
                //     leftNode->prev->next = leftNode->next;
                //     leftNode = leftNode->next;
                //     leftNode->prev = leftNode->prev->prev;
                //     continue;
                // }
                temp_left += leftNode->array_size;
                leftNode = leftNode->next;
            }
            int temp_right = temp_left;
            Node *rightNode = leftNode;
            while (temp_right + rightNode->array_size < r)
            {
                // if (rightNode->array_size == 0 && rightNode->prev != NULL)
                // {
                //     rightNode->prev->next = rightNode->next;
                //     rightNode = rightNode->next;
                //     rightNode->prev = rightNode->prev->prev;
                //     continue;
                // }
                temp_right += rightNode->array_size;
                rightNode = rightNode->next;
                // if (rightNode->array_size == 1)
                //     rightNode->tag = isNotReverse;
            }

            if (leftNode == rightNode) //reverse的區間都再同一個node
            {
                int temp;
                if (leftNode->tag == isNotReverse)
                    for (int index_l = l - temp_left - 1, index_r = r - temp_right - 1; index_l < index_r; ++index_l, --index_r)
                    {
                        temp = leftNode->array[index_l];
                        leftNode->array[index_l] = leftNode->array[index_r];
                        leftNode->array[index_r] = temp;
                    }
                else
                    for (int index_l = leftNode->array_size - (l - temp_left), index_r = leftNode->array_size - (r - temp_right);
                         index_r < index_l; ++index_r, --index_l)
                    {
                        temp = leftNode->array[index_l];
                        leftNode->array[index_l] = leftNode->array[index_r];
                        leftNode->array[index_r] = temp;
                    }
                // print(list, 1);
                break;
            }

            // int numOfL = l - temp_left; //從這個node的第幾個ele開始般
            // int numOfR = r - temp_right;
            Node *leftNewNode = createNode();
            Node *rightNewNode = createNode();

            if (leftNode->tag == isNotReverse)
            {
                int up_index = leftNode->array_size;
                for (int index = l - temp_left - 1; index < up_index; ++index)
                {
                    leftNewNode->array[leftNewNode->array_size++] = leftNode->array[index];
                    --leftNode->array_size;
                }
                changeTag(leftNewNode);
            }
            else
            {
                int changePoint = leftNode->array_size - (l - temp_left);
                // for (int index = leftNode->array_size - (l - temp_left); index >= 0; --index)
                int *a = malloc(sizeof(int) * MAX_LEN);
                int a_size = 0;
                for (int index = leftNode->array_size - 1; index >= 0; --index)
                {
                    if (index <= changePoint)
                    {
                        leftNewNode->array[leftNewNode->array_size++] = leftNode->array[index];
                        // ++leftNewNode->array_size;
                        // leftNode->array[index] = leftNode->array[index + 1];
                        --leftNode->array_size;
                    }
                    else
                    {
                        a[a_size++] = leftNode->array[index];
                    }
                }
                leftNode->array = a;
                leftNode->array_size = a_size;
                changeTag(leftNode);
                changeTag(leftNewNode);
            }

            if (rightNode->tag == isNotReverse)
            {
                int changePoint = r - temp_right;
                int up_index = rightNode->array_size;
                int *a = malloc(sizeof(int) * MAX_LEN);
                int a_size = 0;
                for (int index = 0; index < up_index; ++index)
                {
                    if (index < changePoint)
                    {
                        rightNewNode->array[rightNewNode->array_size++] = rightNode->array[index];
                        rightNode->array[index] = rightNode->array[index + 1];
                        --rightNode->array_size;
                    }
                    else
                    {
                        a[a_size++] = rightNode->array[index];
                    }
                }
                rightNode->array = a;
                rightNode->array_size = a_size;
                changeTag(rightNewNode);
            }
            else
            {
                for (int index = rightNode->array_size - 1, cnt = (r - temp_right - 1); cnt >= 0; --index, --cnt)
                {
                    rightNewNode->array[rightNewNode->array_size++] = rightNode->array[index];
                    --rightNode->array_size;
                }
                changeTag(rightNewNode);
            }
            // text("test");
            // print(list, 1);
            leftNewNode->next = leftNode->next;
            leftNewNode->prev = leftNode;
            leftNode->next->prev = leftNewNode;
            leftNode->next = leftNewNode;
            rightNewNode->next = rightNode;
            rightNewNode->prev = rightNode->prev;
            rightNode->prev->next = rightNewNode;
            rightNode->prev = rightNewNode;
            // print(list, 1);

            Node *ptr1 = leftNewNode;
            Node *ptr2 = leftNewNode->next;
            ptr1->next = rightNode;
            ptr1->prev = ptr2;
            while (ptr2 != rightNode)
            {
                changeTag(ptr2);
                ptr2->prev = ptr2->next;
                ptr2->next = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr2->prev;
            }
            changeTag(rightNewNode); //while迴圈會被改到，改回來
            rightNewNode->prev = leftNode;
            leftNode->next = rightNewNode;
            rightNode->prev = leftNewNode;
            // leftNewNode->next = rightNode;

            // Node *curNode = list->tail;
            // printf("||");
            // while (curNode != NULL)
            // {
            //     if (curNode->tag == isNotReverse)
            //         for (int i = 0; i < curNode->array_size; ++i)
            //             printf("%d ", curNode->array[i]);
            //     else
            //         for (int i = curNode->array_size - 1; i >= 0; --i)
            //             printf("%d ", curNode->array[i]);
            //     printf(" || ");
            //     curNode = curNode->prev;
            // }
            // text("");
            // print(list, 1);

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
    print(list, 0);
}