import random
n = random.randint(1, 10)
a = [0] * n
for i in range(n):
	a[i] = random.randint(1, 123123123)
q = random.randint(1, 10)
print(n)
print(*a)
print(q)
for i in range(q):
	print(random.randint(1, n), random.randint(1, 100))