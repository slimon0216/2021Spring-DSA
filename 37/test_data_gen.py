import random as rd
from random import randint


def generate(mode):
    global num_of_seq
    if mode == 1:
        l = rd.randint(1, num_of_seq)
        r = rd.randint(l, num_of_seq)
        return "Reverse {} {}\n".format(l,r)
    if mode == 2:
        i = rd.randint(1, num_of_seq+1)
        x = rd.randint(-10**5,10**5)
        num_of_seq += 1
        return 'Insert ' + str(i) + ' ' + str(x) + '\n'
    if mode == 3:
        i = randint(1,num_of_seq);
        num_of_seq -= 1
        return "Delete {}\n".format(i)
    if mode == 4:
        l = rd.randint(1, num_of_seq)
        r = rd.randint(l, num_of_seq)
        k = randint(1, r-l+1)
        return "Query {} {} {}\n".format(l,r, k)
  
n = 10000
q = 10000
num_of_seq = n

seq = [str(rd.randrange(-10**5, 10**5)) for i in range(n)]
# seq = [str(i) for i in range(1, 1+n)]
# with open('test.in', 'w', encoding='utf-8') as f:
print("{} {}".format(n,q))
print(' '.join(seq)+'')
for i in range(q):
    # print(num_of_seq)
    print(generate(randint(1,4)),end='')
