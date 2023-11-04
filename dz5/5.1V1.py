def search(sp, pos):
    low = sp[0]
    high = sp[len(sp) - 1]
    mid = len(sp) // 2

    while low <= high and sp[mid] != pos:
        if sp[mid] < pos:
            low = mid + 1
        else:
            high = mid - 1
    if low > high:
        return ("Не найден!")
    else:
        return mid

#sp = input("Введите строку: ")
#pos = input("Желаемый элемент: ")
print(search([12,23,34,45,57,57,5,34], 4))