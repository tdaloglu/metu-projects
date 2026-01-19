def operation(string):
    result = []
    for i in range(len(string)):
        if string[i] == "o":
            element = string[:i] + "x" + string[i+1:]
            result.append(element)
    return result


def find_children(string, lst):
    result = []
    for item in operation(string):
        if item in lst:
            result.append(item)
    return result


def find_min_x(lst):
    min_string = lst[0]
    count = min_string.count("x")
    for item in lst:
        if item.count("x") <= count:
            min_string = item
            count = min_string.count("x")
    return min_string


def make_tree(string, lst):
    children = find_children(string, lst)
    index = lst.index(string)
    del lst[index]
    if children == []:
        return string
    else:
        element = []  
        for child in children:
            element.append(make_tree(child, lst))
        return [string] + element


def OX_to_tree(lst):
    root = find_min_x(lst)
    new_lst = lst[:]
    return make_tree(root, new_lst)


