С = 73


def f(n, step=73):
    a = []
    while n >= step:
        a.append(str(n % step))
        n //= step
    if n != 0:
        a.append(str(n))
    a.reverse()
    return a


mod = 1000000000
ans = -10000000000000
for i in range(2, 3):
    lo = {}
    n = i
    f_v = "_".join(f(n)[-3:])
    cnt = 0
    while f_v not in lo:
        n *= i
        cnt += 1
        lo[f_v] = cnt
        f_v = "_".join(f(n)[-3:])
        print(f_v)
    ans = max(ans, cnt - lo[f_v])
print(ans)
