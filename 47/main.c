#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100005
#define true 1
#define false 0

typedef int bool;

char text[MAX], garbles[MAX];

// int hash(char *s)
// {
//     int value = s[0];
//     for (int i = 1; i < strlen(s); i++)
//     {
//         value = (value << 2) + s[i];
//         // printf("%d ", value);
//     }
//     // printf("\n");
//     return value;
// }

// int reverse_hash(char *s)
// {
//     int value = 1;
//     for (int i = strlen(s); i >= 0; i--)
//     {
//         value = (value >> 2) + s[i] - 1;
//         printf("%d ", value);
//     }
//     printf("\n");
//     return value;
// }

int main()
{
    // char a[256];
    // // for (int i = 0;; i = (i << 2) - 1)
    // //     printf("%d \n", (i));
    // while (1)
    // {
    //     gets(a);
    //     // hash(a);
    //     printf("%d\n", hash(a));
    // }

    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", &text);
        scanf("%s", &garbles);
        int len_text = strlen(text);
        int len_garbles = strlen(garbles);
        int still_lacks = 0;

        int garble_require_table[200] = {0};
        for (int i = 0; i < len_garbles; ++i)
        {
            if (garble_require_table[garbles[i]] == 0)
                ++still_lacks;
            ++garble_require_table[garbles[i]];
        }
        // printf("%d\n", still_lacks);
        // for (int i = 0; i < 200; ++i)
        // {
        //     if (garble_require_table[i])
        //     {
        //         printf("%c %d\n", i, garble_require_table[i]);
        //     }
        // }

        /* find garbled text */
        int window_l = 0, window_r = 0;
        int garbled_l = 0, garbled_r = len_text - 1;
        int in_windows[200] = {0};
        while (garble_require_table[text[window_l]] == 0)
            ++window_l;
        window_r = window_l;
        bool find_garble = false;
        while (window_r < len_text)
        {
            // printf("%c\n", text[window_r]);
            if (garble_require_table[text[window_r]]) // find a char in garbled
            {
                // --garble_require_table[text[window_r]];
                ++in_windows[text[window_r]];
                if (garble_require_table[text[window_r]] == in_windows[text[window_r]])
                    --still_lacks;
            }
            if (still_lacks == 0) // find a garbled text
            {
                find_garble = true;
                // 盡可能縮小窗口
                while (true)
                {
                    if (garble_require_table[text[window_l]] > 0) // it's a garbled char
                    {
                        if (in_windows[text[window_l]] - 1 < garble_require_table[text[window_l]])
                            break;
                        --in_windows[text[window_l]];
                        ++window_l;
                    }
                    else
                        ++window_l;
                }
                garbled_l = window_l;
                garbled_r = window_r;
            }

            if (window_r < len_text)
                ++window_r;
            while (window_r - window_l >= garbled_r - garbled_l)
            {
                if (garble_require_table[text[window_l]] && in_windows[text[window_l]] == garble_require_table[text[window_l]])
                    ++still_lacks;
                --in_windows[text[window_l]];
                ++window_l;
            }
        }
        // printf("%d %d\n", garbled_l, garbled_r);
        // puts(text);
        // for (int i = 0; i < len_text; ++i)
        // {
        //     if ((i >= garbled_l && i <= garbled_r))
        //         printf("%c", text[i]);
        // }
        // printf("\n");
        // for (int i = 0; i < len_text; ++i)
        // {
        //     if (!(i >= garbled_l && i <= garbled_r))
        //         printf("%c", text[i]);
        // }
        // printf("\n");
        // if (find_garble)
        //     puts("find");
        // else
        //     puts("not found");
        int len_clean_text = 0;
        char *clean_text;
        if (find_garble)
        {
            clean_text = malloc(sizeof(char) * MAX);
            for (int i = 0; i < len_text; ++i)
            {
                if ((i >= garbled_l && i <= garbled_r))
                    continue;
                clean_text[len_clean_text++] = text[i];
            }
            clean_text[len_clean_text] = '\0';
        }
        else
        {
            clean_text = text;
            len_clean_text = len_text;
        }
        // puts(clean_text);
        int l = 0, r = len_clean_text - 1;
        int bound_l = 0, bound_r = len_clean_text - 1;
        int hash_l = 0;
        int hash_r = 0;
        bool sep[MAX] = {false};
        while (l < r)
        {
            hash_l = (hash_l << 1) + clean_text[l];
            hash_r = (hash_r) + (clean_text[r] << (bound_r - r));
            if (hash_l == hash_r)
            {
                bool match = true;
                for (int i = bound_l, j = r; i <= l; ++i, ++j)
                {
                    if (clean_text[i] != clean_text[j])
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    sep[l] = sep[r - 1] = true;
                    bound_l = l + 1;
                    bound_r = r - 1;
                    hash_r = hash_l = 0;
                }
            }
            if (l + 1 == r)
                break;
            ++l;
            --r;
            // printf("%d %d\n", l, r);
        }
        for (int i = 0; i < len_clean_text; ++i)
        {
            printf("%c", clean_text[i]);
            if (sep[i])
                printf("%c", '|');
        }
        printf("\n");
    }
    return 0;
}