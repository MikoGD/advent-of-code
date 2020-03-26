#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool check_increase(string::iterator, string::iterator);
bool check_adjacent(string::iterator, string::iterator);

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
    adjacent = check_adjacent(begin, end);

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

bool check_adjacent(string::iterator begin, string::iterator end)
{
  string::iterator curr_iter = begin;
  string::iterator adj_iter;
  bool result = false;

  while (curr_iter != end)
  {
    adj_iter = adjacent_find(curr_iter, end);

    if (adj_iter == end)
    {
      return false;
    }
    else
    {
      result = true;
      adj_iter++;

      while(adj_iter != end)
      {
        if (*adj_iter == *(adj_iter + 1))
        {
          result = false;
          adj_iter++;
        }
        else
        {
          curr_iter = adj_iter++;
          break;
        }
      }

      if (result == true)
      {
        return true;
      }
    }
  }
  return result;
}