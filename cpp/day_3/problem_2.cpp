#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <array>
#include <ctype.h>
#include <cstdlib>
#include <algorithm>

#define DIRECTION tuple<char, int>
#define PATH vector<DIRECTION>
#define LINES vector<Line>
#define TRACKERS vector<Tracker>

using namespace std;

typedef struct Line
{
  int tail[2];
  int head[2];
  int curr_steps = 0;
} Line;

typedef struct Wires
{
  PATH wire_1;
  LINES lines_1;
  PATH wire_2;
  LINES lines_2;
} Wires;

typedef struct Tracker
{
  Line wire_1;
  Line wire_2;
  int intersection[2];
} Tracker;

Wires input_puller(string);
PATH create_path(string);
LINES get_lines(PATH);
Line create_line(Line, DIRECTION);
TRACKERS get_trackers(
    LINES::iterator,
    LINES::iterator,
    LINES::iterator,
    LINES::iterator);
Tracker create_tracker(
    LINES::iterator,
    LINES::iterator,
    LINES::iterator,
    LINES::iterator);
bool check_intersection(LINES::iterator, LINES::iterator);
vector<int> get_manhanttain_distances(TRACKERS::iterator, TRACKERS::iterator);
vector<int> get_steps(TRACKERS::iterator, TRACKERS::iterator);
int calculate_steps(TRACKERS::iterator);

int diff(int, int);
void copy_lines(LINES, LINES);
void copy_array(int[], int[]);

int main()
{
  Wires wires = input_puller("input.txt");

  wires.lines_1 = get_lines(wires.wire_1);
  wires.lines_2 = get_lines(wires.wire_2);

  TRACKERS trackers = get_trackers(
      wires.lines_1.begin(),
      wires.lines_1.end(),
      wires.lines_2.begin(),
      wires.lines_2.end());

  vector<int> distances = get_manhanttain_distances(
      trackers.begin(),
      trackers.end());

  vector<int> steps = get_steps(trackers.begin(), trackers.end());

  cout << *min_element(distances.begin(), distances.end()) << endl;
  cout << *min_element(steps.begin(), steps.end());

  return 0;
}

Wires input_puller(string file_name)
{
  ifstream file;
  string path;
  Wires wires;

  file.open(file_name);

  file >> path;

  wires.wire_1 = create_path(path);

  file >> path;

  wires.wire_2 = create_path(path);

  file.close();

  return wires;
}

PATH create_path(string path)
{
  DIRECTION direction;
  vector<char> steps_char;
  PATH paths;

  for (size_t i = 0; i < path.size(); i++)
  {
    if (isalpha(path[i]))
    {
      get<0>(direction) = path[i];
    }
    else if (isdigit(path[i]))
    {
      steps_char.push_back(path[i]);
    }
    else if (path[i] == ',')
    {
      string steps(steps_char.begin(), steps_char.end());
      get<1>(direction) = stoi(steps);

      paths.push_back(direction);

      steps_char.clear();
    }
  }

  return paths;
}

LINES get_lines(PATH wire)
{
  Line temp, prev_line, next_line;
  int origin[2] = {0, 0};
  copy_array(origin, temp.tail);
  copy_array(origin, temp.head);

  LINES lines;

  lines.push_back(temp);

  for (DIRECTION direction : wire)
  {
    prev_line = lines.back();
    next_line = create_line(prev_line, direction);
    lines.push_back(next_line);
  }

  return lines;
}

