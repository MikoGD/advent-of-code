#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int> input_puller(string);
vector<string> split_string(string, char);
vector<int> convert_to_int(vector<string>);
void run_program(vector<int> &);

int main()
{
  vector<int> codes;
  int output;

  codes = input_puller("input.txt");

  codes[1] = 12;
  codes[2] = 2;

  run_program(codes);

  output = codes[0];

  cout << "output: " << output << endl;

  return 0;
} // END main()

vector<int> input_puller(string file_name)
{
  ifstream file;
  vector<string> codes;
  string raw_codes;
  vector<int> int_codes;

  file.open("input.txt");

  file >> raw_codes;

  file.close();

  codes = split_string(raw_codes, ',');
  int_codes = convert_to_int(codes);

  return int_codes;
} // END input_puller()

vector<string> split_string(string raw_string, char delimiter)
{
  vector<char> elem;
  vector<string> split_string;

  for (size_t i = 0; i < raw_string.length(); i++)
  {
    if (raw_string[i] != delimiter)
    {
      elem.push_back(raw_string[i]);
    }
    else
    {
      string temp(elem.begin(), elem.end());
      split_string.push_back(temp);
      elem.clear();
    } // END IF
  }   // END FOR

  return split_string;
} // END split_string()

vector<int> convert_to_int(vector<string> codes)
{
  vector<int> int_codes;

  for (string code : codes)
  {
    int_codes.push_back(stoi(code));
  } // END FOR

  return int_codes;
} // END convert_to_int()

void run_program(vector<int> &codes)
{
  int opcode, param_1, param_2, pos, instruction_pointer;

  opcode = 0;
  instruction_pointer = 0;

  while (codes[instruction_pointer] != 99)
  {
    opcode = codes[instruction_pointer];
    param_1 = codes[instruction_pointer + 1];
    param_2 = codes[instruction_pointer + 2];
    pos = codes[instruction_pointer + 3];

    if (opcode == 1)
    {
      codes[pos] = codes[param_1] + codes[param_2];
    }
    else if (opcode == 2)
    {
      codes[pos] = codes[param_1] * codes[param_2];
    }
    else
    {
      cout << "error: opcode " << opcode << " does not exist";
      exit(EXIT_FAILURE);
    } // END IF

    instruction_pointer += 4;
  } // END WHILE
} // END run_program()