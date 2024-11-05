import sys
sys.set_int_max_str_digits(1000000000)
precalc_power = [1] * 500002
for i in range(1, 500002):
    precalc_power[i] = precalc_power[i - 1] * 10
print("good")
def square(number, amount_of_digits=1000):
    s = 1
    approximate = 0
    for i in range(amount_of_digits):
        for z in range(1,number*10):
            apr10 = approximate*10
            if (apr10+z)**3 > number * precalc_power[(s-1)*3]:
                approximate = apr10 + z-1
                s += 1
                break
    return approximate
n, k = int(input()), int(input()) + 1
print(n ** (1/3))
print(square(n, k))