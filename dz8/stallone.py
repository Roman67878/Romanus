def stallone(lst):
    i = 0
    el = lst[0]
    s = len(lst)
    while i < len(lst):
        if el <= lst[i]:
            el = lst[i]
            i += 1
        else:
            del lst[i]
            s -= 1
    return lst


nums = [1]
new_nums = stallone(nums)
print(new_nums)
