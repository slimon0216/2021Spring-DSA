#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    system("gcc main.c -static -O0 -std=c11 -g -lm");
    system("gcc -o check check.c");
    return 0;
}
