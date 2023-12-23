def quick(lst) -> tuple[list, int, list]:
    if len(lst) <= 1:
        return lst
    middle = lst[(len(lst) // 2)]
    low = [x for x in lst if x <= middle]
    high = [x for x in lst if x >= middle]
    return low, middle, high


nums = [1, 4, 2, 5, -3]
new_nums = quick(nums)
print(new_nums)



