#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int MAX_LEN = 3;
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

int n_len_int_seq, q_num_query, len, temp, i, x, l, r, k, index, index_to_delete, index_to_insert;
char cmd[10], c;
Node *curNode, *leftNode, *rightNode, *leftNewNode, *rightNewNode, *ptr1, *ptr2, *newNode, *list_tail, *list_head;
DList *list;

void check_tail(DList *list)
{
    if (list_tail->array_size == 0)
        list_tail = list_tail->prev;
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
    if (next->array_size <= MAX_LEN - prev->array_size )
    {
        if (prev->tag == isNotReverse)
        {   
            if(next->tag == isNotReverse)
            {     
                int prev_index = prev->array_size;
                int post_index = 0;
                int up_index = next->array_size;
                for(; post_index < up_index; ++post_index, ++prev_index)
                {
                    prev->array[prev_index] = next->array[post_index];
                    ++prev->array_size; -- next->array_size;
                }
            }
            else
            {
                int prev_index = prev->array_size;
                int post_index = next->array_size-1;
                // int up_index = next->array_size;
                for(; post_index >= 0; --post_index, ++prev_index)
                {
                    prev->array[prev_index] = next->array[post_index];
                    ++prev->array_size; -- next->array_size;
                }
                
            }
            prev->next = next->next;
            if (next!=list_tail)
                next->next->prev = prev;
            else
                list_tail = prev;
            free(next);
            flag = 1;
        }
    }
    return flag;
}

void traverse_merge()
{
    int flag = 0;
    Node* curNode = list_head;
    while(curNode->next != list_tail && curNode->next != NULL)
    {
        flag = merge(curNode, curNode->next);
        if (flag==0)
            curNode = curNode->next;
        // text("hi");
    }

}






