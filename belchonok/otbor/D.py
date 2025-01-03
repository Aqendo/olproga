am = 18 * 2560 * 1536 / 8 / 1024 
diff = 6 * 1024
for i in range(1, 1000000):
    cnt1 = (am + 16) // 17 * 17 * i
    cnt2 = (am + 68) // 69 * 69 * i
    if abs(cnt1 - cnt2) > diff:
        print(i)
        break