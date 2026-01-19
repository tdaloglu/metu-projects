import os
import time
import importlib.util

spec = importlib.util.spec_from_file_location("the3", "./the3.py")
the3 = importlib.util.module_from_spec(spec)
spec.loader.exec_module(the3)

cases_dir = "./Cases/Medium Cases"

if not os.path.exists(cases_dir):
    print(f"Error: Test case directory '{cases_dir}' does not exist.")
    exit(1)

case_files = sorted([f for f in os.listdir(cases_dir) if f.endswith(".txt")])

if not case_files:
    print(f"Error: No test case files found in '{cases_dir}'.")
    exit(1)

correct_count = 0
total_count = 0
first_failed_case = None

for case_file in case_files:
    case_path = os.path.join(cases_dir, case_file)
    try:
        with open(case_path, "r") as f:
            lines = f.read().strip().split("\n")

        n, m = map(int, lines[0].split())
        string_list = lines[1:n+1]
        correct_output = int(lines[n+1])

        start_time = time.time()
        try:
            output = the3.count_rectangles(string_list)
            elapsed_time = (time.time() - start_time) * 1000

            result = "PASS" if output == correct_output else "FAIL"
            if result == "PASS":
                correct_count += 1
            else:
                if first_failed_case is None:
                    first_failed_case = case_file
            total_count += 1

            print(f"{case_file}: Result = {output}, Expected = {correct_output}, Time = {elapsed_time:.2f}ms, {result}")
        except Exception as e:
            total_count += 1
            if first_failed_case is None:
                first_failed_case = case_file
            print(f"{case_file}: Error during function execution: {e}")
    except Exception as e:
        total_count += 1
        if first_failed_case is None:
            first_failed_case = case_file
        print(f"{case_file}: Error reading or processing file: {e}")

if total_count > 0:
    accuracy = (correct_count / total_count) * 100
    print(f"\nTest Summary: {correct_count}/{total_count} cases passed. Accuracy = {accuracy:.2f}%")
    if accuracy == 100.0:
        print("Congratulations! All test cases passed successfully.")
    else:
        print(f"First failed case: {first_failed_case}")
