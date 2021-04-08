#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int MAX_LEN = 300;

#define isReverse 0
#define isNotReverse 1

void reverse_arr(int *arr, int len)
{
    int temp = 0;
    for (int i = 0, j = len - 1; i < j; ++i, --j)
    {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void insertionSort(int *arr, int len)
{
    int cur;
    for (int i = 1; i < len; ++i)
    {
        cur = arr[i];
        int j = i - 1;
        while ((j >= 0) && (arr[j] > cur))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = cur;
    }
}
int *copy_arr(int *arr, int len)
{
    int *newarr = malloc(sizeof(int) * MAX_LEN);
    for (int i = 0; i < len; ++i)
        newarr[i] = arr[i];
    return newarr;
}
typedef struct Node
{
    struct Node *prev, *next;
    int *array;
    int *sorted_array;
    int array_size;
    int tag;
} Node;

typedef struct DList
{
    Node *head;
    Node *tail;
    int total_element;
} DList;

DList *createDList()
{
    DList *D = (DList *)malloc(sizeof(DList));
    D->head = D->tail = NULL;
    D->total_element = 0;
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
    node->sorted_array = malloc(sizeof(int) * MAX_LEN);
    node->tag = isNotReverse;
    return node;
}

// void insert(int val)
// {
// }
int n_len_int_seq, q_num_query, len, temp, i, x, l, r, k, index, index_to_delete, index_to_insert;
char cmd[10], c;
Node *curNode, *leftNode, *rightNode, *leftNewNode, *rightNewNode, *ptr1, *ptr2, *newNode, *list_tail, *list_head;
DList *list;
// void insert(int val){
// int create = 0;
void deleteNode(Node *node)
{
    // --create;
    free(node->array);
    free(node->sorted_array);
    free(node);
}

void check_tail(DList *list)
{
    while (list_tail->array_size == 0)
    {
        list_tail = list_tail->prev;
        deleteNode(list_tail->next);
    }
}

void check_head(DList *list)
{
    while (list_head->array_size == 0)
    {
        list_head = list_head->next;
        deleteNode(list_head->prev);
    }
}

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
    Node *curNode = list_head;
    if (sep == 1)
    {
        printf("|| ");
        while (curNode != list_tail)
        {
            // num_nodes++;
            if (curNode->tag == isNotReverse)
                for (int i = 0; i < curNode->array_size; ++i)
                    printf("%d ", curNode->array[i]);
            else
                for (int i = curNode->array_size - 1; i >= 0; --i)
                    printf("%d ", curNode->array[i]);
            printf(" || ");
            curNode = curNode->next;
        }
        if (curNode->tag == isNotReverse)
            for (int i = 0; i < curNode->array_size; ++i)
                printf("%d ", curNode->array[i]);
        else
            for (int i = curNode->array_size - 1; i >= 0; --i)
                printf("%d ", curNode->array[i]);
    }
    else
    {
        while (curNode != list_tail)
        {
            if (curNode->tag == isNotReverse)
                for (int i = 0; i < curNode->array_size; ++i)
                    printf("%d ", curNode->array[i]);
            else
                for (int i = curNode->array_size - 1; i >= 0; --i)
                    printf("%d ", curNode->array[i]);
            curNode = curNode->next;
            // num_nodes++;
        }
        if (curNode->tag == isNotReverse)
            for (int i = 0; i < curNode->array_size; ++i)
                printf("%d ", curNode->array[i]);
        else
            for (int i = curNode->array_size - 1; i >= 0; --i)
                printf("%d ", curNode->array[i]);
    }
    printf("\n");
}

void print_sorted(DList *list)
{
    Node *curNode = list_head;

    printf("|| ");
    while (curNode != list_tail)
    {

        for (int i = 0; i < curNode->array_size; ++i)
            printf("%d ", curNode->sorted_array[i]);
        printf(" || ");
        curNode = curNode->next;
    }

    for (int i = 0; i < curNode->array_size; ++i)
        printf("%d ", curNode->sorted_array[i]);
    text("");
}
int num_nodes = 1;

void count_node(DList *list)
{
    Node *curNode = list_head;
    while (curNode != list_tail)
    {
        num_nodes++;
        curNode = curNode->next;
        // printf("%d\n", num_nodes);
    }
    printf("number of nodes:%d\n", num_nodes);
}

int merge(Node *prev, Node *next)
{
    int flag = 0;
    if (next->array_size <= MAX_LEN - prev->array_size)
    {
        if (prev->tag == isNotReverse)
        {
            if (next->tag == isNotReverse)
            {
                int prev_index = prev->array_size;
                int next_index = 0;
                int up_index = next->array_size;
                for (; next_index < up_index; ++next_index, ++prev_index)
                {
                    prev->array[prev_index] = next->array[next_index];
                    ++prev->array_size;
                    --next->array_size;
                }
            }
            else
            {
                int prev_index = prev->array_size;
                int next_index = next->array_size - 1;
                // int up_index = next->array_size;
                for (; next_index >= 0; --next_index, ++prev_index)
                {
                    prev->array[prev_index] = next->array[next_index];
                    ++prev->array_size;
                    --next->array_size;
                }
            }
            prev->next = next->next;
            if (next != list_tail)
                next->next->prev = prev;
            else
            {
                list_tail = prev;
                list_tail->next = NULL;
            }
            deleteNode(next);
            flag = 1;
        }
        else if (prev->tag == isReverse)
        {
            if (next->tag == isNotReverse)
            {
                int up_index = next->array_size;
                int index = 0;
                int cnt = 0;
                for (index = prev->array_size - 1; cnt < prev->array_size; --index, cnt++)
                {
                    prev->array[index + up_index] = prev->array[index];
                }
                for (index = 0; index < up_index; ++index)
                {
                    // prev->array[index + up_index] = prev->array[index];
                    prev->array[index] = next->array[--next->array_size];
                    ++prev->array_size;
                }
            }
            else
            {
                int *newarr = malloc(sizeof(int) * MAX_LEN);
                int i;
                for (i = 0; i < next->array_size; ++i)
                {
                    newarr[i] = next->array[i];
                }
                int cnt = 0;
                for (; cnt < prev->array_size; ++cnt, ++i)
                {
                    newarr[i] = prev->array[cnt];
                }
                free(prev->array);
                prev->array = newarr;
                prev->array_size = i;
            }
            prev->next = next->next;
            if (next != list_tail)
                next->next->prev = prev;
            else
                list_tail = prev;
            deleteNode(next);
            flag = 1;
        }
    }
    return flag;
}

void traverse_merge()
{
    int if_delete_next = 0;
    curNode = list_head->next;
    Node *ptr;
    while (curNode->next != list_tail && curNode != list_tail && curNode->next != NULL && curNode->next != NULL)
    {
        if (curNode->array_size == 0)
        {
            ptr = curNode;
            if (curNode != list_head)
                curNode->prev->next = curNode->next;
            else
                list_head = curNode->next;
            curNode->next->prev = curNode->prev;
            curNode = ptr->next;
            deleteNode(ptr);
        }
        if_delete_next = merge(curNode, curNode->next);
        if (if_delete_next == 1)
        {
            free(curNode->sorted_array);
            curNode->sorted_array = copy_arr(curNode->array, curNode->array_size);
            insertionSort(curNode->sorted_array, curNode->array_size);
            continue;
        }
        curNode = curNode->next;
    }
    // check_tail(list);
}

int main()
{
    int z;
    // scanf("%d %d", &n_len_int_seq, &q_num_query);
    n_len_int_seq = readInt();
    q_num_query = readInt();
    MAX_LEN = (int)sqrt(n_len_int_seq);
    // printf("hello");
    DList *list = createDList();
    list_tail = list_head = createNode();
    curNode = list_head;
    for (i = 0; i < n_len_int_seq; ++i)
    {
        temp = readInt();

        if (!(curNode->array_size < MAX_LEN * 90 / 100))
        {
            Node *newNode = createNode();
            list_tail = newNode;
            curNode->next = newNode;
            newNode->prev = curNode;
            curNode = curNode->next;
        }
        curNode->array[curNode->array_size] = temp;
        curNode->sorted_array[curNode->array_size] = temp;
        curNode->array_size++;
        insertionSort(curNode->sorted_array, curNode->array_size);
        ++list->total_element;
    }
    // print(list, 1);

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            continue;

        Node *curNode = list_head;
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
                newNode->sorted_array[0] = x;
                newNode->next = list_head;
                list_head->prev = newNode;
                list_head = newNode;
            }
            else if (i == list->total_element)
            {
                Node *newNode = createNode();
                if (list_tail->tag == isNotReverse)
                {
                    newNode->array[newNode->array_size++] = list_tail->array[list_tail->array_size - 1];
                    newNode->sorted_array[0] = list_tail->array[list_tail->array_size - 1];
                    list_tail->array[list_tail->array_size - 1] = x;
                    list_tail->sorted_array = copy_arr(list_tail->array, list_tail->array_size);
                    insertionSort(list_tail->sorted_array, list_tail->array_size);
                }
                else
                {
                    newNode->array[newNode->array_size++] = list_tail->array[0];
                    list_tail->array[0] = x;
                }
                list_tail->next = newNode;
                newNode->prev = list_tail;
                list_tail = newNode;
            }
            else if (i - 1 == list->total_element)
            {
                Node *newNode = createNode();
                newNode->array[newNode->array_size++] = x;
                newNode->sorted_array[0] = x;
                list_tail->next = newNode;
                newNode->prev = list_tail;
                list_tail = newNode;
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
                if (curNode->tag == isReverse)
                {
                    reverse_arr(curNode->array, curNode->array_size);
                    changeTag(curNode);
                }
                if (curNode->array_size == MAX_LEN)
                {
                    if (i - temp == 1)
                    { //滿了又要插在這個array的頭
                        // if 前面還放得下(curNode不會是head  會在前面被做掉)
                        if (curNode->prev->array_size < MAX_LEN && curNode->prev->tag == isNotReverse)
                        {
                            curNode = curNode->prev;
                            curNode->array[curNode->array_size] = x;
                            curNode->sorted_array[curNode->array_size] = x;
                            ++curNode->array_size;
                            insertionSort(curNode->sorted_array, curNode->array_size);
                        }
                        else //放不下就在前面創一個node
                        {
                            Node *newNode = createNode();
                            newNode->array[newNode->array_size] = x;
                            newNode->sorted_array[newNode->array_size] = x;
                            ++newNode->array_size;
                            newNode->next = curNode;
                            newNode->prev = curNode->prev;
                            curNode->prev->next = newNode;
                            curNode->prev = newNode;
                        }
                    }
                    else //不然在後面創node，把東西往後推
                    {
                        Node *newNode = createNode();
                        if (curNode != list_tail)
                        {
                            newNode->next = curNode->next;
                            curNode->next->prev = newNode;
                            newNode->prev = curNode;
                            curNode->next = newNode;
                        }
                        else
                        {
                            curNode->next = newNode;
                            newNode->prev = curNode;
                            list_tail = newNode;
                        }

                        for (int index = 0; index <= MAX_LEN - (i - temp); ++index)
                        {
                            newNode->array[newNode->array_size++] = curNode->array[index + i - temp - 1];
                            --curNode->array_size;
                        }
                        curNode->array[i - temp - 1] = x;
                        ++curNode->array_size;
                        curNode->sorted_array[curNode->array_size] = x;

                        newNode->sorted_array = copy_arr(newNode->array, newNode->array_size);
                        insertionSort(newNode->sorted_array, newNode->array_size);

                        curNode->sorted_array = copy_arr(curNode->array, curNode->array_size);
                        insertionSort(curNode->sorted_array, curNode->array_size);
                    }
                }
                //沒滿還能放
                else
                {

                    for (int index = curNode->array_size; index > (i - temp - 1); index--)
                        curNode->array[index] = curNode->array[index - 1];
                    curNode->array[i - temp - 1] = x;
                    curNode->sorted_array[curNode->array_size] = x;
                    curNode->array_size++;
                    insertionSort(curNode->sorted_array, curNode->array_size);
                }
            }
            ++list->total_element;
            check_head(list);
            check_tail(list);
            break;
        case 'D':

            --list->total_element;
            break;
        case 'R':
            l = readInt();
            r = readInt();
            if (l == r)
                break;
            int temp_left = 0;
            Node *leftNode = list_head;
            while (temp_left + leftNode->array_size < l)
            {
                if (leftNode->array_size == 0 && leftNode->prev != NULL)
                {
                    Node *ptr = leftNode;
                    leftNode->prev->next = leftNode->next;
                    leftNode = leftNode->next;
                    leftNode->prev = leftNode->prev->prev;
                    deleteNode(ptr);
                    continue;
                }
                temp_left += leftNode->array_size;
                leftNode = leftNode->next;
            }
            int temp_right = temp_left;
            Node *rightNode = leftNode;
            while (temp_right + rightNode->array_size < r)
            {

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
            leftNewNode->sorted_array = copy_arr(leftNewNode->array, leftNewNode->array_size);
            insertionSort(leftNewNode->sorted_array, leftNewNode->array_size);
            leftNode->sorted_array = copy_arr(leftNode->array, leftNode->array_size);
            insertionSort(leftNode->sorted_array, leftNode->array_size);

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
            rightNewNode->sorted_array = copy_arr(rightNewNode->array, rightNewNode->array_size);
            insertionSort(rightNewNode->sorted_array, rightNewNode->array_size);
            rightNode->sorted_array = copy_arr(rightNode->array, rightNode->array_size);
            insertionSort(rightNode->sorted_array, rightNode->array_size);

            leftNewNode->next = leftNode->next;
            leftNewNode->prev = leftNode;
            leftNode->next->prev = leftNewNode;
            leftNode->next = leftNewNode;
            rightNewNode->next = rightNode;
            rightNewNode->prev = rightNode->prev;
            rightNode->prev->next = rightNewNode;
            rightNode->prev = rightNewNode;

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

            check_head(list);
            check_tail(list);
            traverse_merge();

            break;
        case 'Q':
            // text("query");
            l = readInt();
            r = readInt();
            k = readInt();
            break;
        }
        // print(list, 1);
        // print_sorted(list);
        // assert(list_head->array_size > 0);
    }
    print(list, 0);
    // printf("MAX_LEN :%d\n", MAX_LEN);
    // count_node(list);
    // printf("total element: %d\neach node contains %f elements\n", list->total_element, (float)(list->total_element) / num_nodes);
    // printf("full rate: %.2f%%\n", (float)(list->total_element) / num_nodes / MAX_LEN * 100);
    // float memory = (float)(num_nodes) * (sizeof(int) * MAX_LEN + sizeof(Node)) / 1000;
    // printf("memory usage: %f KB\n", memory);

    return 0;
}
