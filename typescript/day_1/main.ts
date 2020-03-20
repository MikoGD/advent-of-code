const fs = require('fs')

const input_puller = (file_name: string): number[] => {
  const file = fs.readFileSync(file_name, 'utf-8')

  const file_split = file.split('\r\n')

  const module_masses = file_split.map((curr: string) => {
    return parseInt(curr, 10)
  })

  return module_masses
}

const fuel_required = (mass: number): number => {
  const extra_fuel = Math.floor(mass / 3) - 2

  if (extra_fuel <= 0) {
    return 0
  }

  return extra_fuel + fuel_required(extra_fuel)
}

const get_total_fuel = (modules: number[]): number => {
  let total_fuel = 0

  modules.forEach(mass => (total_fuel += fuel_required(mass)))

  return total_fuel
}

const run_solution = (): void => {
  const modules: number[] = input_puller('./day_1/input.txt')
  const solution = get_total_fuel(modules)
  console.log(solution)
}

run_solution()
