fs = [
    lambda x, y, z: (x or z) <= ((not x) == y),
    lambda x, y, z: ((z <= x) == (y and z)) <= (x and y),
    lambda x, y, z: (x or y or (not z)) == (y and z),
    lambda x, y, z: (y == x) == (z <= y),
    lambda x, y, z: (y <= x) == z
]
for f in fs:
    cnt = [0, 0]
    for x in range(2):
        for y in range(2):
            for z in range(2):
                if (not (x and z)) and y==z:
                    cnt[f(x, y, z)] += 1
    print(cnt)