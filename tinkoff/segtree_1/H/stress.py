from subprocess import Popen, PIPE
from random import randint as uid
import random

def gen_test() -> str:
	n = uid(1, 10)
	m = uid(1, 3)
	s = f"{n} {m}\n"
	for i in range(m):
		move = random.choice(['R', 'C', '?'])
		if move == '?':
			l = uid(1, n)
			r = uid(l, n)
			s += f"{move} {l} {r}\n"
		elif move == 'R':
			i = uid(1, n)
			q = uid(0, 100)
			s += f"{move} {i} {q}\n"
		else:
			l = uid(1, n)
			r = uid(l, n)
			x = uid(0, 100)
			s += f"{move} {l} {r} {x}\n"
	return s

i = 0
print(gen_test())
print("=====")
while True:
	test = gen_test()
	print(i)
	i += 1
	p = Popen(["./main"], stdin=PIPE, stdout=PIPE)
	stdout, _ = p.communicate(test.encode())
	main=stdout.decode().strip()

	p = Popen(["./old"], stdin=PIPE, stdout=PIPE)
	stdout, _ = p.communicate(test.encode())
	old=stdout.decode().strip()
	if old != main:
		print("\n\n", test, "\n\n")
		print("Old:", old)
		print("Main:", main)
		break