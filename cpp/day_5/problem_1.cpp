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
void run_program(vector<int> &);

int main()
{
  vector<int> codes;
  vector<int> temp_codes;

  codes = input_puller("input_2.txt");

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

  for (string code : codes)
  {
    cout << code << endl;
  }

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

/*
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
*/