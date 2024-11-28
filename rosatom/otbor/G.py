n, x = map(int, input().split())
a = list(zip(list(map(int, input().split())), list(map(int, input().split()))))
b = list(zip(list(map(int, input().split())), list(map(int, input().split()))))
c = list(zip(list(map(int, input().split())), list(map(int, input().split()))))
answer = 100000000000000000
for i in range(n):
    for j in range(n):
        for k in range(n):
            if a[i][1] + b[j][1] + c[k][1] <= x:
                answer = min(
                    answer,
                    max(a[i][0], b[j][0], c[k][0]) - min(a[i][0], b[j][0], c[k][0]),
                )
if answer == 100000000000000000:
    print(-1)
else:
    print(answer)