int main()
{
    // scanf("%d %d", &n_len_int_seq, &q_num_query);
    n_len_int_seq = readInt();
    q_num_query = readInt();
    MAX_LEN = (int)sqrt(n_len_int_seq);
    // printf("hello");
    list = createDList();
    list_tail = list_head = createNode();
    ++list->list_size;
    curNode = list_head;
    for (i = 0; i < n_len_int_seq; ++i)
    {
        temp = readInt();

        if (!(curNode->array_size < MAX_LEN *95/100))
        {
            Node *newNode = createNode();
            list_tail = newNode;
            curNode->next = newNode;
            newNode->prev = curNode;
            curNode = curNode->next;
            ++list->list_size;
        }
        curNode->array[curNode->array_size++] = temp;
        ++list->total_element;
    }
    // print(list, 1);
    // curNode = list_head;
    // while (curNode != NULL){
    //     for (int i = 0; i < curNode->array_size; ++i)
    //         printf("%d ", curNode->array[i]);
    //     curNode = curNode->next;
    // }
    // printf("\n");
    int counter = 0;
    while ((c = getchar()) != EOF)
    {
        ++counter;
        if (c == '\n')
            continue;

        curNode = list_head;
        switch (c)
        {
        case 'I':
            // insert an integer x before the ith element of the sequence.
            // If i − 1 equals the length of the sequence, then insert x at the end of it.
            i = readInt();
            x = readInt();
            if (i == 1)
            {   
            //     // text("hi");
            //     if(curNode->array_size != MAX_LEN)
            //     {
            //         if (curNode->tag == isReverse )
            //             curNode->array[curNode->array_size++] = x;
            //         else
            //         {
            //             for (int index = curNode->array_size; index > 0; --index)
            //                 curNode->array[index] = curNode->array[index - 1];
            //             curNode->array[0] = x;
            //             ++curNode->array_size;
            //         }
            //     }    
            //     else
                {   
                    newNode = createNode();
                    newNode->array[newNode->array_size++] = x;
                    newNode->next = list_head;
                    list_head->prev = newNode;
                    list_head = newNode;
                    ++list->list_size;
                }
            }
            else if (i == list->total_element)
            {
                
                // list_tail->next = newNode;
                if (list_tail->array_size == MAX_LEN)
                {
                    newNode = createNode();
                    newNode->prev = list_tail;
                    list_tail->next = newNode;
                    newNode->array[newNode->array_size++] = list_tail->array[list_tail->array_size-1];
                    list_tail->array[list_tail->array_size - 1] = x;
                    list_tail = newNode;

                    // ++list->list_size;
                }
                // curNode = list_tail;
                else if (list_tail->tag == isNotReverse)
                {
                    // newNode = createNode();
                    list_tail->array[list_tail->array_size] = list_tail->array[list_tail->array_size - 1];
                    list_tail->array[list_tail->array_size -1 ] = x;
                    ++list_tail->array_size;
                        }
                else
                {
                    for (int index = list_tail->array_size; index > 1; index--)
                        list_tail->array[index] = list_tail->array[index - 1];
                    list_tail->array[1] = x;
                    ++list_tail->array_size;
                }
            }
            else if (i - 1 == list->total_element)
            {
                // if (list_tail->tag == isNotReverse)
                {
                    newNode = createNode();
                    newNode->array[newNode->array_size++] = x;
                    list_tail->next = newNode;
                    newNode->prev = list_tail;
                    ++list->list_size;
                    list_tail = newNode;
                }
                // else
                // assert(1 == 2);
            }
            else
            {
                temp = 0;
                while (temp + curNode->array_size < i)
                {
                    // if (x-temp)
                    // merge(curNode, curNode->next);
                    temp += curNode->array_size;
                    if (curNode->next == NULL)
                    {
                        newNode = createNode();
                        newNode->prev = curNode;
                        curNode->next = newNode;
                        // ++lis
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
                            if (curNode->prev->array_size < MAX_LEN && curNode->prev->tag == isNotReverse)
                            {
                                curNode = curNode->prev;
                                curNode->array[curNode->array_size++] = x;
                            }
                            // else if (curNode->prev->array_size < MAX_LEN && curNode->prev->tag == isReverse)
                            // {
                            //     curNode = curNode->prev;
                            // }
                            else
                            {
                                newNode = createNode();
                                newNode->array[newNode->array_size++] = x;

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
                            newNode = createNode();
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

                            ++list->list_size;
                        }
                    }
                    else //順序是反的
                    {
                        if (i - temp == 1) //滿了又要插在這個array的頭 (其實是尾端)
                        {                  //如果前面node還有空位而且順序是正向的就直接丟過去
                            if (curNode->prev->array_size < MAX_LEN && curNode->prev->tag == isNotReverse)
                            {
                                curNode = curNode->prev;
                                curNode->array[curNode->array_size++] = x;
                            }
                            else //不然就新增node，因為順序是反的，新增的Node要放在這個前面
                            {
                                newNode = createNode();
                                newNode->array[newNode->array_size++] = x;

                                // ++newNode->array_size;
                                newNode->next = curNode;
                                newNode->prev = curNode->prev;
                                curNode->prev->next = newNode;
                                curNode->prev = newNode;
                                ++list->list_size;
                            }
                        }
                        else //滿了又要插在這個array的中間，且array是反的
                        {    //就往前新增Node，從這個array的插入點往前推一格(因為是反的)
                            newNode = createNode();
                            newNode->next = curNode->next;
                            curNode->next->prev = newNode;
                            newNode->prev = curNode;
                            curNode->next = newNode;

                            newNode->array[newNode->array_size++] = curNode->array[0];
                            index = 0;
                            index_to_insert = curNode->array_size - (i - temp);
                            for (; index != index_to_insert; ++index)
                            {
                                curNode->array[index] = curNode->array[index + 1];
                                // newNode->array[newNode->array_size++] = curNode->array[index + i - temp - 1];
                                // --curNode->array_size;
                            }
                            curNode->array[index] = x;

                            ++list->list_size;
                        }
                        check_tail(list);
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
                                curNode->array[curNode->array_size++] = x;
                            }
                        }
                        else
                        {
                            for (int index = curNode->array_size; index > (i - temp - 1); index--)
                                curNode->array[index] = curNode->array[index - 1];
                            curNode->array[i - temp - 1] = x;

                            curNode->array_size++;
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
                        curNode->array_size++;

                    }
                }
            }
            ++list->total_element;
            // print(list, 1);
            // traverse_merge();
            break;
        case 'D':
            i = readInt();

            temp = 0;
            if (i == list->total_element && list_tail->tag == isNotReverse)
            {
                curNode = list_tail;
                // if (curNode->tag == isNotReverse)
                --curNode->array_size;
                --list->total_element;
                // check_tail();
                if (curNode->array_size == 0)
                {
                    list_tail = curNode->prev;
                    list_tail->next = NULL;
                    free(curNode);
                }
                break;
            }
            while (temp + curNode->array_size < i)
            {
                // if (x-temp)
                // merge(curNode, curNode->next);
                temp += curNode->array_size;
                if (curNode->next == NULL)
                {
                    newNode = createNode();
                    newNode->prev = curNode;
                    curNode->next = newNode;
                }
                // merge(curNode, curNode->next);
                curNode = curNode->next;
            }
            // printf("%d\n", curNode->array[0]);

            if (curNode->array_size == 1)
            {
                if (curNode == list_head)
                {
                    curNode->next->prev = NULL;
                    list_head = curNode->next;
                    free(curNode);
                }
                else if (curNode == list_tail)
                {
                    list_tail = curNode->prev;
                }
                else
                {
                    curNode->next->prev = curNode->prev;
                    curNode->prev->next = curNode->next;
                    free(curNode);
                }
                --list->list_size;
            }
            else if (curNode->tag == isNotReverse)
            {
                index_to_delete = i - temp - 1;
                len = curNode->array_size;
                for (index = index_to_delete; index < len - 1; ++index)
                {
                    curNode->array[index] = curNode->array[index + 1];
                }
                --curNode->array_size;
            }
            else if (curNode->tag == isReverse)
            {
                index_to_delete = curNode->array_size - (i - temp);
                len = curNode->array_size;
                for (index = index_to_delete; index < len - 1; ++index)
                {
                    curNode->array[index] = curNode->array[index + 1];
                }
                --curNode->array_size;
                if (curNode->array_size == 1)
                    curNode->tag = isNotReverse;
            }
            // else
            //     assert(1 == 2);

            --list->total_element;

            break;
        case 'R':
            l = readInt();
            r = readInt();
            if (l == r)
                break;
            int temp_left = 0;
            leftNode = list_head;
            while (temp_left + leftNode->array_size < l)
            {
                if (leftNode->array_size == 0 && leftNode->prev != NULL)
                {
                    ptr1 = leftNode;
                    leftNode->prev->next = leftNode->next;
                    leftNode = leftNode->next;
                    leftNode->prev = leftNode->prev->prev;
                    free(ptr1);
                    continue;
                }
                temp_left += leftNode->array_size;
                leftNode = leftNode->next;
                // merge(leftNode, leftNode->next);
                // if (leftNode->array_size == 1)
                //     assert(leftNode->tag == isNotReverse);
            }
            int temp_right = temp_left;
            rightNode = leftNode;
            while (temp_right + rightNode->array_size < r)
            {
                if (rightNode->array_size == 0 && rightNode->prev != NULL)
                {
                    ptr1 = rightNode;
                    rightNode->prev->next = rightNode->next;
                    rightNode = rightNode->next;
                    rightNode->prev = rightNode->prev->prev;
                    free(ptr1);
                    continue;
                }
                temp_right += rightNode->array_size;
                rightNode = rightNode->next;
                // if (rightNode->array_size == 1)
                //     assert(rightNode->tag == isNotReverse);
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
            if (l-temp_left == 1 && r - temp_right == rightNode->array_size && leftNode != list_head && rightNode != list_tail)
            {
                Node *a = leftNode->prev, *b = rightNode->next;
                leftNode->prev->next = rightNode;
                // text("hi");
                rightNode->next->prev = leftNode;

                ptr1 = leftNode->prev;
                ptr2 = leftNode;
                // ptr1->next = rightNode;
                // ptr1->prev = ptr2;
                while (ptr2 != rightNode)
                {

                    changeTag(ptr2);
                    if (ptr2->array_size == 1)
                        ptr2->tag = isNotReverse;
                    ptr2->prev = ptr2->next;
                    ptr2->next = ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr2->prev;
                }
                changeTag(rightNode); //while迴圈會被改到，改回來
                // rightNode->prev = leftNode;
                ptr2->next = ptr1;
                rightNode->prev = a;
                leftNode->next = b;
                // rightNode->prev = leftNewNode;
                if (rightNode->array_size == 1)
                    rightNode->tag = isNotReverse;

                check_tail(list);
                break;
            }
            
            //把兩端移到外側
            // if (leftNode->array_size <= MAX_LEN - leftNode->prev->array_size && rightNode->array_size <= MAX_LEN - rightNode->next->array_size)
            // {
            //     if (leftNode->prev->tag == isNotReverse && leftNode->tag == isNotReverse)
            //     {
            //         int prev_index = leftNode->prev->array_size;
            //         int post_index = 0;
            //         up_index = leftNode->array_size;
            //         for(; post_index < up_index; ++post_index, ++prev_index)
            //             leftNode->prev->array[prev_index] = leftNode->array[post_index];
            //     }
            //     // else
            //     // {
            //     //     ;
            //     // }
                
            // }

            

            leftNewNode = createNode();
            rightNewNode = createNode();
            // ++list->list_size;
            // ++list->list_size;
            leftNewNode->next = leftNode->next;
            leftNewNode->prev = leftNode;
            leftNode->next->prev = leftNewNode;
            leftNode->next = leftNewNode;
            rightNewNode->next = rightNode;
            rightNewNode->prev = rightNode->prev;
            rightNode->prev->next = rightNewNode;
            rightNode->prev = rightNewNode;

            ptr1 = leftNewNode;
            ptr2 = leftNewNode->next;
            ptr1->next = rightNode;
            ptr1->prev = ptr2;
            while (ptr2 != rightNode)
            {

                changeTag(ptr2);
                if (ptr2->array_size == 1)
                    ptr2->tag = isNotReverse;
                ptr2->prev = ptr2->next;
                ptr2->next = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr2->prev;
            }
            changeTag(rightNewNode); //while迴圈會被改到，改回來
            rightNewNode->prev = leftNode;
            leftNode->next = rightNewNode;
            rightNode->prev = leftNewNode;
            if (rightNode->array_size == 1)
                rightNode->tag = isNotReverse;

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


            // if (rightNewNode->array_size <= MAX_LEN - leftNode->array_size )
            // {
            //     if (rightNewNode->tag == isNotReverse && leftNode->tag == isNotReverse)
            //     {
            //         int prev_index = leftNode->array_size;
            //         int post_index = 0;
            //         int up_index = rightNewNode->array_size;
            //         for(; post_index < up_index; ++post_index, ++prev_index)
            //         {
            //             leftNode->array[prev_index] = rightNewNode->array[post_index];
            //             ++leftNode->array_size; -- rightNewNode->array_size;
            //         }
            //         leftNode->next = rightNewNode->next;
            //         rightNewNode->next->prev = leftNode;
            //         free(rightNewNode);
            //     }
                
            // }
            // merge(leftNode, rightNewNode);
            // merge(leftNewNode, rightNode);
            // if (rightNewNode->array_size <= MAX_LEN - rightNode->array_size){}
            

            traverse_merge();
            check_tail(list);
            break;
        case 'Q':
            // text("query");
            l = readInt();
            r = readInt();
            k = readInt();
            break;

        
        }
        // print(list, 1);
// if (counter%10 == 0)
//             traverse_merge();
    }
    // Node *curNode = list_head;
    // while (curNode != NULL)
    // {
    //     for (int i = 0; i < curNode->array_size; ++i)
    //         printf("%d ", curNode->array[i]);
    //     curNode = curNode->next;
    // }
    print(list,0);
    // printf("MAX_LEN :%d\n", MAX_LEN);
    // count_node(list);
    // printf("total element: %d\neach node contains %f elements\n", list->total_element, (float)(list->total_element) / num_nodes);
    // printf("full rate: %.2f%%\n", (float)(list->total_element) / num_nodes / MAX_LEN * 100);
    return 0;
}


