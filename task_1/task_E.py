L = 50
I = 1
II = 2
III = 3
IV = 4
V = 5
IX = 9
X = 10
XXX = 30

rome_to_arabic_dict = {}

def rome_to_arabic(rome_number: str) -> int:
    if len(rome_number) == 0:
        rome_to_arabic_dict[''] = 0
        return 0
    if rome_number == 'L':
        rome_to_arabic_dict['L'] = L
        return L

    arabic_number = 0
    current_latter = 0

    while current_latter < len(rome_number) and rome_number[current_latter] == 'X':
        arabic_number += X
        current_latter += 1

    if current_latter < len(rome_number) and rome_number[current_latter] == 'L':
        arabic_number += XXX
        current_latter += 1

    if current_latter < len(rome_number) and rome_number[current_latter] == 'I':
        current_latter += 1

        if len(rome_number) - current_latter == 0:
            arabic_number += I
        elif len(rome_number) - current_latter == 1 and rome_number[current_latter] == 'I':
            arabic_number += II
        elif len(rome_number) - current_latter == 1 and rome_number[current_latter] == 'V':
            arabic_number += IV
        elif len(rome_number) - current_latter == 1 and rome_number[current_latter] == 'X':
            arabic_number += IX
        elif len(rome_number) - current_latter == 2:
            arabic_number += III
    elif current_latter < len(rome_number) and rome_number[current_latter] == 'V':
        current_latter += 1
        arabic_number += V + len(rome_number) - current_latter

    rome_to_arabic_dict[rome_number] = arabic_number

    return arabic_number
    

if __name__ == "__main__":
    n = int(input())
    input_lst = []

    for i in range(n):
        input_lst.append(input())

    input_lst = [name.strip().split() for name in input_lst]
    input_lst = [(pair[0], rome_to_arabic(pair[1])) for pair in input_lst]
    input_lst = sorted(input_lst)
    arabic_to_rome_dict = {rome_to_arabic_dict[key]: key for key in rome_to_arabic_dict}
    input_lst = [(pair[0], arabic_to_rome_dict[pair[1]]) for pair in input_lst]
    input_lst = list(' '.join(pair) for pair in input_lst)
    
    print('\n'.join(input_lst))
