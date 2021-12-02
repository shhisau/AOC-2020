#include <fstream>
#include <vector>
#include <iostream>

//
// Created by Cesilia Meyer on 12/1/21.
//

using namespace std;

void part_one( ifstream &myfile )
{
  uint increased_count = 0;
  uint decreased_count = 0;
  string line;
  string previous_line;

  // file is good, lets read each line
  while ( getline( myfile, line ) )  // same as: while (getline( myfile, line ).good())
  {
    if ( previous_line.empty() )
    {
      cout << "(N/A - no previous measurement)" << line << endl;
    }
    else 
    {
      // we have a previous line
      // convert strings to ints and subtract
      int current = stoi( line );
      int previous = stoi( previous_line );

      // cout << current << " - " << previous << "= " << current - previous << endl;
      if( ( current - previous ) > 0 )
      {
        increased_count++;
      } 
      else 
      {
        decreased_count++;
      }
    }
    previous_line = line;
  }
  
  cout << "increased count = " << increased_count << endl;
  cout << "decreased count = " << decreased_count << endl;
}

void part_two( ifstream &myfile)
{
  string current_line;
  string prev_prev;
  string prev;

  uint increased_count = 0;
  uint decreased_count = 0;
  int previous_sum = 0;
  int current_sum = 0;
  // file is good, lets read each line
  while ( getline( myfile, current_line ) )  // same as: while (getline( myfile, line ).good())
  {
    if ( prev.empty() )
    {
      cout << "Just read the first number" << endl;
      prev = current_line;
      continue;
    }
    else if (prev_prev.empty())
    {
      /* code */
      cout << "Read the second number" << endl;
      prev_prev = prev;
      prev = current_line;
      continue;
    }
    else
    {
      // we have 3 numbers
      // convert strings to ints and subtract
      current_sum = stoi( current_line ) + stoi( prev ) + stoi( prev_prev );
      if( previous_sum == 0 )
      {
        cout << "(N/A - no previous sum)" << endl;
      }
      else
      {
        // cout << current_sum << " - " << previous_sum << "= " << current_sum - previous_sum << endl;
        if( ( current_sum - previous_sum ) > 0 )
        {
          increased_count++;
        } 
        else 
        {
          decreased_count++;
        }
      }
    }

    previous_sum = current_sum;
    // move strings by one
    prev_prev = prev;
    prev = current_line;
  }

  cout << "increased count = " << increased_count << endl;
  cout << "decreased count = " << decreased_count << endl;
}

int main() {
  ifstream myfile( "/Users/cesiliameyer/Development/AOC-2021/Day1/input" );

  if ( !myfile )  // same as: if (myfile.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }

  part_one( myfile );
  myfile.clear();  // clear fail and eof bits
  myfile.seekg(0, std::ios::beg);
  part_two( myfile );

  myfile.close();

  return 0;
}