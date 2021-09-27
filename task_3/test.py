import os
import random as rnd
from collections import defaultdict


PROGRAM_NAME  = 'task_A'
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
        '5 12\n1 3 5 7 9\n-10 1 2 3 4 5 6 7 8 9 10 100\n',
        '5 5\n1 1 1 1 1\n-2 -1 1 2 3\n',
        '5 10\n-5 -4 -3 -2 -1\n-7 -4 -5 -2 0 1 2 3 -2 10\n',
        '10 10\n1 1 3 3 4 4 4 5 5 5\n-1 1 2 3 4 5 6 7 9 0\n',
        '1 6\n1\n-1 1 3 4 5 100\n',
        '2 6\n1 6\n-1 1 3 4 5 100\n'
    ]

    return result


def right_solution(input_data_lst: list) -> list:
    result = [
        '1 1 1 3 3 5 5 7 7 9 9 9',
        '1 1 1 1 1',
        '-5 -4 -5 -2 -1 -1 -1 -1 -2 -1',
        '1 1 1 3 4 5 5 5 5 1',
        '1 1 1 1 1 1',
        '1 1 1 6 6 6'
    ]

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

        if test_output.strip('\n').strip(' ') == right_output.strip('\n').strip(' '):
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

