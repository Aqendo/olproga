from subprocess import Popen, PIPE
from random import randint as uid
def gen_test():
	n = uid(1000000, 1000000)
	a = [0] * n
	for i in range(n):
		a[i] = uid(1, 1000000000)
	return str(n) + "\n" + ' '.join([str(i) for i in a])
i = 0
while True:
	test = gen_test()
	print(i)
	i += 1
	p = Popen(["./main"], stdin=PIPE, stdout=PIPE)
	stdout, _ = p.communicate(test.encode())
	main=int(stdout.decode())

	p = Popen(["./old"], stdin=PIPE, stdout=PIPE)
	stdout, _ = p.communicate(test.encode())
	old=int(stdout.decode())
	if old != main:
		print("Old:", old)
		print("Main:", main)
		break