q = int(input())

def get(r):
    return 45 * (r // 9) + (r % 9) * (r % 9 + 1) // 2

for i in range(q):
    a, b = map(int, input().split())
    print(get(b) - get(a - 1))