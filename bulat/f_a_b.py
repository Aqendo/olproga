NEEDED = 2_097_152

def F(a, b):
	if b == 0: return 0
	ans = 0
	while a != 0 and b != 0 and a != b:
		if a > b:
			ans += (a - b) * b;
			a = b
		else:
			ans += (b - a + 1) * a
			b = a - 1
	if a == 0 or b == 0: return ans
	return ans + a * a

cnt = 0

for i in range(NEEDED + 1):
	l, r = 1, NEEDED
	while r - l > 1:
		m = (l + r) // 2
		if F(i, m) <= NEEDED:
			l = m
		else:
			r = m
	cnt += (F(i, l) == NEEDED)
	cnt += (F(i, l - 1) == NEEDED)
	cnt += (F(i, l + 1) == NEEDED)

print(cnt)