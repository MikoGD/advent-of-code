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
  vector<Line> lines_1;
  PATH wire_2;
  vector<Line> lines_2;
} Wires;

typedef struct Tracker
{
  LINES wire_1;
  LINES wire_2;
  int intersection[2];
} Tracker;

Wires input_puller(string);
PATH create_path(string);
LINES get_lines(PATH);
Line create_line(Line, DIRECTION);
TRACKERS get_trackers(LINES, LINES);
Tracker create_tracker(LINES, LINES, Line, Line, int, int);
bool check_intersection(Line, Line);
vector<int> get_manhanttain_distances(TRACKERS);

void copy_lines(LINES, LINES);
void copy_array(int[], int[]);

int main()
{
  Wires wires = input_puller("input.txt");

  wires.lines_1 = get_lines(wires.wire_1);
  wires.lines_2 = get_lines(wires.wire_2);

  TRACKERS trackers = get_trackers(wires.lines_1, wires.lines_2);
  /*
  for (Tracker tracker : trackers)
  {
    cout << "intersection: " << tracker.intersection[0] << ", " << tracker.intersection[1] << endl;
  }
  */

  vector<int> distances = get_manhanttain_distances(trackers);

  cout << *min_element(distances.begin(), distances.end()) << endl;

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

TRACKERS get_trackers(LINES wire_1, LINES wire_2)
{
  TRACKERS trackers;
  int index_1 = 0;
  int index_2 = 0;

  for (Line line_1 : wire_1)
  {
    for (Line line_2 : wire_2)
    {
      if (check_intersection(line_1, line_2))
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

        trackers.push_back(
            create_tracker(
                wire_1,
                wire_2,
                line_1,
                line_2,
                index_1,
                index_2));
      }
      index_2++;
    }
    index_1++;
    index_2 = 0;
  }

  return trackers;
}

Tracker create_tracker(
    LINES wire_1,
    LINES wire_2,
    Line line_1,
    Line line_2,
    int index_1,
    int index_2)
{
  Line horizontal, vertical;
  Tracker tracker;

  int diff_1 = wire_1.size() - index_1;
  int diff_2 = wire_2.size() - index_2;

  LINES spliced_1(wire_1.begin(), wire_1.end() - diff_1);
  LINES spliced_2(wire_2.begin(), wire_2.end() - diff_2);

  if (line_1.tail[0] == line_1.head[0])
  {
    vertical = line_1;
    horizontal = line_2;
  }
  else
  {
    horizontal = line_1;
    vertical = line_2;
  }

  copy_lines(tracker.wire_1, spliced_1);
  copy_lines(tracker.wire_2, spliced_2);
  tracker.intersection[0] = vertical.head[0];
  tracker.intersection[1] = horizontal.head[1];

  return tracker;
}

bool check_intersection(Line line_1, Line line_2)
{
  Line horizontal, vertical;
  int min_x, min_y, max_x, max_y;
  bool x_b, y_b;

  if (line_1.tail[0] == 0 && line_1.tail[1] == 0)
  {
    return false;
  }

  if (line_1.tail[0] == line_1.head[0] && line_2.tail[1] == line_2.head[1])
  {
    vertical = line_1;
    horizontal = line_2;
  }
  else if (line_1.tail[1] == line_1.head[1] && line_2.tail[0] == line_2.head[0])
  {
    horizontal = line_1;
    vertical = line_2;
  }
  else
  {
    return false;
  }

  if (horizontal.tail[0] < horizontal.head[0])
  {
    min_x = horizontal.tail[0];
    max_x = horizontal.head[0];
  }
  else
  {
    min_x = horizontal.head[0];
    max_x = horizontal.tail[0];
  }

  if (vertical.tail[1] < vertical.head[1])
  {
    min_y = vertical.tail[1];
    max_y = vertical.head[1];
  }
  else
  {
    min_y = vertical.head[1];
    max_y = vertical.tail[1];
  }

  for (int x = min_x + 1; x < max_x - 1; x++)
  {
    if (x == vertical.head[0])
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
    if (y == horizontal.head[1])
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
  if (result == true)
  {
    string x_str = x_b == true ? "true" : "false";
    string y_str = y_b == true ? "true" : "false";

    cout << "horizontal tail: " << horizontal.tail[0] << ", " << horizontal.tail[1];
    cout << " head: " << horizontal.head[0] << ", " << horizontal.head[1] << endl;
    cout << "vertical tail: " << vertical.tail[0] << ", " << vertical.tail[1];
    cout << " head: " << vertical.head[0] << ", " << vertical.head[1] << endl;

    cout << "x = " << x_str << ", y = " << y_str << endl;
    cout << "result " << result << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  }
  */

  return x_b && y_b;
}

vector<int> get_manhanttain_distances(TRACKERS trackers)
{
  vector<int> distances;
  int x, y;

  for (Tracker tracker : trackers)
  {
    x = abs(0 - tracker.intersection[0]);
    y = abs(0 - tracker.intersection[1]);
    distances.push_back(x + y);
  }

  return distances;
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