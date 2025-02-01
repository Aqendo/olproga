def f(a, m):
    if a >= 88: return m%2==0
    if m == 0: return 0
    h = [f(a + 1, m - 1), f(a + 4, m - 1), f(a * 3, m - 1)]
    return any(h) if (m - 1) % 2 == 0 else all(h)
print([i for i in range(1, 88) if not f(i, 1) and f(i, 2)])
print([i for i in range(1, 88) if not f(i, 1) and f(i, 3)])
print([i for i in range(1, 88) if not f(i, 2) and f(i, 4)])