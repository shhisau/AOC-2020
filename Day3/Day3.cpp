#include <fstream>
#include <iostream>
#include <vector>

//
// Created by Cesilia Meyer on 12/3/21.
//

using namespace std;


int main() {

  int oxygen_rating = 0;
  int co2_rating = 0;

  uint number_of_lines = 0;
  vector<int> sum_of_ones(12, 0); // size 12 with values of 0
  ifstream file( "/Users/cesiliameyer/Development/AOC-2021/Day3/input" );

  if ( !file )  // same as: if (file.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }
  string current_line;
  while ( getline( file, current_line ) )  // same as: while (getline( myfile, line ).good())
  {
    ++number_of_lines; // keep track of how many lines are read
  
    int index=0;
    for ( const char &c: current_line ) {
      auto value = c - '0'; // convert char to an int
      sum_of_ones[index]+=value; // add value
      index++;
    }
  }

  // figure out common number
 string gamma_rate;
 string epsilon_rate;
  for( auto index: sum_of_ones) {
    if(index > (number_of_lines/2)){
      gamma_rate+='1';
      epsilon_rate+='0';
    } else {
      gamma_rate+='0';
      epsilon_rate+='1';
    }
  }
  auto gamma_dec = stoi(gamma_rate, 0, 2);
  auto epsilon_dec = stoi(epsilon_rate, 0, 2);
  cout << "Gamma rate = " << gamma_dec << endl;
  cout << "Epsilon rate = " << epsilon_dec << endl;
  cout << "Part 1 = " << gamma_dec * epsilon_dec << endl;
  return 0;
}
