for a in range(1, 9):
    for b in range(9):
        for c in range(9):
            for d in range(9):
                for e in range(9):
                    for f in range(9):
                        s = f"{a}{b}{c}{d}{e}{f}"
                        s2 = f"{f}{e}{d}{c}{b}{a}"
                        des = int(s, 9)
                        des2 = int(s2, 9)
                        if des * 8 == des2:
                            print(s, s2)
                            exit(0)
                        

