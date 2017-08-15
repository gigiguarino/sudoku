

#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <deque>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;



//////////////////////////////////////
// SPOT struct
//////////////////////////////////////
struct SPOT
{
  int row;
  int col;
  int num;
  bool valid;
  bool operator== (SPOT &s)
  {
    return (s.row == row && s.col == col);
  }
  bool operator!= (SPOT &s)
  {
    return (s.row != row || s.col != col);
  }
};


//////////////////////////////////////
// correct board and current board
// for comparison
//////////////////////////////////////
vector<SPOT> correct_board_spots;
vector<string> corrects;


//////////////////////////////////////
// in_row(spot)
// returns true if there is
// already that number in the row
//////////////////////////////////////
bool in_row(SPOT s, vector<SPOT> spots)
{
  for (int c = 0; c < 9; c++)
  {
    if ((spots[s.row*9 + c].num == s.num) &&
        (spots[s.row*9 + c] != s))
    {
      return true;
    }
  }
  
  return false;
}

//////////////////////////////////////
// in_col(spot)
// returns true if there is
// already that number in the col
//////////////////////////////////////
bool in_col(SPOT s, vector<SPOT> spots)
{
  int col = s.col;
  
  for (int r = 0; r < 9; r++)
  {
    if ((spots[r*9 + col].num == s.num) &&
        (spots[r*9 + col] != s))
    {
      return true;
    }
  }
  
  return false;
}

//////////////////////////////////////
// in_square(spot)
// returns true if there is already
// that number in the square
//////////////////////////////////////
bool in_square(SPOT s, vector<SPOT> spots)
{
  int row = s.row;
  int col = s.col;
  
  int small_r = 0;
  int big_r   = 0;
  int small_c = 0;
  int big_c   = 0;
  
  // row checks
  if (row >= 0 && row <= 2)
  {
    small_r = 0;
    big_r   = 2;
  }
  
  else if (row >= 3 && row <= 5)
  {
    small_r = 3;
    big_r   = 5;
  }
  
  else if (row >= 6 && row <= 8)
  {
    small_r = 6;
    big_r   = 8;
  }
  
  else
  {
    cout << "in_square error: invalid row\n";
    return false;
  }
  //////////////
  
  // col checks
  if (col >= 0 && col <= 2)
  {
    small_c = 0;
    big_c   = 2;
  }
  
  else if (col >= 3 && col <= 5)
  {
    small_c = 3;
    big_c   = 5;
  }
  
  else if (col >= 6 && col <= 8)
  {
    small_c = 6;
    big_c   = 8;
  }
  
  else
  {
    cout << "in_square error: invalid col\n";
    return false;
  }
  //////////////
  
  for (int r = small_r; r <= big_r; r++)
  {
    for (int c = small_c; c <= big_c; c++)
    {
      if ((spots[r*9 + c].num == s.num) &&
          (spots[r*9 + c] != s))
      {
        return true;
      }
    }
  }
    
  return false;
}

//////////////////////////////////////
// make_correct_string()
// creates the string for the file
//////////////////////////////////////
string make_correct_string()
{
  string correct_string = "";
  for (int i = 0; i < 81; i++)
  {
    correct_string += to_string(correct_board_spots[i].num);
  }

  return correct_string;
}


//////////////////////////////////////
// struct to hold backtraces
//////////////////////////////////////
struct BT
{
  int row;
  int col;
  int num;
  vector<int> num_to_try;
};

vector<BT> backtrack_vec;

//////////////////////////////////////
// print_bt()
// for debugging
//////////////////////////////////////
void print_bt()
{
  for (int i = 0; i < backtrack_vec.size(); i++)
  {
    cout << "backtrack[" << i << "]: "
         << "r:" << backtrack_vec[i].row << " "
         << "c:" << backtrack_vec[i].col << " "
         << "n:" << backtrack_vec[i].num << endl;
  }
}

