def count_rectangles(Pattern):
    def coordinates(x, y):
        return Pattern[y][x]

    def find_1s(lst):
        result = []
        for y in range(len(lst)):
            for x in range(len(lst[0])):
                if coordinates(x, y) == "1":
                    result.append((x, y))
        return result

    def check_if_rectangles(p1, p2):
        a = p1[0]
        b = p1[1]
        c = p2[0]
        d = p2[1]
        if abs(a-c) < 2 or abs(b-d) < 2:
            return False
        if a >= c or b >= d:
            return False
        for i in range(a, c+1):
            if coordinates(i, b) == "0" or coordinates(i, d) == "0":
                return False
        for j in range(b, d+1):
            if coordinates(a, j) == "0" or coordinates(c, j) == "0":
                return False
        for k in range(a+1, c):
            for l in range(b+1, d):
                if coordinates(k, l) == "0":
                    return True
        return False

    def func(lst):
        result = []
        for i in lst:
            for j in lst:
                if i != j:
                    tup = tuple(sorted([i, j]))
                    if tup not in result:
                        result.append(tup)
        return result

    result = func(find_1s(Pattern))
    count = 0
    for i in result:
        if check_if_rectangles(i[0], i[1]):
            count += 1
    return count
