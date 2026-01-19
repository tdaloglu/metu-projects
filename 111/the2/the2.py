d = eval(input())
annual_income = float(input())
tax = 0

def number_of_children_under_18(n):
    if n < 18:
        return n

list_of_child_under_18 = list(filter(number_of_children_under_18,d["CHILD"]))

def tax_calculation(dict):
    if dict["INCOME"] == "low":
        tax = (annual_income*10)/100
    elif dict["INCOME"] == "middle":
        tax = (annual_income*20)/100
    else:
        tax = (annual_income*30)/100

    if dict["MARITAL_STATUS"] == "married":
        tax = tax - 500 - (300*len(dict["CHILD"]))
    elif dict["MARITAL_STATUS"] == "single_parent":
        tax = tax - (600*len(dict["CHILD"]))

    tax = tax - (200*len(list_of_child_under_18))

    if dict["SPECIAL_NEEDS"]:
        tax = tax - 1000

    if dict["ELDERLY_CARE"]:
        tax = tax - 800

    if dict["CITY_CATEGORY"] == "suburban":
        tax = tax - 200
    elif dict["CITY_CATEGORY"] == "rural":
        tax = tax - 400

    if dict["EDUCATION"]:
        tax = tax - 500

    if dict["HEALTHCARE"]:
        tax = tax - 750

    if dict["GREEN_INITIATIVES"]:
        tax = tax - 300

    if dict["PROPERTY_STATUS"] == "rents":
        tax = tax - 300

    if dict["TAXPAYER_DURATION"] == "regular":
        tax = (tax*95)/100
    elif dict["TAXPAYER_DURATION"] == "long_term":
        tax = (tax*90)/100

    if tax < 0:
        tax = 0

    return tax

final_tax_amount = tax_calculation(d)

print("%.2f" % final_tax_amount)
