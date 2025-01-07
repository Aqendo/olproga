n, m, k = map(int, input().split())
A, B, C = map(int, input().split())
T = int(input())
oldm = m
superfast = [0] * (m + 1) 
for i in range(m):
    superfast[i] = int(input()) - 1
    if superfast[i] * B > T:
        m = i
        break
superfast[m] = n
answer = m - 1
remain = []
for i in range(1, m + 1):
    fro, to = superfast[i - 1], superfast[i]
    delta = to - fro - 1
    if delta <= 0: continue
    if fro * B + A*delta <= T:
        answer += delta
        continue
    mx = (T - fro * B) // A
    answer += mx
    from_dop, to_dop = fro + mx + 1, to - 1
    if from_dop > to_dop: continue
    timer = 0
    while from_dop <= to - 1:
        timer += 1
        if timer - 2 > k - oldm: break
        if fro * B + (from_dop - fro) * C > T:
            break
        if fro * B + (from_dop - fro) * C + (to_dop - from_dop) * A <= T:
            remain.append(to_dop - from_dop + 1)
            break
        mx = (T - fro * B - (from_dop - fro) * C) // A
        remain.append(mx + 1)
        from_dop += mx + 1
if len(remain) == 0:
    print(answer)
    exit(0)
remain.sort(reverse=True)
for i in range(0, min(len(remain), k - oldm)):
    answer += remain[i]
print(answer)