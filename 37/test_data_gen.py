import random as rd
from random import randint


def generate(mode):
    global numofseq
    if numofseq == 1:
        mode = randint(1,2)
    if mode == 1:
        l = rd.randint(1, numofseq-1)
        r = rd.randint(l+1, numofseq)
        return "Reverse {} {}\n".format(l,r)
    if mode == 2:
        i = rd.randint(1, numofseq+1)
        x = rd.randint(-1000,1000)
        numofseq += 1
        return 'Insert ' + str(i) + ' ' + str(x) + '\n'
    if mode == 3:
        i = randint(1,numofseq);
        numofseq -= 1
        return "Delete {}\n".format(i)
n = 20000
q = 20000
numofseq = n

# seq = [str(rd.randrange(-100, 100)) for i in range(n)]
seq = [str(i) for i in range(1, 1+n)]
# with open('test.in', 'w', encoding='utf-8') as f:
print("{} {}".format(n,q))
print(' '.join(seq)+'')
for i in range(q):
    # print(numofseq)
    print(generate(randint(1,2)),end='')