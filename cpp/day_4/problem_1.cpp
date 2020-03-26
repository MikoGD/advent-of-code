#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool check_increase(string::iterator, string::iterator);

int main()
{
  int start_range = 367479;
  int end_range = 893698;
  int count_viable = 0;

  bool increase, adjacent;

  string curr_num;
  string::iterator begin, end;

  for (int i = start_range; i < end_range + 1; i++)
  {
    curr_num = to_string(i);
    begin = curr_num.begin();
    end = curr_num.end();

    increase = check_increase(begin, end);
    adjacent = adjacent_find(begin, end) != end;

    if (increase == true && adjacent == true)
    {
      count_viable++;
    }
  }

  cout << count_viable << endl;

  return 0;
}

bool check_increase(string::iterator begin, string::iterator end)
{
  string::iterator iter;

  for (iter = begin + 1; iter != end; ++iter)
  {
    if (*iter < *(iter - 1))
    {
      return false;
    }
  }

  return true;
}