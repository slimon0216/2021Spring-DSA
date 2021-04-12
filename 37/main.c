#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int MAX_LEN = 300;

#define isReverse 0
#define isNotReverse 1
int binarySearch(int *arr, int l, int r, float target)
{
    if (r - l == 1) //只有一個元素
    {
        if (target > arr[l])
            return &arr[l + 1] - arr;
        else
            return &arr[l] - arr;
    }
    if (r - l == 2) //有兩個元素
    {
        if (target < arr[l])
            return &arr[l] - arr;
        else if (target > arr[r - 1])
            return &arr[r] - arr;
        else
            return &arr[l + 1] - arr;
    }
    int mid;
    while (r - l + 1 > 3)
    {
        mid = (l + r) / 2;
        if (arr[mid] == target)
        {
            // while (mid - 1 > 0)
            // {
            //     if (arr[mid - 1] == arr[mid])
            //         mid--;
            //     else
            //         break;
            // }
            return &arr[mid] - arr;
        }

        else if (arr[mid] > target)
            r = mid;
        else if (arr[mid] < target)
            l = mid;
    }
    // if (l == 0)
    //     return -1; //代表說要放在頭
    for (; l <= r; l++)
    {
        if (l > 0)
            if (arr[l - 1] > target)
                return &arr[l - 1] - arr;
    }
    return &arr[l - 1] - arr;
}
int L[1000], R[1000];
void MERGE(int *arr, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int left, int right)
{
    if (left < right)
    {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        MERGE(arr, left, mid, right);
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

// int cparr[MAX_LEN];
void copy_arr(int *from, int *to, int len)
{
    for (int i = 0; i < len; ++i)
        to[i] = from[i];
}

// void insert(int val){

// }
int n_len_int_seq, q_num_query, len, temp, i, x, l, r, k, index, index_to_delete, index_to_insert;
char cmd[10], c;
Node *curNode, *leftNode, *rightNode, *leftNewNode, *rightNewNode, *ptr1, *ptr2, *newNode, *list_tail, *list_head;
DList *list;
int temp_arr[1000], temp_arr_l[1000], temp_arr_r[1000], *sorted_arrarys[1000], origin_lens[1000], bound_r[1000], arr_for_indexes[1000];

// void insert(int val){
// int create = 0;
// void deleteNode(Node *node)
// {
// --create;
// free(node->array);
// free(node->sorted_array);
// free(node);
// }

void check_tail(DList *list)
{
    while (list_tail->array_size == 0)
    {
        list_tail = list_tail->prev;
        // deleteNode(list_tail->next);
    }
}

void check_head(DList *list)
{
    while (list_head->array_size == 0)
    {
        list_head = list_head->next;
        // deleteNode(list_head->prev);
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

void delete_from_sorted(int *arr, int len, int x)
{
    int i = 0;
    while (arr[i] != x && i < len)
        ++i;
    for (; i < len - 1; ++i)
    {
        arr[i] = arr[i + 1];
    }
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
}
int num_nodes = 1;

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
            // deleteNode(next);
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
                // free(prev->array);
                prev->array = newarr;
                prev->array_size = i;
            }
            prev->next = next->next;
            if (next != list_tail)
                next->next->prev = prev;
            else
                list_tail = prev;
            // deleteNode(next);
            flag = 1;
        }
    }
    return flag;
}

void traverse_merge()
{
    int if_merge = 0;
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
            // deleteNode(ptr);
        }
        if_merge = merge(curNode, curNode->next);
        if (if_merge == 1)
        {
            copy_arr(curNode->array, curNode->sorted_array, curNode->array_size);
            mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
            continue;
        }
        curNode = curNode->next;
    }
    // check_tail(list);
}

