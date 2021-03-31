a, b = input().split(' ')
a, b = int(a), int(b)

seq = input().split(' ')

while True:
    try:
        cmd = input().split(' ')
        i, x = int(cmd[1]), int(cmd[2])
        cmd = cmd[0]
        seq.insert(i-1,x)
        # print(cmd)
        # for i in seq:
        #     print(i, end=' ')
        # print('')
    except EOFError as e:
        break


for i in seq:
    print(i, end=' ')