Line create_line(Line prev_line, DIRECTION direction)
{
  Line next_line;
  char dir = get<0>(direction);
  int steps = get<1>(direction);

  if (dir == 'R')
  {
    next_line.tail[0] = prev_line.head[0];
    next_line.tail[1] = prev_line.head[1];
    next_line.head[0] = prev_line.head[0] + steps;
    next_line.head[1] = prev_line.head[1];
    next_line.curr_steps = prev_line.curr_steps + steps;
  }
  else if (dir == 'L')
  {
    next_line.tail[0] = prev_line.head[0];
    next_line.tail[1] = prev_line.head[1];
    next_line.head[0] = prev_line.head[0] - steps;
    next_line.head[1] = prev_line.head[1];
    next_line.curr_steps = prev_line.curr_steps + steps;
  }
  else if (dir == 'U')
  {
    next_line.tail[0] = prev_line.head[0];
    next_line.tail[1] = prev_line.head[1];
    next_line.head[0] = prev_line.head[0];
    next_line.head[1] = prev_line.head[1] + steps;
    next_line.curr_steps = prev_line.curr_steps + steps;
  }
  else if (dir == 'D')
  {
    next_line.tail[0] = prev_line.head[0];
    next_line.tail[1] = prev_line.head[1];
    next_line.head[0] = prev_line.head[0];
    next_line.head[1] = prev_line.head[1] - steps;
    next_line.curr_steps = prev_line.curr_steps + steps;
  }
  else
  {
    cout << "ERROR: no direction - " << dir << endl;
    exit(EXIT_FAILURE);
  }

  return next_line;
}

TRACKERS get_trackers(
    LINES::iterator line_1_begin,
    LINES::iterator line_1_end,
    LINES::iterator line_2_begin,
    LINES::iterator line_2_end)
{
  TRACKERS trackers;
  LINES::iterator iter_1, iter_2;

  for (iter_1 = line_1_begin; iter_1 != line_1_end; ++iter_1)
  {
    for (iter_2 = line_2_begin; iter_2 != line_2_end; ++iter_2)
    {
      if (check_intersection(iter_1, iter_2))
      {
        /*
        cout << "creating tracker" << endl;
        cout << "line_1 tail: " << line_1.tail[0] << ", " << line_1.tail[1];
        cout << " head: " << line_1.head[0] << ", " << line_1.head[1] << endl;
        cout << "line_2 tail: " << line_2.tail[0] << ", " << line_2.tail[1];
        cout << "head: " << line_2.head[0] << ", " << line_2.head[1] << endl;
        cout << "index_1: " << index_1 << ", index_2: " << index_2 << endl;
        cout << "wire_2: " << wire_1.size() << ", wire_2: " << wire_2.size() << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        */
        trackers.push_back(create_tracker(
            line_1_begin,
            iter_1,
            line_2_begin,
            iter_2));
      }
    }
  }

  return trackers;
}

Tracker create_tracker(
    LINES::iterator begin_1,
    LINES::iterator end_1,
    LINES::iterator begin_2,
    LINES::iterator end_2)
{
  LINES::iterator horizontal, vertical;
  Tracker tracker;

  if (end_1->tail[0] == end_1->head[0])
  {
    vertical = end_1;
    horizontal = end_2;
  }
  else
  {
    horizontal = end_1;
    vertical = end_2;
  }

  /*
  cout << "horizontal tail: " << horizontal->tail[0] << ", " << horizontal->tail[1];
  cout << " head: " << horizontal->head[0] << ", " << horizontal->head[1] << endl;
  cout << "vertical tail: " << vertical->tail[0] << ", " << vertical->tail[1];
  cout << " head: " << vertical->head[0] << ", " << vertical->head[1] << endl;
  */

  /*
  tracker.wire_1.assign(begin_1, end_1);
  tracker.wire_2.assign(begin_2, end_2);
  */
  tracker.wire_1 = *(end_1 - 1);
  tracker.wire_2 = *(end_2 - 1);
  /*
  cout << horizontal->head[1] << endl;
  cout << end_1->head[1] << endl;
  cout << end_2->head[1] << endl;
  cout << (tracker.wire_1.end() - 1)->head[1] << endl;
  cout << (tracker.wire_2.end() - 1)->head[1] << endl;
  */
  /*
  cout << horizontal->head[1] << endl;
  cout << end_1->head[1] << endl;
  cout << end_2->head[1] << endl;
  cout << (end_1 + 1)->head[1] << endl;
  cout << (end_2 + 1)->head[1] << endl;
  */

  tracker.intersection[0] = vertical->head[0];
  tracker.intersection[1] = horizontal->head[1];
  /*
  cout << tracker.intersection[1] << endl;
  */

  /*
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  for (LINES::iterator i = tracker.wire_1.begin(); i != tracker.wire_1.end(); ++i)
  {
    cout << "tail 1: " << i->tail[0] << ", " << i->tail[1];
    cout << " head 1: " << i->head[0] << ", " << i->head[1] << endl;
    cout << "-------------------" << endl;
  }
  */
  /*
  cout << "tail 0: " << (tracker.wire_1.end() - 0)->tail[0] << ", " << (tracker.wire_1.end() - 0)->tail[0];
  cout << " head 0: " << (tracker.wire_1.end() - 0)->head[0] << ", " << (tracker.wire_1.end() - 0)->head[0] << endl;
  cout << "tail 2: " << (tracker.wire_2.end() - 0)->tail[0] << ", " << (tracker.wire_2.end() - 0)->tail[0];
  cout << " head 2: " << (tracker.wire_2.end() - 0)->head[0] << ", " << (tracker.wire_2.end() - 0)->head[0] << endl;
  */

  /*
  cout << "tail 1: " << (tracker.wire_1.begin() + 35)->tail[0] << ", " << (tracker.wire_1.begin() + 35)->tail[1];
  cout << " head 1: " << (tracker.wire_1.begin() + 35)->head[0] << ", " << (tracker.wire_1.begin() + 35)->head[1] << endl;
  cout << "tail 2: " << (tracker.wire_2.begin() + 35)->tail[0] << ", " << (tracker.wire_2.begin() + 35)->tail[1];
  cout << " head 2: " << (tracker.wire_2.begin() + 35)->head[0] << ", " << (tracker.wire_2.begin() + 1)->head[1] << endl;
  */

  return tracker;
}

