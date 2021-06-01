#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include <time.h>
#define MAX 100005

#define true 1
#define false 0
typedef struct Node
{
    int data;
    struct Node *next;

} Node;

inline Node *createNode(const unsigned int data);

typedef struct Queue
{
    Node *head;
    Node *tail;
} Queue;

inline void push_back(Queue *q, const unsigned int len);

inline void pop_front(Queue *q);

inline unsigned int queue_isEmpty(const Queue *q);

typedef struct Stack
{
    unsigned int array[2 * MAX];
    unsigned int size;
} Stack;

Stack *createStack()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->size = -1;
    return stack;
}

inline void push(Stack *stack, unsigned int value);
inline void pop(Stack *stack);
inline unsigned int stack_isEmpty(const Stack *stack);

inline unsigned int top(const Stack *stack);
inline unsigned int readInt();
unsigned int *adj_list[MAX];
unsigned int N;
unsigned int len;
unsigned int table[MAX] = {false};
unsigned int ans[15 * MAX] = {0};
unsigned int len_ans = 0;
Queue *q[MAX];
unsigned int temp;
int main()
{
    // double begin = clock();
    setvbuf(stdin, calloc(1 << 26, sizeof(char)), _IOFBF, 1 << 26);
    setvbuf(stdout, calloc(1 << 26, sizeof(char)), _IOFBF, 1 << 26);
    N = readInt();
    Stack *stack = createStack();
    for (unsigned int i = 1; i < N + 1; ++i)
    {
        q[i] = malloc(sizeof(Queue));
        q[i]->head = q[i]->tail = NULL;
        len = readInt();

        // temp = readInt();
        push_back(q[i], len);
    }

    unsigned int i = 1;
    unsigned int from, to;
    while (i <= N)
    {
        if (queue_isEmpty(q[i]) == false)
        {
            push(stack, i);
            table[i] = true;
        }

        while (stack_isEmpty(stack) == false)
        {

            while (queue_isEmpty(q[top(stack)]) == false)
            {
                from = top(stack);
                to = q[from]->head->data;
                if (q[to]->head->data == from)
                {
                    ans[len_ans++] = from;
                    ans[len_ans++] = to;

                    // printf("%d %d\n", from, to);
                    //真的去pop
                    pop_front(q[to]);
                    pop_front(q[from]);

                    if (!stack_isEmpty(stack))
                    {
                        table[from] = false;
                        pop(stack);
                        // flag = true;
                        break;
                    }
                }
                else if (table[to] == true)
                {
                    printf("No\n");
                    return 0;
                }
                else
                {
                    table[to] = true;
                    push(stack, to);
                }
                if (queue_isEmpty(q[top(stack)]) == true)
                    break;
            }
        }
        if (queue_isEmpty(q[i]))
            ++i;
    }
    // printf("Yes\n");
    puts("Yes");
    i = 0;
    for (; i + 400 < len_ans; i += 400)
    {
        printf("%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n",
               ans[i], ans[i + 1],
               ans[i + 2], ans[i + 3],
               ans[i + 4], ans[i + 5],
               ans[i + 6], ans[i + 7],
               ans[i + 8], ans[i + 9],
               ans[i + 10], ans[i + 11],
               ans[i + 12], ans[i + 13],
               ans[i + 14], ans[i + 15],
               ans[i + 16], ans[i + 17],
               ans[i + 18], ans[i + 19],
               ans[i + 20], ans[i + 21],
               ans[i + 22], ans[i + 23],
               ans[i + 24], ans[i + 25],
               ans[i + 26], ans[i + 27],
               ans[i + 28], ans[i + 29],
               ans[i + 30], ans[i + 31],
               ans[i + 32], ans[i + 33],
               ans[i + 34], ans[i + 35],
               ans[i + 36], ans[i + 37],
               ans[i + 38], ans[i + 39],
               ans[i + 40], ans[i + 41],
               ans[i + 42], ans[i + 43],
               ans[i + 44], ans[i + 45],
               ans[i + 46], ans[i + 47],
               ans[i + 48], ans[i + 49],
               ans[i + 50], ans[i + 51],
               ans[i + 52], ans[i + 53],
               ans[i + 54], ans[i + 55],
               ans[i + 56], ans[i + 57],
               ans[i + 58], ans[i + 59],
               ans[i + 60], ans[i + 61],
               ans[i + 62], ans[i + 63],
               ans[i + 64], ans[i + 65],
               ans[i + 66], ans[i + 67],
               ans[i + 68], ans[i + 69],
               ans[i + 70], ans[i + 71],
               ans[i + 72], ans[i + 73],
               ans[i + 74], ans[i + 75],
               ans[i + 76], ans[i + 77],
               ans[i + 78], ans[i + 79],
               ans[i + 80], ans[i + 81],
               ans[i + 82], ans[i + 83],
               ans[i + 84], ans[i + 85],
               ans[i + 86], ans[i + 87],
               ans[i + 88], ans[i + 89],
               ans[i + 90], ans[i + 91],
               ans[i + 92], ans[i + 93],
               ans[i + 94], ans[i + 95],
               ans[i + 96], ans[i + 97],
               ans[i + 98], ans[i + 99],
               ans[i + 100], ans[i + 101],
               ans[i + 102], ans[i + 103],
               ans[i + 104], ans[i + 105],
               ans[i + 106], ans[i + 107],
               ans[i + 108], ans[i + 109],
               ans[i + 110], ans[i + 111],
               ans[i + 112], ans[i + 113],
               ans[i + 114], ans[i + 115],
               ans[i + 116], ans[i + 117],
               ans[i + 118], ans[i + 119],
               ans[i + 120], ans[i + 121],
               ans[i + 122], ans[i + 123],
               ans[i + 124], ans[i + 125],
               ans[i + 126], ans[i + 127],
               ans[i + 128], ans[i + 129],
               ans[i + 130], ans[i + 131],
               ans[i + 132], ans[i + 133],
               ans[i + 134], ans[i + 135],
               ans[i + 136], ans[i + 137],
               ans[i + 138], ans[i + 139],
               ans[i + 140], ans[i + 141],
               ans[i + 142], ans[i + 143],
               ans[i + 144], ans[i + 145],
               ans[i + 146], ans[i + 147],
               ans[i + 148], ans[i + 149],
               ans[i + 150], ans[i + 151],
               ans[i + 152], ans[i + 153],
               ans[i + 154], ans[i + 155],
               ans[i + 156], ans[i + 157],
               ans[i + 158], ans[i + 159],
               ans[i + 160], ans[i + 161],
               ans[i + 162], ans[i + 163],
               ans[i + 164], ans[i + 165],
               ans[i + 166], ans[i + 167],
               ans[i + 168], ans[i + 169],
               ans[i + 170], ans[i + 171],
               ans[i + 172], ans[i + 173],
               ans[i + 174], ans[i + 175],
               ans[i + 176], ans[i + 177],
               ans[i + 178], ans[i + 179],
               ans[i + 180], ans[i + 181],
               ans[i + 182], ans[i + 183],
               ans[i + 184], ans[i + 185],
               ans[i + 186], ans[i + 187],
               ans[i + 188], ans[i + 189],
               ans[i + 190], ans[i + 191],
               ans[i + 192], ans[i + 193],
               ans[i + 194], ans[i + 195],
               ans[i + 196], ans[i + 197],
               ans[i + 198], ans[i + 199],
               ans[i + 200], ans[i + 201],
               ans[i + 202], ans[i + 203],
               ans[i + 204], ans[i + 205],
               ans[i + 206], ans[i + 207],
               ans[i + 208], ans[i + 209],
               ans[i + 210], ans[i + 211],
               ans[i + 212], ans[i + 213],
               ans[i + 214], ans[i + 215],
               ans[i + 216], ans[i + 217],
               ans[i + 218], ans[i + 219],
               ans[i + 220], ans[i + 221],
               ans[i + 222], ans[i + 223],
               ans[i + 224], ans[i + 225],
               ans[i + 226], ans[i + 227],
               ans[i + 228], ans[i + 229],
               ans[i + 230], ans[i + 231],
               ans[i + 232], ans[i + 233],
               ans[i + 234], ans[i + 235],
               ans[i + 236], ans[i + 237],
               ans[i + 238], ans[i + 239],
               ans[i + 240], ans[i + 241],
               ans[i + 242], ans[i + 243],
               ans[i + 244], ans[i + 245],
               ans[i + 246], ans[i + 247],
               ans[i + 248], ans[i + 249],
               ans[i + 250], ans[i + 251],
               ans[i + 252], ans[i + 253],
               ans[i + 254], ans[i + 255],
               ans[i + 256], ans[i + 257],
               ans[i + 258], ans[i + 259],
               ans[i + 260], ans[i + 261],
               ans[i + 262], ans[i + 263],
               ans[i + 264], ans[i + 265],
               ans[i + 266], ans[i + 267],
               ans[i + 268], ans[i + 269],
               ans[i + 270], ans[i + 271],
               ans[i + 272], ans[i + 273],
               ans[i + 274], ans[i + 275],
               ans[i + 276], ans[i + 277],
               ans[i + 278], ans[i + 279],
               ans[i + 280], ans[i + 281],
               ans[i + 282], ans[i + 283],
               ans[i + 284], ans[i + 285],
               ans[i + 286], ans[i + 287],
               ans[i + 288], ans[i + 289],
               ans[i + 290], ans[i + 291],
               ans[i + 292], ans[i + 293],
               ans[i + 294], ans[i + 295],
               ans[i + 296], ans[i + 297],
               ans[i + 298], ans[i + 299],
               ans[i + 300], ans[i + 301],
               ans[i + 302], ans[i + 303],
               ans[i + 304], ans[i + 305],
               ans[i + 306], ans[i + 307],
               ans[i + 308], ans[i + 309],
               ans[i + 310], ans[i + 311],
               ans[i + 312], ans[i + 313],
               ans[i + 314], ans[i + 315],
               ans[i + 316], ans[i + 317],
               ans[i + 318], ans[i + 319],
               ans[i + 320], ans[i + 321],
               ans[i + 322], ans[i + 323],
               ans[i + 324], ans[i + 325],
               ans[i + 326], ans[i + 327],
               ans[i + 328], ans[i + 329],
               ans[i + 330], ans[i + 331],
               ans[i + 332], ans[i + 333],
               ans[i + 334], ans[i + 335],
               ans[i + 336], ans[i + 337],
               ans[i + 338], ans[i + 339],
               ans[i + 340], ans[i + 341],
               ans[i + 342], ans[i + 343],
               ans[i + 344], ans[i + 345],
               ans[i + 346], ans[i + 347],
               ans[i + 348], ans[i + 349],
               ans[i + 350], ans[i + 351],
               ans[i + 352], ans[i + 353],
               ans[i + 354], ans[i + 355],
               ans[i + 356], ans[i + 357],
               ans[i + 358], ans[i + 359],
               ans[i + 360], ans[i + 361],
               ans[i + 362], ans[i + 363],
               ans[i + 364], ans[i + 365],
               ans[i + 366], ans[i + 367],
               ans[i + 368], ans[i + 369],
               ans[i + 370], ans[i + 371],
               ans[i + 372], ans[i + 373],
               ans[i + 374], ans[i + 375],
               ans[i + 376], ans[i + 377],
               ans[i + 378], ans[i + 379],
               ans[i + 380], ans[i + 381],
               ans[i + 382], ans[i + 383],
               ans[i + 384], ans[i + 385],
               ans[i + 386], ans[i + 387],
               ans[i + 388], ans[i + 389],
               ans[i + 390], ans[i + 391],
               ans[i + 392], ans[i + 393],
               ans[i + 394], ans[i + 395],
               ans[i + 396], ans[i + 397],
               ans[i + 398], ans[i + 399],
               ans[i + 400], ans[i + 401],
               ans[i + 402], ans[i + 403],
               ans[i + 404], ans[i + 405],
               ans[i + 406], ans[i + 407],
               ans[i + 408], ans[i + 409],
               ans[i + 410], ans[i + 411],
               ans[i + 412], ans[i + 413],
               ans[i + 414], ans[i + 415],
               ans[i + 416], ans[i + 417],
               ans[i + 418], ans[i + 419],
               ans[i + 420], ans[i + 421],
               ans[i + 422], ans[i + 423],
               ans[i + 424], ans[i + 425],
               ans[i + 426], ans[i + 427],
               ans[i + 428], ans[i + 429],
               ans[i + 430], ans[i + 431],
               ans[i + 432], ans[i + 433],
               ans[i + 434], ans[i + 435],
               ans[i + 436], ans[i + 437],
               ans[i + 438], ans[i + 439],
               ans[i + 440], ans[i + 441],
               ans[i + 442], ans[i + 443],
               ans[i + 444], ans[i + 445],
               ans[i + 446], ans[i + 447],
               ans[i + 448], ans[i + 449],
               ans[i + 450], ans[i + 451],
               ans[i + 452], ans[i + 453],
               ans[i + 454], ans[i + 455],
               ans[i + 456], ans[i + 457],
               ans[i + 458], ans[i + 459],
               ans[i + 460], ans[i + 461],
               ans[i + 462], ans[i + 463],
               ans[i + 464], ans[i + 465],
               ans[i + 466], ans[i + 467],
               ans[i + 468], ans[i + 469],
               ans[i + 470], ans[i + 471],
               ans[i + 472], ans[i + 473],
               ans[i + 474], ans[i + 475],
               ans[i + 476], ans[i + 477],
               ans[i + 478], ans[i + 479],
               ans[i + 480], ans[i + 481],
               ans[i + 482], ans[i + 483],
               ans[i + 484], ans[i + 485],
               ans[i + 486], ans[i + 487],
               ans[i + 488], ans[i + 489],
               ans[i + 490], ans[i + 491],
               ans[i + 492], ans[i + 493],
               ans[i + 494], ans[i + 495],
               ans[i + 496], ans[i + 497],
               ans[i + 498], ans[i + 499],
               ans[i + 500], ans[i + 501],
               ans[i + 502], ans[i + 503],
               ans[i + 504], ans[i + 505],
               ans[i + 506], ans[i + 507],
               ans[i + 508], ans[i + 509],
               ans[i + 510], ans[i + 511],
               ans[i + 512], ans[i + 513],
               ans[i + 514], ans[i + 515],
               ans[i + 516], ans[i + 517],
               ans[i + 518], ans[i + 519],
               ans[i + 520], ans[i + 521],
               ans[i + 522], ans[i + 523],
               ans[i + 524], ans[i + 525],
               ans[i + 526], ans[i + 527],
               ans[i + 528], ans[i + 529],
               ans[i + 530], ans[i + 531],
               ans[i + 532], ans[i + 533],
               ans[i + 534], ans[i + 535],
               ans[i + 536], ans[i + 537],
               ans[i + 538], ans[i + 539],
               ans[i + 540], ans[i + 541],
               ans[i + 542], ans[i + 543],
               ans[i + 544], ans[i + 545],
               ans[i + 546], ans[i + 547],
               ans[i + 548], ans[i + 549],
               ans[i + 550], ans[i + 551],
               ans[i + 552], ans[i + 553],
               ans[i + 554], ans[i + 555],
               ans[i + 556], ans[i + 557],
               ans[i + 558], ans[i + 559],
               ans[i + 560], ans[i + 561],
               ans[i + 562], ans[i + 563],
               ans[i + 564], ans[i + 565],
               ans[i + 566], ans[i + 567],
               ans[i + 568], ans[i + 569],
               ans[i + 570], ans[i + 571],
               ans[i + 572], ans[i + 573],
               ans[i + 574], ans[i + 575],
               ans[i + 576], ans[i + 577],
               ans[i + 578], ans[i + 579],
               ans[i + 580], ans[i + 581],
               ans[i + 582], ans[i + 583],
               ans[i + 584], ans[i + 585],
               ans[i + 586], ans[i + 587],
               ans[i + 588], ans[i + 589],
               ans[i + 590], ans[i + 591],
               ans[i + 592], ans[i + 593],
               ans[i + 594], ans[i + 595],
               ans[i + 596], ans[i + 597],
               ans[i + 598], ans[i + 599],
               ans[i + 600], ans[i + 601],
               ans[i + 602], ans[i + 603],
               ans[i + 604], ans[i + 605],
               ans[i + 606], ans[i + 607],
               ans[i + 608], ans[i + 609],
               ans[i + 610], ans[i + 611],
               ans[i + 612], ans[i + 613],
               ans[i + 614], ans[i + 615],
               ans[i + 616], ans[i + 617],
               ans[i + 618], ans[i + 619],
               ans[i + 620], ans[i + 621],
               ans[i + 622], ans[i + 623],
               ans[i + 624], ans[i + 625],
               ans[i + 626], ans[i + 627],
               ans[i + 628], ans[i + 629],
               ans[i + 630], ans[i + 631],
               ans[i + 632], ans[i + 633],
               ans[i + 634], ans[i + 635],
               ans[i + 636], ans[i + 637],
               ans[i + 638], ans[i + 639],
               ans[i + 640], ans[i + 641],
               ans[i + 642], ans[i + 643],
               ans[i + 644], ans[i + 645],
               ans[i + 646], ans[i + 647],
               ans[i + 648], ans[i + 649],
               ans[i + 650], ans[i + 651],
               ans[i + 652], ans[i + 653],
               ans[i + 654], ans[i + 655],
               ans[i + 656], ans[i + 657],
               ans[i + 658], ans[i + 659],
               ans[i + 660], ans[i + 661],
               ans[i + 662], ans[i + 663],
               ans[i + 664], ans[i + 665],
               ans[i + 666], ans[i + 667],
               ans[i + 668], ans[i + 669],
               ans[i + 670], ans[i + 671],
               ans[i + 672], ans[i + 673],
               ans[i + 674], ans[i + 675],
               ans[i + 676], ans[i + 677],
               ans[i + 678], ans[i + 679],
               ans[i + 680], ans[i + 681],
               ans[i + 682], ans[i + 683],
               ans[i + 684], ans[i + 685],
               ans[i + 686], ans[i + 687],
               ans[i + 688], ans[i + 689],
               ans[i + 690], ans[i + 691],
               ans[i + 692], ans[i + 693],
               ans[i + 694], ans[i + 695],
               ans[i + 696], ans[i + 697],
               ans[i + 698], ans[i + 699],
               ans[i + 700], ans[i + 701],
               ans[i + 702], ans[i + 703],
               ans[i + 704], ans[i + 705],
               ans[i + 706], ans[i + 707],
               ans[i + 708], ans[i + 709],
               ans[i + 710], ans[i + 711],
               ans[i + 712], ans[i + 713],
               ans[i + 714], ans[i + 715],
               ans[i + 716], ans[i + 717],
               ans[i + 718], ans[i + 719],
               ans[i + 720], ans[i + 721],
               ans[i + 722], ans[i + 723],
               ans[i + 724], ans[i + 725],
               ans[i + 726], ans[i + 727],
               ans[i + 728], ans[i + 729],
               ans[i + 730], ans[i + 731],
               ans[i + 732], ans[i + 733],
               ans[i + 734], ans[i + 735],
               ans[i + 736], ans[i + 737],
               ans[i + 738], ans[i + 739],
               ans[i + 740], ans[i + 741],
               ans[i + 742], ans[i + 743],
               ans[i + 744], ans[i + 745],
               ans[i + 746], ans[i + 747],
               ans[i + 748], ans[i + 749],
               ans[i + 750], ans[i + 751],
               ans[i + 752], ans[i + 753],
               ans[i + 754], ans[i + 755],
               ans[i + 756], ans[i + 757],
               ans[i + 758], ans[i + 759],
               ans[i + 760], ans[i + 761],
               ans[i + 762], ans[i + 763],
               ans[i + 764], ans[i + 765],
               ans[i + 766], ans[i + 767],
               ans[i + 768], ans[i + 769],
               ans[i + 770], ans[i + 771],
               ans[i + 772], ans[i + 773],
               ans[i + 774], ans[i + 775],
               ans[i + 776], ans[i + 777],
               ans[i + 778], ans[i + 779],
               ans[i + 780], ans[i + 781],
               ans[i + 782], ans[i + 783],
               ans[i + 784], ans[i + 785],
               ans[i + 786], ans[i + 787],
               ans[i + 788], ans[i + 789],
               ans[i + 790], ans[i + 791],
               ans[i + 792], ans[i + 793],
               ans[i + 794], ans[i + 795],
               ans[i + 796], ans[i + 797],
               ans[i + 798], ans[i + 799]);
    }
    for (; i + 20 < len_ans; i += 20)
    {
        printf("%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n%d %d\n",
               ans[i], ans[i + 1],
               ans[i + 2], ans[i + 3],
               ans[i + 4], ans[i + 5],
               ans[i + 6], ans[i + 7],
               ans[i + 8], ans[i + 9],
               ans[i + 10], ans[i + 11],
               ans[i + 12], ans[i + 13],
               ans[i + 14], ans[i + 15],
               ans[i + 16], ans[i + 17],
               ans[i + 18], ans[i + 19]);
    }
    for (; i < len_ans; i += 2)
    {
        printf("%d %d\n", ans[i], ans[i + 1]);
    }
    // double end = clock();
    // printf("%f\n", (end - begin) / CLOCKS_PER_SEC);
    // printf("%d", len_ans);
    return 0;
}
char c;
unsigned int readInt()
{
    unsigned int num = 0;
    // unsigned int flag = 0;
    c = getchar();
    while ((c < '0' || c > '9'))
    {
        // if (c == '-')
        //     flag = 1;
        c = getchar();
    }
    while (c > ('0' - 1) && c < ('9' + 1))
        num = num * 10 + (c - '0'), c = getchar();
    // if (flag == 0)
    return num;
    // else
    //     return num * (-1);
}

void push_back(Queue *q, const unsigned int len)
{
    for (unsigned int i = len; i--;)
    {
        Node *newNode = createNode(readInt());
        if (q->head == NULL)
            q->head = q->tail = newNode;
        else
        {
            q->tail->next = newNode;
            q->tail = newNode;
        }
    }
}

void pop_front(Queue *q)
{
    if (q->head != NULL)
        q->head = q->head->next;
}

Node *createNode(const unsigned int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

unsigned int queue_isEmpty(const Queue *q)
{
    if (q->head == NULL)
        return true;
    return false;
}

void push(Stack *stack, unsigned int value)
{
    stack->size++;
    stack->array[stack->size] = value;
}

void pop(Stack *stack)
{
    --stack->size;
}

unsigned int stack_isEmpty(const Stack *stack)
{
    return stack->size == -1;
}
unsigned int top(const Stack *stack)
{
    return stack->array[stack->size];
}