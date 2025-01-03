for y in range(2007, 1000000000):
    x = (27 ** y + 9**9 -1) * (81 ** y) - 3 + 3 **y
    print(x)
    cnt = [0, 0, 0]
    while x > 0:
        cnt[x % 3] += 1
        x //= 3
    if cnt[2] == 2024:
        print(y)
        exit(0)