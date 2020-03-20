'''
day_2
'''
from typing import List


def main():
    code = input_puller('input.txt')
    code[1] = 12
    code[2] = 2
    answer = get_solution(code.copy())

    print(answer)
# END main()


def input_puller(file_name: str) -> List[int]:
    code = []

    with open(file_name, 'r', encoding='utf-8') as file:
        code = file.read().strip().split(',')
        code = [int(num) for num in code]
    # END WITH

    return code
# END input_puller()


def run_opcode(code: List[int], instruction_pointer: int):
    opcode = code[instruction_pointer]
    param_1 = code[instruction_pointer + 1]
    param_2 = code[instruction_pointer + 2]
    param_3 = code[instruction_pointer + 3]

    if opcode == 1:
        code[param_3] = code[param_1] + code[param_2]
    elif opcode == 2:
        code[param_3] = code[param_1] * code[param_2]
    # END IF
# END run_opcode()


def run_program(code: List[int]):
    for i in range(0, len(code), 4):
        if code[i] == 99:
            break
        # END IF

        run_opcode(code, i)
    # END FOR
# END run_program()


def get_solution(code: List[int]) -> int:
    temp_code: List[int]

    for noun in range(0, 100):
        for verb in range(0, 100):
            temp_code = code.copy()
            temp_code[1] = noun
            temp_code[2] = verb
            run_program(temp_code)

            if (temp_code[0] == 19690720):
                return (100 * temp_code[1]) + temp_code[2]
            # END IF
        # END INNER FOR
    # END FOR

    return -1
# END get_solution()


if __name__ == '__main__':
    main()
# END IF
