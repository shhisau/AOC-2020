#include <iostream>
#include <fstream>

using namespace std;

int main() {
  ifstream file( "/Users/cesiliameyer/Development/AOC-2021/Day4/sample" );

  if ( !file )  // same as: if (file.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }

  string current_line;
  while( getline(file, current_line)){
      
  }
  return 0;
}