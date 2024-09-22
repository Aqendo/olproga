from subprocess import Popen, PIPE
from random import randint as uid
def gen_test():
	n = 9
	s = f"{n}\n"
	for i in range(n):
		x1, y1 = uid(-20, 20), uid(-20, 20)
		x2, y2 = uid(x1, 40), uid(y1, 40)
		s += f"{x1} {y1} {x2} {y2}\n"
	return s
i = 0
while True:
	test = gen_test()
	print(i)
	i += 1
	p = Popen(["./main"], stdin=PIPE, stdout=PIPE)
	stdout, _ = p.communicate(test.encode())
	try:
		main=int(stdout.decode())
	except:
		print("test:::\n\n",test,sep="")
		exit(0)

	p = Popen(["./old"], stdin=PIPE, stdout=PIPE)
	stdout, _ = p.communicate(test.encode())
	old=int(stdout.decode())
	if old != main:
		print(test)
		print("Old:", old)
		print("Main:", main)
		break