#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include <assert.h>

typedef struct Node {
    unsigned int val;
    struct Node *prev, *next;
}Node;

typedef struct DList{
    Node *head;
    Node *tail;
    unsigned int size;
}DList;

DList* createDList(){
    DList *D = (DList*)malloc(sizeof(DList));
    D->head = D->tail = NULL;
    D->size = 0;
    return D;
}

inline int ReadInt();

char cmd[10];
unsigned int r, l, ra, rb, i, numOfRail_k, numOfRec_n, cnt, num;
DList *dl[1000], *D, *a, *b;
Node *temp, *curNode, *prevNode, *nextNode;
char flag, c;
int main()
{
    scanf("%d %d", &numOfRail_k, &numOfRec_n);
    i = numOfRail_k;
    while (--i){
        dl[i] = createDList();
    }
    dl[0] = createDList();

    cnt = numOfRec_n;
    
    while(cnt){
        --cnt;
        // scanf("%s", cmd);
        c = getchar();
        // flag = cmd[0];
        switch(c) {
        case 'e':
            r = 0;
            c = getchar();
            while(c <'0' || c > '9') 
                c = getchar();
            while(c>('0'-1) && c <('9'+1))
                r = r*10 + (c -'0'),c = getchar();

            l = 0;
            c = getchar();
            while(c <'0' || c > '9') 
                c = getchar();
            while(c>('0'-1) && c <('9'+1))
                l = l*10 + (c -'0'),c = getchar();
            // insert(dl[r], &l);
            D = dl[r];
            {
                Node *node = malloc(sizeof(Node));
                node->val = l;
                node->prev = node->next = NULL;

                if (!D->size) 
                    D->head = D->tail = node;
                else{
                    if (!D->tail->next){
                        D->tail->next = node;   //'''next 不一定是下一個'''
                        node->prev = D->tail;
                        D->tail = node;
                    }
                    // else if (!D->tail->prev)
                    else
                    {
                        D->tail->prev = node;
                        node->next = D->tail;
                        D->tail = node;
                    }
                }
                ++D->size;
            }
            break;

        case 'l':
            // scanf("%d", &r);
            r = ReadInt();
            // pop_back(dl[r]);
            D = dl[r];
            if (D->size)
            {
                if (D->size == 1)  //only one node
                {
                    D->tail = D->head = NULL;
                    D->size = 0;
                    // return;
                }
                else{
                    Node *ptr = D->tail;
                    if (!D->tail->next ){
                        ptr = ptr->prev;
                        if (ptr->next == D->tail)
                            ptr->next = NULL;
                        else
                            ptr->prev = NULL;
                        // free(D->tail);
                        D->tail = ptr;
                        // message("not reverse");
                    }
                    else if (!D->tail->prev ){
                        ptr = ptr->next;
                        if (ptr->prev == D->tail)
                            ptr->prev = NULL;
                        else
                            ptr->next = NULL;

                        // free(D->tail);
                        D->tail = ptr;
                        // message("reverse");
                    }
                    --D->size;
                }
            }
            break;
        case 'm':
            // scanf("%d %d", &ra, &rb);
            ra = ReadInt();
            rb = ReadInt();
            // migrate(dl[ra], dl[rb]);
            a = dl[ra];
            b = dl[rb];
            if (!a->size)
                break;
            else if (!b->size)   // b has no node
            {
                b->head = a->tail;
                b->tail = a->head;
                a->tail = a->head = NULL;
                b->size = a->size;
                a->size = 0;
                // assert(2 == 3);
            }
            else  //  b has at least one node
            {
                temp = a->head;
                a->head = a->tail;
                a->tail = temp;
                if (!b->tail->next ){
                    b->tail->next = a->head;
                    if (!a->head->prev ){
                        a->head->prev = b->tail;
                    }
                    // else if (!a->head->next )
                    else
                    {
                        a->head->next = b->tail;
                    }
                }
                else if (!b->tail->prev ){
                    b->tail->prev = a->head;
                    if (!a->head->next ){
                        a->head->next = b->tail;
                    }
                    // else if (!a->head->prev )
                    else
                    {
                        a->head->prev = b->tail;
                    }
                }
                b->tail = a->tail;
                a->head = a->tail = NULL;
                b->size += a->size;
                a->size = 0;
            }
            break;
        }
        // for(unsigned int i = 0; i < numOfRail_k; ++i)
        // {    
        //     printf("rail %d , size = %d: ", i, dl[i]->size);
        //     print(dl[i]);
        // // message("tes");
        //     if (dl[i]->size > 1 ){
        //     assert((dl[i]->head->next != NULL) || (dl[i]->head->prev != NULL));
        //     assert((dl[i]->tail->next != NULL) || (dl[i]->tail->prev != NULL));
        //     }
        // }
        // printf("\n");
    }

    for(i = 0; i < numOfRail_k; ++i)
    {
        D = dl[i];
        if (!D->size)
        {
            printf("\n");
            continue;
        }
        curNode = D->head;
        prevNode = D->head;
        while (1)
        {   
            if (curNode == D->tail){
                printf("%d\n", curNode->val);
                break;
            }
            // printf("sdf ");
            nextNode = NULL;   //你確定 next 真的是next?
            if (!curNode->prev ){  //如果curnode的prev是NULL，next就是下一個
                nextNode = curNode->next;
            }
            else if (!curNode->next){  //不然如果curnode的next是NULL，prev就是下一個
                nextNode = curNode->prev;
            }
            else if (curNode->next == prevNode){   //不然(prev, next都不是NULL)如果curnode的next是上一個node,prev就是下一個
                nextNode = curNode->prev;
            }
            else{  //不然如果curnode的prev是上一個node,next就是下一個
                nextNode = curNode->next;
            }

            // now nextNode is the True nextNode
            printf("%d ", curNode->val);
            prevNode = curNode;
            curNode = nextNode;
        }
    }
    return 0;
}

int ReadInt()
{
	num = 0;
	char c = getchar();
	while(c <'0' || c > '9') 
        c=getchar();
	while(c>('0'-1) && c <('9'+1))
		num = num*10 + (c -'0'),c = getchar();
	return num;
}

