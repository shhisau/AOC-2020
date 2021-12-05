#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

//
// Created by Cesilia Meyer on 12/3/21.
//

using namespace std;

// returns the sum of ones per bit in a file
vector<int> add_all_vectors(vector<vector<int>> data)
{
  vector<int> sum_of_ones(data[0].size(), 0);
  
  // iterate through each vector
  for( vector<int> vector: data){
    // iterate through each number in the vector
    int index = 0;
    for( int value: vector){
      cout << value << endl;
      sum_of_ones[index]+=value;
      index++;
    }
  }
  return sum_of_ones;
}

vector<string> common_uncommon(vector<int> sum_of_ones, int lines)
{
  // figure out common number
  vector<string> result;
  string gamma_rate;
  string epsilon_rate;
  for( auto index: sum_of_ones) {
    auto a = ((float)lines/2);
    if(index >= ((float)lines/2)){
      gamma_rate+='1';
      epsilon_rate+='0';
    } else {
      gamma_rate+='0';
      epsilon_rate+='1';
    }
  }
  result.push_back(gamma_rate);
  result.push_back(epsilon_rate);
  return result;
}

// is this even worth it?!?!?!?
vector<vector<int>> remove_common_number(vector<vector<int>> data, int index, string common_number, bool uncommon)
{
  vector<vector<int>> result;

  // iterate through every line
  for( auto vector: data){
    if(vector.at(index) == (int)common_number[index] -'0')
    {
      result.push_back(vector);
    }
  }

  // will this work? fuck
  if( result.size() > 1){
    auto sum = add_all_vectors(result);
    auto common = common_uncommon(sum, result.size());
    result = remove_common_number( result, index+1, uncommon?common[1]:common[0], uncommon);
  }
  
  return result;
}

int main() {

  vector<int> sum_of_ones(12, 0); // size 12 with values of 0
  vector<vector<int>> data;
  ifstream file( "/Users/cesiliameyer/Development/AOC-2021/Day3/input" );

  if ( !file )  // same as: if (file.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }

  uint number_of_lines = 0;
  string current_line;
  
  while ( getline( file, current_line ) )  // same as: while (getline( myfile, line ).good())
  {
    int index=0;
    data.push_back(sum_of_ones); // add a vector
    for ( const char &c: current_line ) {
      auto value = c - '0'; // convert char to an int
      sum_of_ones[index]+=value; // add value
      data[number_of_lines][index] = value; // store all data...do i need to?
      index++;
    }
    ++number_of_lines; // keep track of how many lines are read
  }

  // figure out common number
  string gamma_rate;
  string epsilon_rate;
  for( auto index: sum_of_ones) {
    if(index > ((float)number_of_lines/2)){
      gamma_rate+='1';
      epsilon_rate+='0';
    } else {
      gamma_rate+='0';
      epsilon_rate+='1';
    }
  }

  auto gamma_dec = stoi(gamma_rate, 0, 2);
  unsigned long n = std::bitset<8>(gamma_rate).to_ulong();
  auto epsilon_dec = stoi(epsilon_rate, 0, 2);
  cout << "Gamma rate = " << gamma_dec << endl;
  cout << "Epsilon rate = " << epsilon_dec << endl;
  cout << "Part 1 = " << gamma_dec * epsilon_dec << endl;

  // part 2, use the sums_of_ones and re read the file?
  file.clear();  // clear fail and eof bits
  file.seekg(0, std::ios::beg);

  // oxygen generator rating
  // most common number in current bit position and only keep data with commong number in that position
  // if no commong number, 1 will be the most common

  auto sum = add_all_vectors(data);
  auto stuff = common_uncommon(sum, data.size());

  // new vector with index common numbers removed
  auto oxygen_rating = remove_common_number( data, 0 , stuff[0], false);

  auto more_stuff = common_uncommon(sum, data.size());
  auto co2_rating = remove_common_number(data, 0, more_stuff[1], true);

  std::stringstream result;
  std::copy(oxygen_rating[0].begin(), oxygen_rating[0].end(), std::ostream_iterator<int>(result, ""));
  auto y = stoi(result.str(), 0, 2);

  result.str("");
  std::copy(co2_rating[0].begin(), co2_rating[0].end(), std::ostream_iterator<int>(result, ""));
  auto z = stoi(result.str(), 0, 2);
  cout << "Part 2 answer = " << y*z << endl;

  return 0;
}