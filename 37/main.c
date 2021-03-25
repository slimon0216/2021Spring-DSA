#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100000;

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

int n_len_int_seq, q_num_query, len, temp, i;
char cmd[10];

void text(char * s){
    printf("%s\n", s);
}

// Node* creatNode(int val){
//     Node* node = malloc(sizeof(Node));
//     node->val = val;
//     node->next = node->prev = NULL;
//     return Node;
// }

void insert(int val){

}

int main()
{
    scanf("%d %d", &n_len_int_seq, &q_num_query);
    // printf("hello");
    Dlist *list = createDList();

    for (i = 0; i < n_len_int_seq; ++i){
        scanf("%d", &temp);
        
    }
    // for (int i = 0; i < len; ++i){
    //     printf("%d ", list[i]);
    // }
    for (int i = 0; i < q_num_query; ++i)
    {
        scanf("%s", cmd);
        switch (cmd[0]){
            case 'I':
                text("in");
                break;
            case 'D':
                text("de");
                break;
            case 'Q':
                text("query");
                break;
            case 'R':
                break;
        }
    }
    return 0;
}