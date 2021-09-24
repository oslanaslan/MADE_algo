import os
import random as rnd


PROGRAM_NAME  = 'task_D'
PROGRAM_DIR = 'build'
TEST_DIR = 'tests'

TEST_INPUT_NAME = 'test_input.txt'
TEST_OUTPUT_NAME = 'test_output.txt'
FAILED_TEST_LOG = True
FAILED_TEST_INPUT = 'test_N_input.txt'
FAILED_TEST_OUTPUT = 'test_N_output.txt'
FAILED_RIGHT_OUTPUT = 'test_N_right.txt'


def test_generator() -> list:
    result = [
        '4 3\naaab\naba\n',
        '7 3\nabacaba\nabc\n'
    ]

    return result


def right_solution(input_data_lst: list) -> list:
    result = [
        '8\n',
        '15\n'
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

        if test_output == right_output:
            ok_test_count += 1
            print(f'Test {test_no}: OK')
        else:
            if FAILED_TEST_LOG:
                failed_input_name = str(test_no).join(FAILED_TEST_INPUT.split('N'))
                failed_input_name = os.path.join(TEST_DIR, failed_input_name)
                failed_output_name = str(test_no).join(FAILED_TEST_OUTPUT.split('N'))
                failed_output_name = os.path.join(TEST_DIR, failed_output_name)
                failed_right_name = str(test_no).join(FAILED_RIGHT_OUTPUT.split('N'))
                failed_right_name = os.path.join(TEST_DIR, failed_right_name)

                with open(failed_input_name, 'w') as f:
                    f.write(test_input)
                
                with open(failed_output_name, 'w') as f:
                    f.write(test_output)

                with open(failed_right_name, 'w') as f:
                    f.write(right_output)

            failed_test_count += 1
            print(f'Test {test_no}: Failed')

    print('\n\nAll tests done')
    # print('\nTotal:', failed_test_count + ok_test_count)
    print('OK:', ok_test_count)
    print('Failed:', failed_test_count)

