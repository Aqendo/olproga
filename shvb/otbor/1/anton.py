def dpoch(a):
    tmp = []
    for i in range(len(a[0])):
        temp = []
        for j in range(len(a)):
            temp.append(a[j][i])
        tmp.append(temp[::-1])
    return tmp

def dprch(a):
    tmp = []
    for i in range(len(a[0])):
        temp = []
        for j in range(len(a)):
            temp.append(a[j][i])
        tmp.append(temp)
    return tmp[::-1]

def mirrbyhor(a):
    for i in range(len(a)):
        a[i] = a[i][::-1]
    return a

def mirrbyvert(a):
    return a[::-1]

n, m = map(int, input().split())
a = []
for i in range(n):
    a.append(list(map(int, input().split())))

ww = int(input())
rt = [int(input()) for i in range(ww)]
for i in range(ww):
    if rt[i] == 1:
        a = dpoch(a)
    elif rt[i] == 2:
        a = dprch(a)
    elif rt[i] == 4:
        a = mirrbyhor(a)
    elif rt[i] == 3:
        a = mirrbyvert(a)

ans1 = 0
ans2 = 0
for i in range(len(a)):
    ans1 += a[i][0]
    ans2 += a[i][-1]
print(ans1, ans2)