bool check_intersection(LINES::iterator line_1, LINES::iterator line_2)
{
  LINES::iterator horizontal, vertical;
  int min_x, min_y, max_x, max_y;
  bool x_b, y_b;

  if (line_1->tail[0] == 0 && line_1->tail[1] == 0)
  {
    return false;
  }

  if (line_1->tail[0] == line_1->head[0] && line_2->tail[1] == line_2->head[1])
  {
    vertical = line_1;
    horizontal = line_2;
  }
  else if (
      line_1->tail[1] == line_1->head[1] && line_2->tail[0] == line_2->head[0])
  {
    horizontal = line_1;
    vertical = line_2;
  }
  else
  {
    return false;
  }

  if (horizontal->tail[0] < horizontal->head[0])
  {
    min_x = horizontal->tail[0];
    max_x = horizontal->head[0];
  }
  else
  {
    min_x = horizontal->head[0];
    max_x = horizontal->tail[0];
  }

  if (vertical->tail[1] < vertical->head[1])
  {
    min_y = vertical->tail[1];
    max_y = vertical->head[1];
  }
  else
  {
    min_y = vertical->head[1];
    max_y = vertical->tail[1];
  }

  for (int x = min_x + 1; x < max_x - 1; x++)
  {
    if (x == vertical->head[0])
    {
      x_b = true;
      break;
    }
    else
    {
      x_b = false;
    }
  }

  for (int y = min_y + 1; y < max_y - 1; y++)
  {
    if (y == horizontal->head[1])
    {
      y_b = true;
      break;
    }
    else
    {
      y_b = false;
    }
  }
  /*
  bool result = x_b && y_b;

  if (result == true)
  {
    string x_str = x_b == true ? "true" : "false";
    string y_str = y_b == true ? "true" : "false";

    cout << "horizontal tail: " << horizontal->tail[0] << ", " << horizontal->tail[1];
    cout << " head: " << horizontal->head[0] << ", " << horizontal->head[1] << endl;
    cout << "vertical tail: " << vertical->tail[0] << ", " << vertical->tail[1];
    cout << " head: " << vertical->head[0] << ", " << vertical->head[1] << endl;

    cout << "x = " << x_str << ", y = " << y_str << endl;
    cout << "result " << result << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  }
  */

  return x_b && y_b;
}

vector<int> get_manhanttain_distances(
    TRACKERS::iterator begin,
    TRACKERS::iterator end)
{
  TRACKERS::iterator iter;
  vector<int> distances;
  int x, y;

  for (iter = begin; iter != end; ++iter)
  {
    x = abs(0 - iter->intersection[0]);
    y = abs(0 - iter->intersection[1]);
    distances.push_back(x + y);
  }

  return distances;
}

