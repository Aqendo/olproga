import sys

input = sys.stdin.readline


def chartoint(s):
    if len(s) == 1:
        if ord("A") <= ord(s) <= ord("Z"):
            return ord(s) - ord("A")
        return 26 + ord(s) - ord("a")
    if s[1] == "^":
        if ord("A") <= ord(s[0]) <= ord("Z"):
            return 52 + ord(s[0]) - ord("A")
        return 52 + 26 + ord(s[0]) - ord("a")
    elif s[1] == "~":
        if ord("A") <= ord(s[0]) <= ord("Z"):
            return 104 + ord(s[0]) - ord("A")
        return 104 + 26 + ord(s[0]) - ord("a")
    elif s[1] == "_":
        if ord("A") <= ord(s[0]) <= ord("Z"):
            return 156 + ord(s[0]) - ord("A")
        return 156 + 26 + ord(s[0]) - ord("a")
    else:
        assert False, "Unreachable"


powers = [0] * 60
powers[0] = 1
for i in range(1, 60):
    powers[i] = powers[i - 1] * 52


def toint(s):
    a = []
    for i in s:
        if ord("a") <= ord(i) <= ord("z") or ord("A") <= ord(i) <= ord("Z"):
            a.append(i)
        else:
            a[-1] += i
    a.reverse()
    answer = 0
    for i in range(len(a)):
        answer += powers[i] * chartoint(a[i])
    return answer


n = toint(input().strip())
k = int(input())
arr = list(map(toint, input().strip().split(" ")))
for i in range(k - 1, -1, -1):
    if arr[i] == n:
        print(i + 1)
        exit(0)
print(0)
