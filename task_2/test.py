import os
import random as rnd
from collections import defaultdict


PROGRAM_NAME  = 'task_D'
PROGRAM_DIR = 'build'
TEST_DIR = 'tests'

TEST_INPUT_NAME = 'test_input.txt'
TEST_OUTPUT_NAME = 'test_output.txt'
FAILED_TEST_LOG = True
FAILED_TEST_PRINT = True
FAILED_TEST_INPUT = 'test_N_input.txt'
FAILED_TEST_OUTPUT = 'test_N_output.txt'
FAILED_RIGHT_OUTPUT = 'test_N_right.txt'


def test_generator() -> list:
    result = [
        '4 3\naaab\naba\n',
        '7 3\nabacaba\nabc\n',
        '5 3\naaaaa\naaa\n',
        '1 1\na\na\n',
        '1 1\na\nb\n'
        '5 1\naaaaa\na\n',
        '14 72\nbgnssorosxhzed\nrxzoxrngrhozshhsshzrbgxgbndrbdbngeordsnebxbgzrbnhnoxohdorsrzbogdndzddobg\n',
        '12 2\ngggbabggggga\nba\n'
        # '100000 100000\n' + 'bababaaabb' * 10000 + '\n' + 'bbabaaaaac' * 10000 + '\n'
    ]

    test_count = 100

    for test_no in range(test_count):
        n = rnd.randint(1, 10**3)
        m = rnd.randint(1, 10**2)
        str_1 = ''
        str_2 = ''
        for i in range(n):
            str_1 += chr(rnd.randint(ord('a'), ord('b')))

        for i in range(m):
            # str_2 += chr(rnd.randint(ord('a'), ord('z')))
            str_2 += rnd.choice(list(set(str_1)))

        res = str(n) + ' ' + str(m) + '\n' + str_1 + '\n' + str_2 + '\n'
        result.append(res)

    return result


def right_solution(input_data_lst: list) -> list:

    def count_latters(substring: str, count_dict: dict) -> int:
        sub_count = defaultdict(lambda: 0)

        for i in substring:
            sub_count[i] += 1

        res = 1

        for i in sub_count:
            if sub_count[i] > count_dict[i]:
                res = 0

        return res


    result = []

    for input_data in input_data_lst:
        input_data = input_data.strip('\n').split('\n')
        n, m = list(map(int, input_data[0].split(' ')))
        str_1 = input_data[1]
        str_2 = input_data[2]
        cards_sym_count = defaultdict(lambda: 0)
        count = 0

        for i in str_2:
            cards_sym_count[i] += 1

        for i in range(1, m + 1):
            for j in range(len(str_1) - i + 1):
                count += count_latters(str_1[j:j + i], cards_sym_count)

        result.append(str(count) + '\n')

    return result


if __name__ == '__main__':
    test_input_path = os.path.join(TEST_DIR, TEST_INPUT_NAME)
    test_output_path = os.path.join(TEST_DIR, TEST_OUTPUT_NAME)
    test_program_name = os.path.join(PROGRAM_DIR, PROGRAM_NAME)
    cmd = 'cat ' + test_input_path + ' | ' + test_program_name + ' > ' + test_output_path
    ok_test_count = 0
    failed_test_count = 0
    test_input_lst = test_generator()
    right_output_lst = right_solution(test_input_lst)

    for test_no, test_input in enumerate(test_input_lst):
        with open(test_input_path, 'w') as f:
            f.write(test_input)

        os.system(cmd)

        with open(test_output_path, 'r') as f:
            test_output = f.read()

        right_output = right_output_lst[test_no]

        if test_output == right_output:
            ok_test_count += 1
            print(f'Test {test_no}: OK')
        else:
            print(f'Test {test_no}: Failed')

            if FAILED_TEST_LOG or FAILED_TEST_PRINT:
                failed_input_name = str(test_no).join(FAILED_TEST_INPUT.split('N'))
                failed_input_name = os.path.join(TEST_DIR, failed_input_name)
                failed_output_name = str(test_no).join(FAILED_TEST_OUTPUT.split('N'))
                failed_output_name = os.path.join(TEST_DIR, failed_output_name)
                failed_right_name = str(test_no).join(FAILED_RIGHT_OUTPUT.split('N'))
                failed_right_name = os.path.join(TEST_DIR, failed_right_name)

                if FAILED_TEST_LOG:
                    with open(failed_input_name, 'w') as f:
                        f.write(test_input)
                    
                    with open(failed_output_name, 'w') as f:
                        f.write(test_output)

                    with open(failed_right_name, 'w') as f:
                        f.write(right_output)

                if FAILED_TEST_PRINT:
                    print('\nINPUT:\n', test_input)
                    print('\nOUTPUT:\n', test_output)
                    print('\nRIGHT\n', right_output, '\n')

            failed_test_count += 1

    print('\n\nAll tests done')
    # print('\nTotal:', failed_test_count + ok_test_count)
    print('OK:', ok_test_count)
    print('Failed:', failed_test_count)

