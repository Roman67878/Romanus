try:
    a = int(input("введите первое число "))
    b = int(input("введите второе число "))
    c = int(input("введите третье число "))
    d = int(input("введите четвертое число "))
    f = int(input("введите пятое число "))
    g = (a*b-c)/(d-f)
    print(g)
except ZeroDivisionError:
    print("На 0 делить нельзя!!")
