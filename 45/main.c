#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#define MAX_TRIANGLES 3000000
#define true 1
#define false 0

typedef int bool;

typedef struct Triangle{
    int p;
    int q;
    int r;
} Triangle;

bool smaller_than(Triangle* a, Triangle* b)
{
    if (a->p < b->p)
        return true;
    else if (a->p == b->p)
    {
        if (a->r < b->r)
            return true;
        else if (a->r == b->r)
        {
            if (a->q < b->q)
                return true;
        }
    }
    return false;
}

Triangle *createTriangle(int p, int q, int r)
{
    Triangle *t = malloc(sizeof(Triangle));
    t->p = p;
    t->q = q;
    t->r = r;
    return t;
}
Triangle* L[MAX_TRIANGLES], *R[MAX_TRIANGLES];
void MERGE(Triangle **arr, int left, int mid, int right)
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
        if (smaller_than(L[i], R[j]))
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

void mergeSort(Triangle **arr, int left, int right)
{
    if (left < right)
    {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        MERGE(arr, left, mid, right);
    }
}

Triangle *triangle_list[MAX_TRIANGLES];

int main() 
{

    generator.init();
    int t = generator.getT();
    // printf("%d \n", t);
    while (t--) 
    {
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);
        for(int i = 0; i < n; i++)
        {
            if (q[i] > r[i])
                triangle_list[i] = createTriangle(p[i], r[i], q[i]);
            else
                triangle_list[i] = createTriangle(p[i], q[i], r[i]);
        }
        mergeSort(triangle_list, 0, n-1);
        // for (int i = 0; i < n; i++)
        // {
            
        //     printf("%d %d %d\n", triangle_list[i]->p, triangle_list[i]->q, triangle_list[i]->r);
        // }
        // for (int i = 0; i < n; i++) 
        //     printf("%d ", p[i]);
        //     printf("\n");
        // for (int i = 0; i < n; i++) 
        //     printf("%d ", q[i]);
        //     printf("\n");
        // for (int i = 0; i < n; i++) 
        //     printf("%d ", r[i]);
        //     printf("\n");
        

    }   
}
