#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "generator.h"
#define MAX_TRIANGLES (3000000 + 10)
#define MAX_PQR (1048576 + 10)

#define true 1
#define false 0

typedef int bool;
typedef long long int ll;

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
        if (a->r > b->r)
            return true;
        else if (a->r == b->r)
        {
            if (a->q > b->q)
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

int BIT[MAX_PQR]={0}, counts_R[MAX_PQR]={0};
void update(int x, int delta)
{
      for(; x <= MAX_PQR; x += x&-x)
        BIT[x] += delta;
}

int query(int x)
{
     int sum = 0;
     for(; x > 0; x -= x&-x)
        sum += BIT[x];
     return sum;
}



int main() 
{
    // printf("%d\n", MAX_PQR);
    generator.init();
    int t = generator.getT();
    // printf("%d \n", t);
    while (t--) 
    {
        int n, *p, *q, *r;
        ll ans = 0;
        generator.getData(&n, &p, &q, &r);
        for(int i = 0; i < n; i++)
        { 
            if (q[i] > r[i])
                triangle_list[i] = createTriangle(p[i]+MAX_PQR, r[i]+MAX_PQR, q[i]+MAX_PQR);
            else
                triangle_list[i] = createTriangle(p[i]+MAX_PQR, q[i]+MAX_PQR, r[i]+MAX_PQR);
        }
        mergeSort(triangle_list, 0, n-1);
        // for (int i = 0; i < n; i++)
        // {
        //     printf("%d %d %d\n", triangle_list[i]->p-MAX_PQR, triangle_list[i]->q-MAX_PQR, triangle_list[i]->r-MAX_PQR);
        // }
        int num_of_r_in_bit = 0;
        for (int i = 0; i < n; ++i)
        {  
            // 去看左頂點 q 跨過多少 r

            // printf("q: %d\n", (triangle_list[i]->q)-MAX_PQR);
            ans += num_of_r_in_bit - query(triangle_list[i]->q ) ;
            // printf("ans += %d - %d\n", num_of_r_in_bit , query(triangle_list[i]->q));
            // printf("ans: %d\n", ans);
            counts_R[triangle_list[i]->r]++;
            update(triangle_list[i]->r, counts_R[triangle_list[i]->r]);
            ++num_of_r_in_bit;
            // for (ll j = 1048579; j <= 1048599;++j)
            // {
            //     printf("%d ", counts_R[j]);
            // }
            // printf("\n");
        }
        printf("%ld\n", ans);
        for (int i = 0; i < MAX_PQR; i++)
        {
            BIT[i] = 0;
            counts_R[i] = 0;
        }
    }
    
    return 0;
}
