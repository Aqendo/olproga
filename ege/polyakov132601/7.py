def f(a, b, m):
    if a + b >= 69: return m%2==0
    if m == 0: return 0
    h = [f(a + 1, b, m - 1), f(a * 2, b, m - 1), f(a, b + 1, m - 1), f(a, b * 2, m - 1)]
    return any(h) if (m - 1) % 2 == 0 else all(h)
print([i for i in range(1, 64) if not f(5, i, 1) and f(5, i, 3)])
print([i for i in range(1, 64) if not f(5, i, 2) and f(5, i, 4)])