cnt = 0
for i in range(100_000_000):
    s = f"{i:0>8}"
    if s.count('6') == 2 and s.count('0') == 1 and s.count('2') == 1 and s.count('5') == 1 and sum(int(x) for x in s) % 5 == 0:
        cnt += 1
print(cnt)