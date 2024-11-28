from math import sqrt

m = int(input())
for n in range(38, 2, -1):
    for x in range(1, int(sqrt(sqrt(m))) + 1):
        if x != 1:
            del_ = x * pow(1 + x, n - 2)
            if m % del_ == 0:
                print(n)
                exit(0)
        if m % x == 0:
            l = 2
            r = int(int(10**18) ** (1 / (n - 1))) + 1
            while r - l > 1:
                mid = (l + r) // 2
                if mid * pow(1 + mid, n - 2) <= m // x:
                    l = mid
                else:
                    r = mid
            if l * pow(1 + l, n - 2) == m // x:
                print(n)
                exit(0)
print(2)
