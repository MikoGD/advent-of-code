'''
Solution for day 1
'''
from typing import List
import math


def main():
    modules: List[int] = input_puller('input.txt')
    module_fuel: float = get_modules_fuel(modules)

    print(f'The amount of fuel required for the modules is {module_fuel}')
# END main()


def input_puller(file_name: str) -> List[int]:
    modules: List[int] = []

    with open(file_name, 'r', encoding='utf-8') as file:
        for line in file:
            modules.append(int(line))
        # END FOR
    # END WITH

    return modules
# END input_puller()


def fuel_required(mass: float) -> float:
    result: float = math.floor(mass / 3) - 2

    return result
# END fuel_required()


def get_modules_fuel(modules: List[int]) -> float:
    result: float = 0
    modules_fuel: float = 0

    for module in modules:
        module_fuel = fuel_required(module)
        fuels_fuel = get_fuels_fuel(module_fuel)
        result += module_fuel + fuels_fuel
    # END FOR

    return result
# END get_solution()


def get_fuels_fuel(mass: float) -> float:
    result: float = math.floor(mass / 3) - 2

    if result <= 0:
        return 0
    else:
        return result + get_fuels_fuel(result)
# END get_fuels_fuel


if __name__ == '__main__':
    main()
# END IF