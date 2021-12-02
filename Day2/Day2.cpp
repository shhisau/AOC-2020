#include <fstream>
#include <iostream>
#include <sstream>


//
// Created by Cesilia Meyer on 12/2/21.
//
// https://adventofcode.com/2021/day/2

using namespace std;

int main() {
  // Create a file reading object
  int position_part_1 = 0;
  int depth_part_1 = 0;
  string action;
  int count;

  // part 2
  int position_part_2 = 0;
  int depth_part_2 = 0;
  int aim = 0;

  ifstream file( "/Users/cesiliameyer/Development/AOC-2021/Day2/input" );

  if ( !file )  // same as: if (file.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }
  string current_line;
  while ( getline( file, current_line ) )  // same as: while (getline( myfile, line ).good())
  {
    stringstream line_stream( current_line );
    line_stream >> action >> count;

    if( action == "forward")
    {
      position_part_1+=count;
      position_part_2+=count;
      depth_part_2+= (aim * count);
    }
    else if( action == "down")
    {
      // part 1
      depth_part_1+=count;
      // part 2
      aim+=count;
    }
    else if ( action == "up")
    {
      // part 1
      depth_part_1-=count;
      // part 2
      aim-=count;
    }
  }

  cout << "position_part_1 = " << position_part_1 << endl;
  cout << "depth_part_1 = " << depth_part_1 << endl;
  cout << "Multiplication = " << position_part_1 * depth_part_1 << endl;
  cout << "===============================" << endl;
  cout << "position_part_2 = " << position_part_2 << endl;
  cout << "depth_part_2 = " << depth_part_2 << endl;
  cout << "Multiplication = " << position_part_2 * depth_part_2 << endl;
  return 0;
}
