x = input("введите выражение ")
y = x.count("(")
z = x.count(")")
if y > z:
    print("не хватает закрывающих скобок!")
elif y < z:
    print("не открывающих скобок!")
else:
    print("скобки на месте!")