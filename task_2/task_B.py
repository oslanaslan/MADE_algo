MAX_ELEMENT_RANGE = 101

if __name__ == '__main__':
    element_counts = [0] * MAX_ELEMENT_RANGE
    result = []

    input_data = input().split()
    input_data = [int(i) for i in input_data]

    for i in input_data:
        element_counts[i] += 1
    
    for i in range(MAX_ELEMENT_RANGE):
        for j in range(element_counts[i]):
            result.append(i)

    print(' '.join(map(str, result)))