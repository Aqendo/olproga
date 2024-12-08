import sys

sys.set_int_max_str_digits(1000000)

n = int(input())
if (n % 2 == 1):
 print(0)
 exit(0)
print(2**(n//2))
