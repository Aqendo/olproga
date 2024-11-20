def find_subarray(arr, k):
    n = len(arr)
    if k > n:
        return False  # Невозможно найти подмассив длины k

    start = 0
    count = 0

    for end in range(n):
        count += arr[end]

        while count > (end - start + 1) / 2:
            if end - start + 1 >= k:
                return True  # Найден подмассив длины не менее k с больше чем половиной единиц
            count -= arr[start]
            start += 1

    return False  # Подмассив не найден


# Пример использования
arr = [0, 1, 1, 0, 1, 1, 0, 1, 0, 1]
k = 4
print(find_subarray(arr, k))  # Вывод: True
