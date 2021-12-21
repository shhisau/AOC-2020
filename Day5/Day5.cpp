#include <fstream>
#include <vector>
#include <iostream>
#include <map> // does it matter?

#include <cstdio>
#include <cstdlib>

//
// Created by Cesilia Meyer on 12/17/21.
//

using namespace std;
using matrix = vector<vector<int>>; // do i want to use this??

struct Point {
    int x;
    int y;
};

inline bool operator<(const Point& p1, const Point& p2) {
    if (p1.x != p2.x) {
        return p1.x < p2.x;
    } else {
        return p1.y < p2.y;
    }
}

int main() {
  ifstream file( "/Users/cesiliameyer/Development/AOC-2021/Day5/input" );

  if ( !file )  // same as: if (myfile.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }

  map<Point, int> holiest_matrix; // going to use a map cause i only want to keep track of relevant data
  for ( string line; getline( file, line ); ) // Read one line at a time
  {
    // guess this works...
    int x1, x2, y1, y2;
    sscanf (line.c_str(),"%d %*c %d %*s %d %*c %d",&x1, &y1, &x2, &y2);
    if( (x1 != x2) && (y1 != y2) )
    {
      continue;
    }

    cout << "we have a line" << endl;
    // do stuff, add to grid
    if( x1 == x2 )
    {
      // line on x
      if(y2>y1)
      {
        for(int i=y1; i<=y2; i++)
        {
          Point point{x1, i};
          holiest_matrix[point] += 1;
        }
      }
      else
      {
        //y2 < y1
        for(int i=y2; i<=y1; i++)
        {
          Point point{x1, i};
          holiest_matrix[point] += 1;
        }
      }
    }
    else
    {
      // line on y
      if(x2>x1)
      {
        for(int i=x1; i<=x2; i++)
        {
          Point point{i, y1};
          holiest_matrix[point] += 1;
        }
      }
      else
      {
        //x2 < x1
        for(int i=x2; i<=x1; i++)
        {
          Point point{i, y1};
          holiest_matrix[point] += 1;
        }
      }
    }
  }

  // read holiest matrix and check for more than 1 
  uint horizontal_vertical_overlaps = 0;
  for(auto kv: holiest_matrix)
  {
    if(kv.second > 1)
    {
      horizontal_vertical_overlaps += 1;
    } 
  }
  cout << "Part 1: " << horizontal_vertical_overlaps << endl;

  // path matrix size of max value x max value, how to store idk
  // read in coordinates and check if x1 and x2 or y1 and y2 are equal


  return 0;
}