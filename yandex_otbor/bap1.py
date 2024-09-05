dels_ = []
import sys
def f(a, b):
	global dels_
	number = a ** b
	dels = []
	for i in range(1, number + 1):
		if number % i == 0:
			dels.append(i)
	now = 1
	for i in dels:
		now *= i
	least = 0
	power = 1
	for i in range(1, 1000000):
		if now >= power * a:
			least = i
			power *= a
		else:
			break
	if len(dels_) != 0:
		print(least - dels_[-1], end=' ')
		sys.stdout.flush()
	dels_.append(least)

try:
	for number in (6,):
		dels = 0
		for i in (3,):
			if number % i == 0: dels += 1
		print(f"{dels} dels: ", end='')
		dels_ = []
		for i in range(1, 8):
			f(number, i)
		print()
		print(dels_)
except KeyboardInterrupt:
	exit(0)