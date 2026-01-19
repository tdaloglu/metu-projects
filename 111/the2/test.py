import subprocess

# Test Case Format:
# It is a tuple with 2 values:
# (<input-text>, <expected-output>)
# If you add or change test cases please make sure to
# set the <extected-output> to the right value.

test_cases = [("""{"INCOME": "middle", "MARITAL_STATUS": "married",\
                "CHILD": [12,13,19], "SPECIAL_NEEDS": False,\
                "ELDERLY_CARE": True, "TAXPAYER_DURATION": "regular",\
                "CITY_CATEGORY": "suburban","EDUCATION": True, "HEALTHCARE": False,\
                "GREEN_INITIATIVES":True,"PROPERTY_STATUS": "rents"}\n36000.00\n""", "3135.00"),

              ("""{"INCOME": "high", "MARITAL_STATUS": "single_parent",\
                "CHILD": [11,18,21], "SPECIAL_NEEDS": False,\
                "ELDERLY_CARE": True, "TAXPAYER_DURATION": "long_term",\
                "CITY_CATEGORY": "urban","EDUCATION": True, "HEALTHCARE": True,\
                "GREEN_INITIATIVES":False,"PROPERTY_STATUS": "owns"}\n57800.00\n""", "11961.00"),

              ("""{"INCOME": "low", "MARITAL_STATUS": "married",\
                "CHILD": [25,20], "SPECIAL_NEEDS": True,\
                "ELDERLY_CARE": True, "TAXPAYER_DURATION": "regular",\
                "CITY_CATEGORY": "rural","EDUCATION": False, "HEALTHCARE": False,\
                "GREEN_INITIATIVES":False,"PROPERTY_STATUS": "rents"}\n29000.0\n""", "0.00"),

              ("""{"INCOME": "middle", "MARITAL_STATUS": "single_parent",\
                "CHILD": [10,14], "SPECIAL_NEEDS": False,\
                "ELDERLY_CARE": False, "TAXPAYER_DURATION": "new",\
                "CITY_CATEGORY": "urban","EDUCATION": True, "HEALTHCARE": False,\
                "GREEN_INITIATIVES":True,"PROPERTY_STATUS": "owns"}\n41500.0\n""", "5900.00"),

              ("""{"INCOME": "high", "MARITAL_STATUS": "married",\
                "CHILD": [4,12,18], "SPECIAL_NEEDS": False,\
                "ELDERLY_CARE": True, "TAXPAYER_DURATION": "long_term",\
                "CITY_CATEGORY": "urban","EDUCATION": True, "HEALTHCARE": True,\
                "GREEN_INITIATIVES":False,"PROPERTY_STATUS": "owns"}\n61500.0\n""", "13140.00"),

              ("""{"INCOME": "low", "MARITAL_STATUS": "single",\
                "CHILD": [], "SPECIAL_NEEDS": True,\
                "ELDERLY_CARE": False, "TAXPAYER_DURATION": "new",\
                "CITY_CATEGORY": "urban","EDUCATION": False, "HEALTHCARE": False,\
                "GREEN_INITIATIVES":False,"PROPERTY_STATUS": "rents"}\n30500.0\n""", "1750.00"),


              ]


for i,v in enumerate(test_cases):
    inputs = v[0]
    process = subprocess.Popen(
    ["python","the2.py"],
    stdin = subprocess.PIPE,
    stdout = subprocess.PIPE,
    stderr = subprocess.PIPE,
    text = True
    )
    stdout, stderr = process.communicate(inputs)
    if stderr :
        print(f"Err in the test case {i}:")
        raise Exception(stderr)
    if stdout == v[1]+"\n":
        print(f"Case {i}: Test Passed")
    else:
        print(f"Case {i}: Test Failed: {stdout.rstrip("\n")} should equal {v[1]}")
