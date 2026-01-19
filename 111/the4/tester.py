from the4 import OX_to_tree
from functools import reduce
import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))

def flatten(sol):
    if type(sol) != list:
        return [sol]
    if sol == []:
        return []
    if type(sol[0]) != list:
        return [sol[0]] + flatten(sol[1:])
    return flatten(sol[0]) + flatten(sol[1:])

def inx_check(s1, s2):
    if type(s1) != str or type(s2) != str:
        return False
    if len(s1) != len(s2):
        return False
    diff = 0
    for i in range(len(s1)):
        if (s1[i] != 'x' and s1[i] != 'o') or (s2[i] != 'x' and s2[i] != 'o'):
            return False
        if (s1[i] != s2[i]) and s1[i] == 'x':
            diff += 1
    return True if diff == 1 else False

def is_ox_string(s):
    return reduce((lambda x,y: x and y), [(c == 'x' or c == 'o') for c in s])

def check_case(t):
    if type(t) == list and len(t) == 1:
        return False
    if is_ox_string(t):
        return True
    return reduce((lambda x,y: x and y), [((inx_check(child, t[0]) if type(child) != list else (inx_check(child[0], t[0]) and check_case(child))) and ([(x if type(x) != list else x[0]) for x in t[1:]].count(child if type(child) != list else child[0]) <= 1)) for child in t[1:]])

folder = "./"
file_name = os.path.join(folder, "test_cases.txt")

with open(file_name) as cases:
    passed = 0
    total = 0
    failed = []
    
    for i, case in enumerate(cases):
        print(f"Case#{i+1}: ", end = '')
        case = case.strip()
        strings = eval(case)
        cp_strings = strings[:]
        solution_tree = OX_to_tree(cp_strings)
        if check_case(solution_tree) and sorted(flatten(solution_tree)) == sorted(strings):
            passed += 1
            print("PASSED")
        else:
            failed += ([i+1] if len(failed) <= 26 else [])
            print("FAILED")
        total += 1
        
    print("Total: {}/{}\nAccuracy: %{:.2f}".format(passed, total, passed/total*100))
    
    if passed != total:
        if len(failed) > 25:
            print(f"First failed 25 cases: {failed[:25]}")
        else:
            print(f"Failed cases: {failed}")
        
        print('Good luck next time :(')
    else:
        print("All passed, good job!")
        
input("press enter to exit...")