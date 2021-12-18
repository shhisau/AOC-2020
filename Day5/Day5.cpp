#include <fstream>
#include <vector>
#include <iostream>

//
// Created by Cesilia Meyer on 12/17/21.
//

using namespace std;

int main() {
  ifstream myfile( "/Users/cesiliameyer/Development/AOC-2021/Day5/sample" );

  if ( !myfile )  // same as: if (myfile.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }

  return 0;
}