int main()
{
    n_len_int_seq = readInt();
    q_num_query = readInt();
    MAX_LEN = (int)sqrt(n_len_int_seq);
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
        ++curNode->array_size;
        mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
        ++list->total_element;
    }

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
            if (list->total_element == 0)
            {
                list_head->array[0] = x;
                list_head->sorted_array[0] = x;
                ++list_head->array_size;
            }
            else if (i == 1)
            {
                Node *newNode = createNode();
                newNode->array[newNode->array_size] = x;
                newNode->sorted_array[newNode->array_size] = x;
                ++newNode->array_size;
                newNode->next = list_head;
                list_head->prev = newNode;
                list_head = newNode;
            }
            else if (i == list->total_element)
            {
                Node *newNode = createNode();
                if (list_tail->tag == isNotReverse)
                {
                    newNode->array[newNode->array_size] = list_tail->array[list_tail->array_size - 1];
                    newNode->sorted_array[newNode->array_size] = list_tail->array[list_tail->array_size - 1];
                    ++newNode->array_size;
                    int index = 0;
                    while (list_tail->sorted_array[index] != list_tail->array[list_tail->array_size - 1])
                    {
                        ++index;
                    }
                    list_tail->sorted_array[index] = x;
                    list_tail->array[list_tail->array_size - 1] = x;
                    mergeSort(list_tail->sorted_array, 0, list_tail->array_size - 1);
                }
                else
                {
                    newNode->array[newNode->array_size++] = list_tail->array[0];
                    newNode->sorted_array[0] = list_tail->array[0];
                    delete_from_sorted(list_tail->sorted_array, list_tail->array_size, list_tail->array[0]);
                    list_tail->array[0] = x;
                    list_tail->sorted_array[list_tail->array_size - 1] = x;
                    // if (list_tail->array_size != MAX_LEN)
                    // ++list_tail->ar
                    mergeSort(list_tail->sorted_array, 0, list_tail->array_size - 1);
                }
                list_tail->next = newNode;
                newNode->prev = list_tail;
                list_tail = newNode;
            }
            else if (i - 1 == list->total_element)
            {
                Node *newNode = createNode();
                newNode->array[newNode->array_size] = x;
                newNode->sorted_array[newNode->array_size] = x;
                ++newNode->array_size;
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
                if (curNode->array_size == MAX_LEN)
                {
                    if (curNode->tag == isNotReverse)
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
                                mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
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

                            copy_arr(newNode->array, newNode->sorted_array, newNode->array_size);
                            mergeSort(newNode->sorted_array, 0, newNode->array_size - 1);

                            copy_arr(curNode->array, curNode->sorted_array, curNode->array_size);
                            mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
                        }
                    }
                    else //順序是反的
                    {
                        if (i - temp == 1) //滿了又要插在這個array的頭 (其實是尾端)
                        {                  //如果前面node還有空位而且順序是正向的就直接丟過去
                            if (curNode->prev->array_size < MAX_LEN && curNode->prev->tag == isNotReverse)
                            {
                                curNode = curNode->prev;
                                curNode->array[curNode->array_size] = x;
                                curNode->sorted_array[curNode->array_size] = x;
                                ++curNode->array_size;
                                mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
                            }
                            else //不然就新增node，因為順序是反的，新增的Node要放在這個前面
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
                        else //滿了又要插在這個array的中間，且array是反的
                        {    //就往後新增Node，從這個array的插入點往前推一格(因為是反的)
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
                            if (curNode == list_tail)
                                list_tail = newNode;

                            newNode->array[newNode->array_size] = curNode->array[0];
                            newNode->sorted_array[newNode->array_size] = curNode->array[0];
                            ++newNode->array_size;

                            int index = 0;
                            int index_to_insert = curNode->array_size - (i - temp);
                            for (; index != index_to_insert; ++index)
                            {
                                curNode->array[index] = curNode->array[index + 1];
                            }
                            curNode->array[index] = x;
                            copy_arr(curNode->array, curNode->sorted_array, curNode->array_size);
                            mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
                        }
                    }
                }
                //沒滿還能放
                else
                {
                    if (curNode->tag == isNotReverse)
                    {
                        if (i - temp == 1 && (curNode->prev->array_size < MAX_LEN) && curNode->prev->tag == isNotReverse)
                        { //滿了又要插在這個array的頭，但前面沒滿
                            {
                                curNode = curNode->prev;
                                curNode->array[curNode->array_size] = x;
                                curNode->sorted_array[curNode->array_size] = x;
                                ++curNode->array_size;
                                mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
                            }
                        }
                        else
                        {
                            for (int index = curNode->array_size; index > (i - temp - 1); index--)
                                curNode->array[index] = curNode->array[index - 1];
                            curNode->array[i - temp - 1] = x;
                            curNode->sorted_array[curNode->array_size] = x;
                            curNode->array_size++;
                            mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
                        }
                    }
                    else
                    {
                        int index = curNode->array_size;
                        int index_to_insert = curNode->array_size - (i - temp - 1);
                        // int cnt = 0;
                        for (; index != index_to_insert; --index)
                        {
                            curNode->array[index] = curNode->array[index - 1];
                        }
                        curNode->array[index] = x;
                        curNode->sorted_array[curNode->array_size] = x;
                        curNode->array_size++;
                        mergeSort(curNode->sorted_array, 0, curNode->array_size - 1);
                    }
                }
            }
            ++list->total_element;
            check_head(list);
            check_tail(list);
            break;
        case 'D':
            i = readInt();
            if (list->total_element == 0)
                break;
            if (list->total_element == 1)
            {
                // free(list_head);
                list_head = createNode();
                list_tail = list_head;
                list->total_element = 0;
                break;
            }
            temp = 0;
            while (temp + curNode->array_size < i)
            {
                // if (x-temp)
                temp += curNode->array_size;
                if (curNode->next == NULL)
                {
                    newNode = createNode();
                    newNode->prev = curNode;
                    curNode->next = newNode;
                }
                curNode = curNode->next;
            }
            if (curNode->array_size == 1) //刪除這個node
            {
                --curNode->array_size;
            }

            else
            {
                if (curNode->tag == isNotReverse)
                    index_to_delete = i - temp - 1;
                else
                    index_to_delete = curNode->array_size - (i - temp);

                int d = curNode->array[index_to_delete];
                len = curNode->array_size;
                for (index = index_to_delete; index < len - 1; ++index)
                {
                    curNode->array[index] = curNode->array[index + 1];
                }
                delete_from_sorted(curNode->sorted_array, curNode->array_size, d);
                --curNode->array_size;
            }

            --list->total_element;
            check_head(list);
            check_tail(list);
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
                    // deleteNode(ptr);
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

            copy_arr(leftNewNode->array, leftNewNode->sorted_array, leftNewNode->array_size);
            mergeSort(leftNewNode->sorted_array, 0, leftNewNode->array_size - 1);
            copy_arr(leftNode->array, leftNode->sorted_array, leftNode->array_size);
            mergeSort(leftNode->sorted_array, 0, leftNode->array_size - 1);

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
            copy_arr(rightNewNode->array, rightNewNode->sorted_array, rightNewNode->array_size);
            mergeSort(rightNewNode->sorted_array, 0, rightNewNode->array_size - 1);
            copy_arr(rightNode->array, rightNode->sorted_array, rightNode->array_size);
            mergeSort(rightNode->sorted_array, 0, rightNode->array_size - 1);

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
            l = readInt();
            r = readInt();
            k = readInt();

            temp_left = 0;
            leftNode = list_head;
            while (temp_left + leftNode->array_size < l)
            {
                if (leftNode->array_size == 0 && leftNode->prev != NULL)
                {
                    Node *ptr = leftNode;
                    leftNode->prev->next = leftNode->next;
                    leftNode = leftNode->next;
                    leftNode->prev = leftNode->prev->prev;
                    continue;
                }
                temp_left += leftNode->array_size;
                leftNode = leftNode->next;
            }
            temp_right = temp_left;
            rightNode = leftNode;
            while (temp_right + rightNode->array_size < r)
            {

                temp_right += rightNode->array_size;
                rightNode = rightNode->next;
            }

            int index_l, index_r;
            int len_temp_arr = 0;

            if (leftNode == rightNode) //reverse的區間都再同一個node
            {
                if (leftNode->tag == isNotReverse)
                {
                    index_l = l - temp_left - 1;
                    index_r = r - temp_right - 1;
                }
                else
                {
                    index_l = leftNode->array_size - (r - temp_right);
                    index_r = leftNode->array_size - (l - temp_left);
                }
                for (; index_l <= index_r; index_l++)
                {
                    temp_arr[len_temp_arr] = leftNode->array[index_l];
                    ++len_temp_arr;
                }
                mergeSort(temp_arr, 0, len_temp_arr - 1);
                printf("%d\n", temp_arr[k - 1]);
                break;
            }
            int len_temp_arr_l = 0, len_temp_arr_r = 0;
            if (leftNode->tag == isNotReverse)
            {
                // int up_index = leftNode->array_size;
                for (int index = l - temp_left - 1; index < leftNode->array_size; ++index)
                    temp_arr_l[len_temp_arr_l++] = leftNode->array[index];
            }
            else
            {
                for (int index = leftNode->array_size - (l - temp_left); index >= 0; index--)
                    temp_arr_l[len_temp_arr_l++] = leftNode->array[index];
            }

            if (rightNode->tag == isNotReverse)
            {
                // int up_index = rightNode->array_size;
                for (int index = 0; index < r - temp_right; ++index)
                    temp_arr_r[len_temp_arr_r++] = rightNode->array[index];
            }
            else
            {
                for (int index = rightNode->array_size - (r - temp_right); index < rightNode->array_size; index++)
                    temp_arr_r[len_temp_arr_r++] = rightNode->array[index];
            }
            mergeSort(temp_arr_l, 0, len_temp_arr_l - 1);
            mergeSort(temp_arr_r, 0, len_temp_arr_r - 1);

            //sorted_arrarys: 指標array 裝著許多分別排好順序的array
            //num_of_sorted_arr: sorted_arrarys 的長度
            //bound_r: 各排好序的array的長度
            int num_of_sorted_arr = 0;
            int min = temp_arr_l[0], max = temp_arr_l[len_temp_arr_l - 1];
            int longest_arr = 0;
            int max_length = 0;

            sorted_arrarys[num_of_sorted_arr++] = temp_arr_l;
            bound_r[0] = len_temp_arr_l < k ? len_temp_arr_l : k;
            origin_lens[0] = len_temp_arr_l < k ? len_temp_arr_l : k;

            leftNode = leftNode->next;
            while (leftNode != rightNode)
            {
                if (leftNode->array_size == 0)
                {
                    leftNode = leftNode->next;
                    continue;
                }
                if (leftNode->array_size > max_length)
                {
                    max_length = leftNode->array_size;
                    longest_arr = num_of_sorted_arr;
                }

                if (leftNode->sorted_array[0] < min)
                    min = leftNode->sorted_array[0];
                if (leftNode->sorted_array[leftNode->array_size - 1] > max)
                    max = leftNode->sorted_array[leftNode->array_size - 1];
                sorted_arrarys[num_of_sorted_arr] = leftNode->sorted_array;
                bound_r[num_of_sorted_arr] = leftNode->array_size < k ? leftNode->array_size : k;
                origin_lens[num_of_sorted_arr] = leftNode->array_size < k ? leftNode->array_size : k;
                ++num_of_sorted_arr;
                leftNode = leftNode->next;
            }
            if (temp_arr_r[0] < min)
                min = temp_arr_r[0];
            if (temp_arr_r[len_temp_arr_r - 1] > max)
                max = temp_arr_r[len_temp_arr_r - 1];

            if (k == 1)
            {
                printf("%d\n", (int)min);
                break;
            }
            else if (k == r - l + 1)
            {
                printf("%d\n", (int)max);
                break;
            }

            sorted_arrarys[num_of_sorted_arr] = temp_arr_r;
            bound_r[num_of_sorted_arr] = len_temp_arr_r < k ? len_temp_arr_r : k;
            origin_lens[num_of_sorted_arr] = len_temp_arr_r < k ? len_temp_arr_r : k;
            ++num_of_sorted_arr;

            // for (int i = 0; i < num_of_sorted_arr; ++i)
            // {

            //     for (int j = 0; j < bound_r[i]; j++)
            //     {
            //         printf("%d ", sorted_arrarys[i][j]);
            //         if (j < bound_r[i] - 1)
            //             if (sorted_arrarys[i][j] < 0 && sorted_arrarys[i][j + 1] > 0)
            //                 printf(" | ");
            //     }
            //     printf("\n");
            // }
            // printf("min: %d\nmax: %d\n", min, max);

            int less_than_k = 0, more_than_k = 0;
            float mid = (float)(max + min) / 2.0 + 0.3;
            // printf("%f\n", mid);
            int bound_l[1000] = {0};
            int cnt = 0;
            while (1)
            {

                for (int i = 0; i < num_of_sorted_arr; ++i)
                {

                    index = binarySearch(sorted_arrarys[i], bound_l[i], bound_r[i], mid);
                    {
                        arr_for_indexes[i] = index;
                        less_than_k += index;
                        more_than_k += origin_lens[i] - index;
                    }
                }

                if (less_than_k == k - 1)
                {
                    int ans = 1000000;
                    for (int i = 0; i < num_of_sorted_arr; ++i)
                    {
                        if ((arr_for_indexes[i] < bound_r[i])) //arr_for_indexes[i] == -1 代表那個array全部都不小於k
                            if (sorted_arrarys[i][arr_for_indexes[i]] >= mid)
                                if (sorted_arrarys[i][arr_for_indexes[i]] < ans)
                                    ans = sorted_arrarys[i][arr_for_indexes[i]];
                    }
                    printf("%d\n", ans);
                    break;
                }
                // assert(!(less_than_k < k && more_than_k < k));

                if (less_than_k == k)
                {
                    int ans = -1000000;
                    for (int i = 0; i < num_of_sorted_arr; ++i)
                    {
                        if (arr_for_indexes[i] - 1 >= 0)
                            if (sorted_arrarys[i][arr_for_indexes[i] - 1] > ans)
                                ans = sorted_arrarys[i][arr_for_indexes[i] - 1];
                    }
                    printf("%d\n", ans);
                    break;
                }
                if (abs(max - min) <= 1)
                {
                    if (cnt < 3)
                    {
                        ++cnt;
                        // continue;
                    }
                    else
                    {
                        int ans = fabs((float)max - mid) < fabs(mid - (float)min) ? max : min;
                        printf("%d\n", ans);
                        break;
                    }
                }

                if (less_than_k < k)
                {

                    min = mid;
                    mid = (max + mid) / 2;
                    for (int i = 0; i < num_of_sorted_arr; ++i)
                    {
                        if (arr_for_indexes[i] > 0)
                            bound_l[i] = arr_for_indexes[i];
                        else
                            bound_l[i] = 0;
                    }
                }
                else
                {
                    max = mid;
                    mid = (min + mid) / 2;
                    for (int i = 0; i < num_of_sorted_arr; ++i)
                    {
                        if (arr_for_indexes[i] >= 0)
                            bound_r[i] = arr_for_indexes[i];
                        else
                            bound_r[i] = 0;
                    }
                }
                less_than_k = more_than_k = 0;
            }
        }
        // print(list, 1);
        // print_sorted(list);
    }
    // print(list, 1);
    // print_sorted(list);

    return 0;
}