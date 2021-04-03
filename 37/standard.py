a, b = input().split(' ')
a, b = int(a), int(b)

seq = input().split(' ')

while True:
    try:
        cmd = input().split(' ')
        # cmd = cmd[0]
        if cmd[0] == 'Insert':
            i, x = int(cmd[1]), int(cmd[2])
            seq.insert(i-1,x)
        elif cmd[0] == 'Reverse':
            l, r = int(cmd[1]), int(cmd[2])
            seq[l-1:r] = seq[l-1:r][::-1]
        elif cmd[0] == 'Delete':
            i = int(cmd[1])
            del seq[i-1]
        # for i in seq:
        #     print(i, end=' ')
        # print('')
    except EOFError as e:
        break

for i in seq:
    print(i, end=' ')