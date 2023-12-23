def bubble(lst):
    for i in range(len(lst)):
        for j in range(len(lst) - 1):
            if lst[j] > lst[i]:
                lst[i], lst[j] = lst[j], lst[i]
    return lst


numbs = [2, 3, 1, 4, 5]
numbs1 = bubble(numbs)
print(numbs1)




            