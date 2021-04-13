# 2021 SPRING DSA HW1
#### Problem 1
1.假設while loop 總共會跑k次，$1+2+3+...+k =\frac{k(1+k)}{2} < n$，$\frac{(k+1)(1+(k+1))}{2} > n$; 得到$k^2 + k < 2n$， $(k+1)^2 + (k+1) > 2n$, 所以是$\Theta(\sqrt{n})$

2.$\Theta$(loglogn) ![](https://i.imgur.com/sU9ogmy.png)

3.將函數遞迴展開可以知道是$\Theta(4^n)$，如附圖 ![](https://i.imgur.com/p3bxsFt.png)




4.**(Prove or disprove)** $f(n)+g(n) = Θ( max(f(n), g(n)) )$\
Sol:\
According to the given definition of the  Θ notation,$f(n)+g(n) = Θ( max(f(n), g(n)) )$ if and only if $f(n)+g(n) = O( max(f(n), g(n)) )$ 
and 
$f(n)+g(n) = \Omega( max(f(n), g(n)) )$. 
* Since $|f(n)+g(n)|$ $\leqslant$ c$_1$ $*max(f(n), g(n))$ when taking c$_1$ = 2 $\forall n > 1$, we know that $f(n)+g(n) = O( max(f(n), g(n)) )$; 
* And since $|f(n)+g(n)|\geqslant$ c$_2$ $* max(f(n), g(n))$ 
when taking c$_2$ = 1 $\forall n > 1$,
we know that $f(n)+g(n) = \Omega( max(f(n), g(n)) )$.
* Hence, we have proved that $f(n)+g(n) = Θ( max(f(n), g(n)) )$

5.(Prove or disprove) If $f(n) = O (i(n))$ and $g(n) = O(j(n))$, then $f(n) · g(n) = O(i(n) · j(n))$.\
Sol:
* If $f(n) = O(i(n))$, there exists positive numbers c$_1$ and x$_1$ s.t. $|f(x)|$ $\leqslant$ c$_1$ $·i(n),  \forall x > x$$_1$ .
* If $g(n) = O(j(n))$, there exists positive numbers c$_2$ and x$_2$ s.t. $|g(x)|$ $\leqslant$ c$_2$ $·j(n),  \forall x > x$$_2$ .
* Then $|f(x)·g(x)| \leqslant |f(x)|·|g(x)| \leqslant c_1·i(n)·c_2·j(n) = c_3·i(n)·j(n)$ where $c_3 = c_1·c_2 , \forall x \geqslant max(x_1, x_2)$ ，and $f(n) · g(n) = O(i(n) · j(n))$. Q.E.D

6.(Prove or disprove) If $f(n) = O ( g(n) )$ , then $2^{f(n)} = O ( 2^{g(n)} )$.\
Sol:\
Consider the case that $f(n) = 2lgn, g(n) = lgn,$\
we konw that $f(n) = O(g(n));$ however\
$2^{f(n)} = 2^{2lgn} = 2^{lg(n^{2})} = n^{2}$\
$2^{g(n)} = 2^{lgn} = n$ \
$2^{f(n)} \neq O ( 2^{g(n)} )$\
Obivously, the statement is not true.



7.![](https://i.imgur.com/KW7d6en.png)


8.(Prove or disprove) lg(n!) = Θ(nlgn)\
![](https://i.imgur.com/AFAaHZN.png)

9.$\Theta(n(lgn)^{2})$![](https://i.imgur.com/Vj8xhVw.png)




---
#### Problem 2
1. 
```
REVERSE(Q1, Q2)
    // Q1 is the source queue
    // Q2 is the helper queue
    while Q1.size > 0
        for i = 1 to Q1.size-1
            temp = Q1.front()
            Q1.dequeue()
            Q1.enqueue(temp)
        temp = Q1.front()
        Q1.dequeue()
        Q2.enqueue(temp)
    while Q2.size > 0 
        temp = Q2.front()
        Q1.enqueue(temp)
        Q2.dequeue()
```

2. Prove that your algorithm in the previous subproblem runs in O($n^2$)-time.
Sol:
分析第一個while loop：
每一次while loop中的for loop都會不停地把Q1最前端的元素取出並放入尾端，for loop會執行(Q1.size-1)次，加上Q2 enqueue的1次操作，總共為Q1.size次操作；然後每次while loop都會讓Q1.size減少1，所以while loop總共會執行(Q1.size)次。若一開始Q1總共有n個element，則，總操作數為 $n+(n-1)+(n-2)+...+1 = \frac{n(1+n)}{2}$ 次，複雜度為O($n^2$)。  

    分析第二個while loop:
把Q2所有的elements放入Q1,while loop總共會執行n次，複雜度為O(n)
所以演算法複雜度為O($n^2$)




3. (10 pts) Illustrate your design, in particular, how you achieve each of the four operations below (preferably with figures).  
Sol:

```
stack left, right;
void push_front(int x)
    push x into left
void push_back(int x)
    push x into right
    
int pop_front():
    if left is empty
        while right is not empty
            push the top element of right into left
            remove the top of right
    front = the top of left
    remove the top of left
    return front
    
int pop_back():
    if right is empty
        while left is not empty
            push the top element of left into right
            remove the top of left
    back = the top of right
    remove the top of right
    return back
```
Time complexity analysis:  
4. O(1) &emsp; 5.O(1)  
6. In the worse case, the while loop would repeat n times (n is the number of elements in right stack);hence O(n).   
7. O(n) for the same reason above\
8.![](https://i.imgur.com/5q0oecI.png)
#### Problem 3
1. Given the initial position of the frog, design an algorithm that computes whether the frog will stop somewhere or keep jumping forever.  
```
WHETHER_STOP(A,init)
    Let B be an array with n initial zero values
    i = init
    steps = 0
    while True
        if A[i] == i
            the frog will stop at the i-th position 
            end while
        else if B[i] == 1 or steps == n
            the frog will keep jumping forever
            end while
        else 
            B[i] = 1
            i = A[i]
            steps = steps + 1
```
##### Prove correctness:  
If A[i] == i, the frog will stop (trivial);\
and if the frog jumps into the position at which have been arrived, we know that the path is a cycle, and it would then go through the same path forever.\
If the forg has already reached n different positions, the next position it would move to must be the one that it has reached before, so it would keep jumping forever.
##### Analysis:
The length of array B is n, and the while loop repeats up top n times. Time complexity is O(n), and extra-space complexity is also O(n).

2. 

```
COUNT-LOOP-LENGTH(A,init)
    Let B be an array with n initial zero values
    i = init
    steps = 0
    while True
        if B[i] == 1 or steps == n
            return  n
        else 
            B[i] = 1
            i = A[i]
            steps = steps + 1
```
##### Prove correctness:
If the frog jumps into the position at which have been arrived, the number of steps it takes is just the length of the cycle.
##### Analysis:
The length of array B is n, and the while loop repeats up top n times. Time complexity is O(n), and extra-space complexity is also O(n).


3.(15 pts) A is a strictly increasing array with n integers, where A = $[a_0, a_1, · · · , a_{n-2}, a{n−1]},
n ≥ 3$. Now, consider the following definitions.
* As,t = $[a_s, a_{s+1}, · · · , a_{t−2}, a_{t−1}],$ where $0 ≤ s < t ≤ n$
* Ms,t = the median of As,t
* f(i, j) = max(M0,i, Mi,j , Mj,n) − min(M0,i, Mi,j , Mj,n), where 0 < i < j < n\
In short, A is partitioned into three subarrays by index i and index j. Each subarray has
its own median. f(i, j) equals to ”the maximum of three medians” minus ”the minimum
of three medians”.
Design an algorithm to find a pair (i, j), where 0 < i < j < n, such that f(i, j) is
minimized.
Finally, let’s play with a new kind of linked list.\
Sol:
```
FIND-PAIR(A, n)  //A is a strictly increasing array with n integers
    i = 1
    min = ∞
    min_i = 0
    min_j = 0
    while i+1 < n
        j = i+1
        temp = f(i, j)
        if temp < min
                min = temp
                min_i = i
                min_j = j
        i += 1
    return min_i, min_j
```
##### Prove correctness:
整個陣列被分為三個區間，如要最小化f(i, j)，那就要最小化max(M0,i, Mi,j , Mj,n)和最大化min(M0,i, Mi,j , Mj,n)，無論如何，M0,i $\leqslant$ Mi,j $\leqslant$  Mj,n 恆成立。所以問題就轉化為最小化Mj,n和最大化M0,i。j越小，Mj,n會越小；i越大，M0,i就越大，所以要最小化f(i, j)，i和j必然是相鄰的兩個整數，因此找出i,j相鄰的所有組合就能得到最佳解。

##### Analysis:
f(i, j) takes constant time(finding the median in six intervals respectly and then doing the comparsions and subtractions have nothing to do with the number of integers).\
The while loop repeats for n-1 times, so the time complexity is $O(n)$; and the extra-space complexity is $O(1)$.

4.(15 pts) \
A **circularly linked list** is a linked list such that the last node of the linked list is
connected to the **head** instead of some nil (NULL) value. We call a node A **decreasing** in
the circularly linked list if A.next.value < A.value.\
Consider a circularly linked list L with n integers, represented by some head node. Assume
that there are **two decreasing nodes** within L. Design an algorithm that “sorts” all nodes
within L such that head points to a new circularly linked list with only one decreasing
node. We expect the algorithm to run in O(n)-time and O(1)-extra-space .\
Sol:

```
SORT(L)
    1. Traverse the L to find the 1-st and the 2-nd decreasing node,
       n1 and n2
    2. Take n1.next as the head and n2 as the tail of a new singly 
       linked list l1, and take n2.next as the head and n1 as the tail of 
       another singly linked list l2 
    3. Compare l1.head and l2.head, remove the larger one and set it as 
       the head of the new singly linked list l3
    4. Compare l1.head and l2.head, remove the larger one and set it as 
       l3.tail
    5. Repeat step 4 unitl one list is empty, and then concate l3.tail 
       to the head of the remained list
    6. Set l3.head as l3.tail.next 
```
##### Prove correctness:
只有兩個decreasing node的 circularly linked list可以視為兩段升序排列的 singly linked list 頭尾相接，因此把他們拆開後再合併成一個升序的 list 再頭尾相接就會得到一個只有一個decreasing node的 circularly linked list

##### Analysis:
找到兩個decreasing node 的worst case是遍歷所有node\
需要O(n)的時間\
將它們合併的worst case也需要O(n)的時間\
因此時間複雜度為 O(n)\
以上操作只需要既存的node進行遍歷和比較大小\
額外空間複雜度為O(1)