import sys


if __name__ == "__main__":
    num_to_rome = {0: '', 1: 'I', 2: 'II', 3: 'III', 4: 'IV', 5: 'V', 6: 'VI', 7: 'VII', 8: 'VIII', 9: 'IX', 10: 'X',
        20: 'XX', 30: 'XXX', 40: 'XL', 50: 'L'}
    
    for i in range(1, 51):
        if i not in num_to_rome:
            num_to_rome[i] = num_to_rome[(i // 10) * 10] + num_to_rome[i % 10]

    rome_to_num = {num_to_rome[key]: key for key in num_to_rome}
    input_lst = []
    N = int(input())

    for i in range(N):
        input_lst.append(input())

    input_lst = [name.strip().split() for name in input_lst]
    input_lst = [(pair[0], rome_to_num[pair[1]]) for pair in input_lst]
    input_lst = sorted(input_lst)
    input_lst = [(pair[0], num_to_rome[pair[1]]) for pair in input_lst]
    input_lst = list(' '.join(pair) for pair in input_lst)
    
    sys.stdout.write('\n'.join(input_lst) + '\n')
    sys.stdout.flush()
