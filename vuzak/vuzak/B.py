import sys

input = sys.stdin.readline
t = int(input())


def get(n):
    return (2 + k * (n - 1)) * n // 2


for _ in range(t):
    s, k = map(int, input().split())
    l, r = 1, 2 * s
    while r - l > 1:
        m = (l + r) // 2
        if get(m) <= s:
            l = m
        else:
            r = m
    print(l)
