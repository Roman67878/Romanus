def stallone(lst):
    i = 0
    el = lst[0]
    while i < len(lst):
        if el <= lst[i]:
            el = lst[i]
            i += 1
        else:
            del lst[i]
    return lst


nums = [1, 31, 2, 5, 67, 31]
new_nums = stallone(nums)
print(new_nums)
print(nums[::-1])
