import random
n = 300
a = [x + 1 for x in range(n)]
random.shuffle(a)
b = [x + 1 for x in range(n)]
random.shuffle(b)
print(n)
aa = 123
s = ""
for i in range(n):
    for j in range(n):
        aa = ((aa * 123 + 123) ^ 432530) % 32948111
        if aa % 2 == 0:
            s += f"{b[j]} "
        else:
            s += f"{a[i]} "
    s += '\n'
print(s)
