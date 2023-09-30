list = []
y = input("введите число ")
while y:
    y = input("введите число ")
    list.append(y)
    list.sort(reverse=True)
print("".join(list))