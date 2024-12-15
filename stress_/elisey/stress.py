from subprocess import Popen, PIPE
from random import randint as uid


def gen_test():
    n, m = 100000, 300000
    test = f"{n} {m}\n"
    for i in range(m):
        test += f"{uid(0, n - 1)} {uid(0,1)} {uid(0, n - 1)} {uid(0,1)}\n"
    print(test)
    return test


i = 0
while True:
    test = gen_test()
    break
    p = Popen(["./norm"], stdin=PIPE, stdout=PIPE)
    stdout, _ = p.communicate(test.encode())
    main = stdout.decode().strip()

    p = Popen(["./elis"], stdin=PIPE, stdout=PIPE)
    stdout, _ = p.communicate(test.encode())
    old = stdout.decode().strip()
    if old != main:
        print(test)
        print("Old:", old, "\n")
        print("Main:", main)
        break
