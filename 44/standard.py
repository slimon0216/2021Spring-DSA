T = int(input())


for t in range(T):
    operations = []
    target_line = []
    prod_lines = []
    num_of_packages, num_of_operations, num_of_lines = map(lambda x: int(x), input().split())
    for i in range(num_of_lines):
        prod_lines.append([])
    for i in range(num_of_operations):
        operations.append(input().split())
    # print(operations[0])
    target_line = list(map(lambda x: int(x), input().split()))
    impossible = False
    tar_index = 0
    op_index = 0
    for op_index in range(num_of_operations+1):
        while True:
            # for i, j in enumerate(prod_lines):
            #     print(i, j)
            if tar_index >= num_of_packages:
                break
            target = target_line[tar_index]
            # print("target " ,target)
            find = False
            for line in prod_lines:
                if len(line) > 0:
                    if line[0] == target:
                        line.pop(0)
                        find = True
                        break
                    elif line[-1] == target:
                        line.pop(-1)
                        find = True
                        break
                    elif max(line) == target:
                        line.remove(max(line))
                        find = True
                        break
                    elif target in line:
                        impossible = True
                        break
                    else:  # 還沒進來
                        pass 
            if find == True:
                tar_index += 1
            else:
                break
        if impossible == True:
            break
        if op_index >= num_of_operations:
            break
        # print(operations[op_index])

        if operations[op_index][0] == 'push':
            prod_lines[int(operations[op_index][2])].append(int(operations[op_index][1]))
        elif operations[op_index][0] == 'merge':
            prod_lines[int(operations[op_index][2])] += prod_lines[int(operations[op_index][1])]
            prod_lines[int(operations[op_index][1])] = []
            
        

    


    if impossible == True:
        print('impossoble')
    else:
        print('possible')