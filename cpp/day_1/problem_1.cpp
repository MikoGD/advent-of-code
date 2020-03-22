#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

vector<int> input_puller(string);

double get_fuel_required(vector<int>);
double calculate_fuel(double);

int main()
{
  vector<int> modules = input_puller("input.txt");
  double fuel = get_fuel_required(modules);

  cout << fixed;
  cout << "Fuel require: " << fuel << endl;

  return 0;
} // END main()

vector<int> input_puller(string file_name)
{
  ifstream file;
  vector<int> modules;
  int module;

  file.open("input.txt");

  while (file.good())
  {
    file >> module;
    modules.push_back(module);
  } // END WHILE

  file.close();

  return modules;
} // END input_puller()

double get_fuel_required(vector<int> modules)
{
  double fuel = 0;

  for (int module : modules)
  {
    fuel += calculate_fuel((double)module);
  } // END FOR

  return fuel;
} // END get_fuel_required()

double calculate_fuel(double module)
{
  return floor(module / 3) - 2;
} // END calculate_fuel()