size = int(input("Размер таблицы: "))
tabl = [0] * size
elem = int(input("Введите элемент: "))


def hessh(key):
    h_key = key % size
    return h_key


def pair(key, value):
    return lambda n: key if n == 0 else value

def set_value(key, value):
    global pair
    h_index = hessh(key)
    if tabl[h_index] is not None:
        for pair in tabl[h_index]:
            if pair[0] == key:
                pair[1] = value
                return tabl
        tabl[h_index].append([key, value])
    else:
        tabl[h_index] = [[key, value]]
    return tabl


#def get_value(key):
    

       



        







        