#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>

using namespace std;


struct board{
  vector<vector<int>> lines;
  vector<vector<bool>> chosen; 
  vector<int> sum_unmarked;
};

int main() {
  ifstream file( "/Users/cesiliameyer/Development/AOC-2021/Day4/input" );

  if ( !file )  // same as: if (file.good())
  {
    cout << "Can't open file" << endl;
    return -1;
  }

  // ==================================================================
  // get chosen bingo numbers first
  // ==================================================================

  vector<int> bingo_numbers; // vectors call new, ie store in heap?
  string current_line;

  {
    if(getline(file, current_line))
    {
      // read and store individual numbers
      stringstream ss(current_line);
      std::string number;
      while( getline(ss,number,',') )
      {
        bingo_numbers.push_back(stoi(number));
      }
    }
  }

  // get each board
  // store all possible combinations of a board in a vector of vectors?
  // each vector has a count of how many numbers have been called,
  // if a vector has mroe than one of a called number how handle? 
  // each time check if a vector has more than 4 counts.....if so which board does
  // it belong to cause its the winner?

  // or should i remove elements as they are called, and if a vector is empty it means
  // that board has won?

  // vector with all boards in text file
  vector<board> boards;

  {
    board current_board;
    int index = -1;
    while( getline(file, current_line)){
      // new board, push empty board and read stuffs
      if(current_line.empty())
      {
        boards.emplace_back(); // create an object of type board, with no arguments 
        index++;
        continue;   
      }
      else
      {
        // we need to add each line as a vector
        vector<int> line;
        stringstream ss(current_line);
        int number; 
        while(ss >> number)
        {
          line.push_back(number);
        }
        vector<bool> shit(line.size(), false);
        boards[index].lines.push_back(line);
        boards[index].chosen.push_back(shit);
      }
    }
  }

  // ==================================================================
  // flip boards and resize
  // ==================================================================
  {
    // vector<vector<int>> flipped_board(boards[0].size(), vector<int>(boards[0][0].size()));
    vector<vector<int>> flipped_board = boards[0].lines; // using to initalize 
    for(int board=0; board<boards.size();board++)
    {
      for(int x=0; x<boards[board].lines.size(); x++)
      {
        for(int y=0; y<boards[board].lines.size(); y++) // figure out actual logic mam
        {
          flipped_board[x][y] = boards[board].lines[y][x];
        }
      }
      boards[board].lines.insert(boards[board].lines.end(), flipped_board.begin(), flipped_board.end());
      // boards[board].chosen.resize(boards[board].lines.size(), false);
      boards[board].sum_unmarked.resize(boards[board].lines.size(), 0);
    }

    // sum shit up, can i do it some where else?
    for(auto &board: boards)
    {
      for(int i=0;i<board.lines.size(); i++) 
      {
        board.sum_unmarked[i] = accumulate(board.lines[i].begin(), board.lines[i].end(), 0);
      }
    }
  }


  // ==================================================================
  // logic to check for bingo
  // ==================================================================

  // read first bingo number 
  for(auto bingo: bingo_numbers)
  {
    for(int board=0; board<boards.size();board++)
    {
      for(int line=0; line < boards[board].lines.size(); line++)
      {
        auto negative = count(boards[board].lines[line].begin(), boards[board].lines[line].end(), bingo) * bingo;
        boards[board].sum_unmarked[line] -= count(boards[board].lines[line].begin(), boards[board].lines[line].end(), bingo) * bingo;
        if(boards[board].sum_unmarked[line] <= 0)
        {
          auto answer = bingo * accumulate(boards[board].sum_unmarked.begin(), boards[board].sum_unmarked.begin() + 5 , 0);
          cout << "Board won, answer: " << answer << endl;
          if(boards.size() == 1)
          {
            cout << "Last one" << endl;
          }
          boards.erase(boards.begin() + board);
          board--;
          break;
        }
      }
    }
  }

  return 0;
}