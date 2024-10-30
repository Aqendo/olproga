from subprocess import Popen, PIPE
from random import randint as uid
def gen_test():
	n = uid(1, 3)
	m = uid(1, 3)
	k = uid(1, 3)
	grid = [[0]*m for i in range(n)]
	for i in range(n):
		for j in range(m):
			grid[i][j] = uid(1, 4)
	queries = [0] * k
	for i in range(k):
		queries[i] = uid(1, 4)
	return (n,m,k,grid,queries)

def get_str(n,m,k,grid,queries):
	s = ""
	s += str(n) + " "
	s += str(m) + "\n"
	for i in range(n):
		for j in range(m):
			s += str(grid[i][j]) + " "
		s += "\n"
	s += str(k) + "\n"
	for i in queries:
		s += str(i) + "\n"
	return s



i = 0
while True:
	test = gen_test()
	test = get_str(*test)
	i += 1
	p = Popen(["./main"], stdin=PIPE, stdout=PIPE)
	stdout, _ = p.communicate(test.encode())
	p = Popen(["python3", "anton.py"], stdin=PIPE, stdout=PIPE)
	stdout1, _ = p.communicate(test.encode())
	if stdout.decode().strip() != stdout1.decode().strip():
		print(test)
		print(stdout)
		print(stdout1)
		break