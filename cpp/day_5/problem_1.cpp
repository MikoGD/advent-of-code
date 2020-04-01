#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> input_puller(string);
void split_string(const string &, vector<string> &);
vector<int> run_program(vector<int>::iterator, vector<int>::iterator, int);
//void run_instruction(string opcode, vector<int>::iterator, vector<int>::iterator);
inline void op_add(string::iterator, vector<int>::iterator, int);
inline void op_multiply(string::iterator, vector<int>::iterator, int);
inline void op_input(vector<int>::iterator, int, int);
inline int op_output(vector<int>::iterator, int);
inline int get_value(int, vector<int>::iterator, int);

int main()
{
  vector<int> codes, temp_codes, outputs;

  int input = 1;

  codes = input_puller("input.txt");

  outputs = run_program(codes.begin(), codes.end(), input);

  for (int output : outputs)
  {
    cout << output << ", ";
  }
  return 0;
}

vector<int> input_puller(string file_name)
{
  ifstream file;
  string raw_codes;
  vector<string> codes;
  vector<int> int_codes;

  file.open(file_name);

  file >> raw_codes;

  file.close();

  split_string(raw_codes, codes);

  transform(codes.begin(), codes.end(), back_inserter(int_codes),
            [](string s) -> int { return stoi(s); });

  return int_codes;
}

void split_string(const string &str, vector<string> &cont)
{
  stringstream ss(str);
  string token;

  while (getline(ss, token, ','))
  {
    cont.push_back(token);
  }
}

vector<int> run_program(vector<int>::iterator begin, vector<int>::iterator end,
                        int input)
{
  int instruction_pointer = 0;
  vector<int> outputs;
  string opcode, opcode_reverse, instruction, parameter_modes;

  while (*(begin + instruction_pointer) != 99)
  {
    opcode = to_string(*(begin + instruction_pointer));
    cout << *(begin + instruction_pointer) << ", ";
    cout << instruction_pointer << endl;

    if (opcode.size() > 1)
    {
      // Get the reverse of the opcdoe
      opcode_reverse.assign(opcode.begin(), opcode.end() + 1);
      reverse(opcode_reverse.begin(), opcode_reverse.end());

      // Split reverse_opcode to get parameter modes and instruction
      instruction.assign(opcode_reverse.begin(), opcode_reverse.begin() + 2);
      parameter_modes.assign(opcode_reverse.begin() + 2,
                             opcode_reverse.end() + 1);
    }
    else
    {
      parameter_modes.assign(2, 0);
      instruction = opcode;
    }

    if (instruction == "01" || instruction == "1")
    {
      op_add(parameter_modes.begin(), begin, instruction_pointer);
      instruction_pointer += 4;
    }
    else if (instruction == "02" || instruction == "2")
    {
      op_add(parameter_modes.begin(), begin, instruction_pointer);
      instruction_pointer += 4;
    }
    else if (instruction == "3")
    {
      op_input(begin, instruction_pointer, input);
      instruction_pointer += 2;
    }
    else if (instruction == "4")
    {
      outputs.push_back(op_output(begin, instruction_pointer));
      instruction_pointer += 2;
    }
    else
    {
      cout << "error: opcode " << instruction << " does not exist";
      exit(EXIT_FAILURE);
    }
  }

  return outputs;
}

/*
void run_instruction(string opcode, vector<int>::iterator begin,
                     vector<int>::iterator end)
{
  string opcode_reverse, instruction, parameter_modes;

  opcode_reverse.assign(opcode.begin(), opcode.end());
  reverse(opcode_reverse.begin(), opcode_reverse.end());

  instruction.assign(opcode_reverse.begin(), opcode_reverse.begin() + 2);
  parameter_modes.assign(opcode_reverse.begin() + 2, opcode_reverse.end());

  if (instruction == "01")
  {
    op_add(begin, parameter_modes.begin(), parameter_modes.end());
  }
  else if (instruction == "02")
  {
    op_add(begin, parameter_modes.begin(), parameter_modes.end());
  }
  else if (instruction == "03")
  {
  }
  else if (instruction == "04")
  {
  }
  else
  {
    cout << "ERROR: no instruction " << instruction << endl;
    exit(EXIT_FAILURE);
  }
}
*/

inline void op_add(string::iterator param_modes,
                   vector<int>::iterator begin_codes,
                   int instruction_offset)
{
  vector<int>::iterator curr_instruction = begin_codes + instruction_offset;
  int param_1 = get_value(*(param_modes), begin_codes, instruction_offset + 1);
  int param_2 = get_value(*(param_modes + 1), begin_codes,
                          instruction_offset + 2);
  int pos = *(curr_instruction + 3);

  *(begin_codes + pos) = param_1 + param_2;
}

inline void op_multiply(string::iterator param_modes,
                        vector<int>::iterator begin_codes,
                        int instruction_offset)
{
  vector<int>::iterator curr_instruction = begin_codes + instruction_offset;
  int param_1 = get_value(*(param_modes), begin_codes, instruction_offset + 1);
  int param_2 = get_value(*(param_modes + 1), begin_codes,
                          instruction_offset + 2);
  int pos = *(curr_instruction + 3);

  *(begin_codes + pos) = param_1 * param_2;
}

inline void op_input(vector<int>::iterator begin_codes, int instruction_offset,
                     int input)
{
  *(begin_codes + *(begin_codes + instruction_offset)) = input;
}

inline int op_output(vector<int>::iterator begin_codes, int instruction_offset)
{
  return *(begin_codes + *(begin_codes + instruction_offset));
}

inline int get_value(int param_mode, vector<int>::iterator begin_codes,
                     int param_offset)
{
  if (param_mode == 0)
  {
    return *(begin_codes + *(begin_codes + param_offset));
  }
  else if (param_mode == 1)
  {
    return *(begin_codes + param_offset);
  }
  else
  {
    cout << "ERROR: No parameter mode " << param_mode << endl;
    exit(EXIT_FAILURE);
  }
}