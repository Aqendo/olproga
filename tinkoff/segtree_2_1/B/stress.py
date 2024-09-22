from subprocess import Popen, PIPE
from random import randint as uid
import random

def gen_test() -> str:
	n = uid(1, 10)
	m = uid(1, 3)
	s = f"{n} {m}\n"
	for i in range(m):
		move = uid(1, 3)
		s += f"{move} "
		if move == 1:
			l = uid(0, n - 1)
			r = uid(l + 1, n)
			v = uid(0, 10)
			s += f"{l} {r} {v}\n"
		elif move == 2:
			l = uid(0, n - 1)
			r = uid(l + 1, n)
			v = uid(0, 10)
			s += f"{l} {r} {v}\n"
		elif move == 3:
			l = uid(0, n - 1)
			r = uid(l + 1, n)
			s += f"{l} {r}\n"
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
		print("\n\n====TEST====\n", test, "\n====ENDTEST====\n\n",sep="")
		print("Old:", old)
		print("Main:", main)
		break