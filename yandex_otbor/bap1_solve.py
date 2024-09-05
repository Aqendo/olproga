a, b = map(int, input().split())
MOD = 998244353
def is_prime(n):
	i = 2
	if n == 2: return True
	elif n < 2: return False
	while i * i <= n:
		if n % i == 0: return False
		i += 1
	return True



prime_divs = []
i = 2
a_now = a
while i * i <= a_now:
	if a % i == 0:
		prime_divs.append(i)
		while a % i == 0:
			a //= i
	i += 1
if is_prime(a):
	prime_divs.append(a)

a = a_now



cnt_primes = [0] * len(prime_divs)
for i in range(len(prime_divs)):
	a_now = a
	while a_now % prime_divs[i] == 0:
		cnt_primes[i] += 1
		a_now /= prime_divs[i]

d_a_b = 1
d_a = 1
for i in cnt_primes:
	d_a_b *= i * b + 1
	d_a *= i + 1
print((b * d_a_b // 2) % MOD)