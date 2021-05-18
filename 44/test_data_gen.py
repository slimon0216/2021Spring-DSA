import random as rd
from itertools import permutations 

T = 1
num_of_packages = 7
num_of_merges = 0
num_of_lines = 5
num_of_operations = num_of_packages + num_of_merges
permutation = list(permutations(list(range(1, num_of_packages+1))))

target_line = list(permutation[rd.randint(0, len(permutation)) ]) 
push = list(permutation[rd.randint(0, len(permutation)) ]) 


print(T)
print(num_of_packages, num_of_operations, num_of_lines)
for p in push:
    print("push", p, rd.randint(0, num_of_lines-1))
print( ' '.join(map(lambda x: str(x),target_line) ) )
