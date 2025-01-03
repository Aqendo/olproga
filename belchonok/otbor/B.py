cntmax = -1230
val = 0
for a in range(11,-1,-1):
    for b in range(11,-1,-1):
        for c in range(11,-1,-1):
            for d in range(11,-1,-1):
                for e in range(11,-1,-1):
                    s = [e, d, c, 9, b, a, 6]
                    if len(set(s)) == len(s):
                        answer = 0
                        for i in range(len(s)):
                            answer += s[i] * 12**i
                        cnttwo = 0
                        while answer > 0 and answer % 2 == 0:
                            answer //= 2
                            cnttwo += 1
                        if cnttwo > cntmax:
                            val = s
                            cntmax = cnttwo
print(val, cntmax)