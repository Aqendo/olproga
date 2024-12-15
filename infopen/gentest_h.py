from subprocess import Popen, PIPE
from random import randint as uid
def gen_test():
    n = 500000
    q = 500000
    print(n, q)
    a = [uid(1, n) for i in range(n)]
    print(*a)
    p = [0] * n
    p[0] = -1
    for i in range(1, n):
        p[i] = uid(0, i - 1)
    print(*p)
    moves = [0] * q
    for i in range(q):
        moves[i] = [0, 0, 0]
        moves[i][0] = uid(1, 2)
        moves[i][1] = uid(0, n)
        moves[i][2] = uid(0, n)
        while moves[i][2] == moves[i][1]:
            moves[i][2] = uid(1, n)
        print(*moves[i])
gen_test()

