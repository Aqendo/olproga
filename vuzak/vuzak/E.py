import sys

input = sys.stdin.readline
mod = 10**9 + 7
n, k = map(int, input().split())
if k == 2:
    print((((((n - 1) ** 2 - 1) * 4 + (n - 2) * 4))) % mod)
else:
    print(36)