//////////////////////////////////////
// generate_correct()
// generate correct sudoku board
//////////////////////////////////////
void generate_correct()
{
  random_device rd;
  mt19937 g(rd());

  bool done = false;
  bool go_back = false;
  bool placed = false;
  
  vector<int> numbers;
  vector<int> current_numbers;
  
  SPOT current_spot;
  BT current_bt;
  vector<SPOT> current_board;

  current_board = correct_board_spots;

  // so we can reset
  numbers.push_back(1);
  numbers.push_back(2);
  numbers.push_back(3);
  numbers.push_back(4);
  numbers.push_back(5);
  numbers.push_back(6);
  numbers.push_back(7);
  numbers.push_back(8);
  numbers.push_back(9);
  
  // fill in first row with 1-9 randomly placed
  // to speed up generation of solution
  current_numbers = numbers;
  shuffle(current_numbers.begin(), current_numbers.end(), g);
  int i = 0;
  while (!current_numbers.empty())
  {
    current_board[i].num = current_numbers.back();
    current_numbers.pop_back();
    i++;
  }

  // get new numbers and shuffle
  // starting at top of second row try first
  int row = 1;
  int col = 0;
  while (!done)
  {
    if (go_back)
    {
      // backtrack
      current_bt = backtrack_vec.back();
      backtrack_vec.pop_back();
      current_spot.row = current_bt.row;
      current_spot.col = current_bt.col;
      current_numbers = current_bt.num_to_try;
      shuffle(current_numbers.begin(), current_numbers.end(), g);
      row = current_spot.row;
      col = current_spot.col;
      current_board[row*9 + col].num = 0;
      placed = false;
      go_back = false;
    }
    
    else
    {
      current_numbers = numbers;
      shuffle(current_numbers.begin(), current_numbers.end(), g);
      current_spot.row = row;
      current_spot.col = col;
      placed = false;
    }
    
    // try all of remaining numbers for validity
    while (!placed && !current_numbers.empty())
    {
      current_spot.num = current_numbers.back();
      current_numbers.pop_back();
      
      if (!in_row(current_spot, current_board) &&
          !in_col(current_spot, current_board) &&
          !in_square(current_spot, current_board))
      {
        current_bt.row = current_spot.row;
        current_bt.col = current_spot.col;
        current_bt.num = current_spot.num;
        current_bt.num_to_try = current_numbers;
        backtrack_vec.push_back(current_bt);
        current_board[row*9 + col].num = current_spot.num;
        placed = true;
      }
    }
    
    // valid spot
    if (placed)
    {
      if (row == 8 && col == 8)
      {
        done = true;
      }
      
      else if (col == 8)
      {
        row++;
        col = 0;
      }
      
      else
      {
        col++;
      }
    }
    
    // backtrack
    if (!placed && current_numbers.empty())
    {
      go_back = true;
    }
  }
  
  correct_board_spots = current_board;
}


//////////////////////////////////////
// make_file()
// prints out all the strings
//////////////////////////////////////
void make_file()
{
  string current;
  while(!corrects.empty())
  {
    current = corrects.back();
    corrects.pop_back();
    cout << current << endl;
  }
}




//////////////////////////////////////
// already_made(string)
// returns true if this string exists
// already
// false otherwise
//////////////////////////////////////
bool already_made(string correct)
{
  for (int i = 0; i < corrects.size(); i++)
  {
    if (correct == corrects[i])
    {
      return true;
    }
  }
  return false;
}





//////////////////////////////////////
// start(num)
//////////////////////////////////////
void start(int num)
{
  srand(time(0));
  SPOT current_spot;
  
  for (int j = 0; j < num; j++)
  {
    correct_board_spots.clear();
      
    for (int i = 0; i < 81; i++)
    {
      current_spot.row    = i/9;
      current_spot.col    = i%9;
      current_spot.num    = 0;
      current_spot.valid  = true;
      correct_board_spots.push_back(current_spot);
    }

    generate_correct();
    string correct_string = make_correct_string();

    if (already_made(correct_string))
    {
      j--;
    }
    else
    {
      corrects.push_back(correct_string);
    }
  }
}





//////////////////////////////////////
// main(number of boards)
//////////////////////////////////////
int main(int argc, char *argv[])
{
  int num = atoi(argv[1]);
  start(num);
  make_file();
  return 0;
}

