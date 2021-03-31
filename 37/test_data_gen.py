import random
def generate(n):
    i = random.randint(1, n)
    x = random.randint(-1000,1000)
    return 'Insert ' + str(i) + ' ' + str(x) + '\n'

n = 10
q = 10
seq = [str(random.randrange(-100, 100)) for i in range(n)]
# with open('test.in', 'w', encoding='utf-8') as f:
print("{} {}".format(n,q))
print(' '.join(seq)+'')
for i in range(q):
    print(generate(n),end='')