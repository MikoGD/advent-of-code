def get_fuels_fuel(m): return 0 if m <= 0 else m + get_fuels_fuel((m//3) - 2)
with open('input.txt', 'r', encoding='utf-8') as file: modules = [int(line) for line in file]
fuels = list(map(lambda n: get_fuels_fuel((n//3)-2), modules))
result = 0
for fuel in fuels: result += fuel
print(result)