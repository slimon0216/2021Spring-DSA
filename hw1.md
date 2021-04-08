### 2021 SPRING DSA HW1
#### Problem 1
1.假設while loop 總共會跑k次，$1+2+3+...+k =\frac{k(1+k)}{2} < n$，$\frac{(k+1)(1+(k+1))}{2} > n$;\
得到$k^2 + k < 2n$， $(k+1)^2 + (k+1) > 2n$ \
所以是$\Theta(\sqrt{n})$

2.$\Theta$(loglogn) ![](https://i.imgur.com/sU9ogmy.png)

3.$O(4^n)$ ![](https://i.imgur.com/5gHSyBS.png)


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
Sol:\
* If $f(n) = O(i(n))$, there exist positive numbers c$_1$ and x$_1$ s.t. $|f(x)|$ $\leqslant$ c$_1$ $·i(n),  \forall x > x$$_1$ .
* If $f(n) = Ω(i(n))$, there exist positive numbers c$_2$ and x$_2$ s.t. $|f(x)| \geqslant c$_2$·i(n), \forall x > x$$_2$ .

6.還沒寫\
7.![sdfsdf](https://i.imgur.com/d66zdRj.png)

8.(Prove or disprove) lg(n!) = Θ(nlgn)![](https://i.imgur.com/H94noNz.png)
9.![](https://i.imgur.com/zeLsJVA.png)


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
每一次while loop中的for loop都會不停地把Q1最前端的元素取出並放入尾端，for loop會執行(Q1.size-1)次，加上Q2 enqueue的1次操作，總共為Q1.size次操作；然後每次while loop都會讓Q1.size減少1，所以while loop總共會執行(Q1.size)次。若一開始Q1總共有n個element，則，總操作數為 n+(n-1)+(n-2)+...+1 = $\frac{n(1+n)}{2}$ 次，複雜度為O($n^2$)。  

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
7. O(n) for the same reason as above\
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