vector<int> get_steps(
    TRACKERS::iterator tracker_begin,
    TRACKERS::iterator tracker_end)
{
  vector<int> steps;
  TRACKERS::iterator iter;
  // int i = 0;

  for (iter = tracker_begin; iter != tracker_end; ++iter)
  {
    /*
    cout << "getting steps" << endl;
    cout << "wire_1 tail: " << (iter->wire_1.end() - 1)->tail[0] << ", " << (iter->wire_1.end() - 1)->tail[1];
    cout << " head: " << (iter->wire_1.end() - 1)->head[0] << ", " << (iter->wire_1.end() - 1)->head[1] << endl;
    cout << "wire_2 tail: " << (iter->wire_2.end() - 1)->tail[0] << ", " << (iter->wire_2.end() - 1)->tail[1];
    cout << " head: " << (iter->wire_2.end() - 1)->head[0] << ", " << (iter->wire_2.end() - 1)->head[1] << endl;
    cout << "intersection: " << (iter->intersection[0]) << ", " << (iter->intersection[1]) << endl;
    cout << "getting steps" << endl;
    cout << "wire_1 tail: " << iter->wire_1.tail[0] << ", " << iter->wire_1.tail[1];
    cout << " head: " << iter->wire_1.head[0] << ", " << iter->wire_1.head[1] << endl;
    cout << "wire_2 tail: " << iter->wire_2.tail[0] << ", " << iter->wire_2.tail[1];
    cout << " head: " << iter->wire_2.head[0] << ", " << iter->wire_2.head[1] << endl;
    cout << "intersection: " << (iter->intersection[0]) << ", " << (iter->intersection[1]) << endl;
    */

    steps.push_back(calculate_steps(iter));

    /*
    cout << "i = " << i << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "got steps" << endl;
    i++;
    */
  }

  return steps;
}

int calculate_steps(TRACKERS::iterator tracker)
{
  int wire_1[2] = {
      tracker->wire_1.head[0],
      tracker->wire_1.head[1]};

  int wire_2[2] = {
      tracker->wire_2.head[0],
      tracker->wire_1.head[1]};

  int intersection[2] = {tracker->intersection[0], tracker->intersection[1]};

  int curr_1_steps = tracker->wire_1.curr_steps;
  int curr_2_steps = tracker->wire_2.curr_steps;

  int x_steps, y_steps;

  if (wire_1[0] == intersection[0])
  {
    x_steps = diff(wire_2[0], intersection[0]);
    y_steps = diff(wire_1[1], intersection[1]);
  }
  else
  {
    x_steps = diff(wire_1[0], intersection[0]);
    y_steps = diff(wire_2[1], intersection[1]);
  }

  /*
  if (curr_1_steps + curr_2_steps == 91327)
  {
    cout << tracker->wire_1.tail[0] << ", " << tracker->wire_1.tail[1] << endl;
    cout << tracker->wire_1.head[0] << ", " << tracker->wire_1.head[1] << endl;
    cout << tracker->wire_1.curr_steps << endl;

    cout << tracker->wire_2.tail[0] << ", " << tracker->wire_2.tail[1] << endl;
    cout << tracker->wire_2.head[0] << ", " << tracker->wire_2.head[1] << endl;
    cout << tracker->wire_2.curr_steps << endl;

    cout << tracker->intersection[0] << ", " << tracker->intersection[1] << endl;
    cout << curr_1_steps << endl;
    cout << curr_2_steps << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  }
  */

  return curr_1_steps + curr_2_steps + x_steps + y_steps;
}

int diff(int num_1, int num_2)
{
  int difference = 0;
  if (num_1 > 0 && num_2 > 0)
  {
    difference = abs(num_1 - num_2);
  }
  else if (
      (num_1 < 0 && num_2 > 0) ||
      (num_1 > 0 && num_2 < 0))
  {
    difference = abs(num_1) + num_2;
  }
  else
  {
    difference = abs(abs(num_1) - abs(num_2));
  }

  return difference;
}

void copy_lines(LINES source, LINES dest)
{
  for (Line l : source)
  {
    dest.push_back(l);
  }
}

void copy_array(int source[], int dist[])
{
  for (size_t i = 0; i < 2; i++)
  {
    dist[i] = source[i];
  }
}