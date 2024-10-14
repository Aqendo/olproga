from subprocess import Popen, PIPE
from typing import List, Tuple
import random
import math

class Test:
	q: int
	n: int
	queries: List[Tuple[int, int]]
	def __init__(self, q, n, queries):
		self.q = q 
		self.n = n
		self.queries = queries
	def __str__(self) -> str:
		string = f"{self.q} {self.n}\n"
		for (x, k) in self.queries:
			string += f"{x} {k}\n"
		return string


def gen_test():
	q = random.randint(1, 10)
	n = random.randint(1, 1000000)
	queries = []
	for i in range(q):
		queries.append((random.randint(1, 100000), random.randint(1, 20)))
	return Test(q, n, queries)

MOD = int(1e9) + 7

def solve_slow(test: Test) -> List[int]:
	ans = []
	n = test.n
	for (x, k) in test.queries:
		coeff = 10 ** int(math.floor(math.log10(x)) + 1)
		for i in range(k):
			n *= coeff
			n += x
		ans.append(n % MOD)
	return ans

while True:
	test = gen_test()
	res_fast = Popen(["./fast"], stdin=PIPE, stdout=PIPE)
	stdout, stderr = res_fast.communicate(str(test).encode())
	res_fast = stdout.decode().strip().split('\n')
	res_fast = [int(i) for i in res_fast]
	res_slow = solve_slow(test)
	if res_fast != res_slow:
		print(test)
		print(res_fast)
		print(res_slow)
