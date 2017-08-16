

#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <deque>
#include <vector>
#include <stdio.h>
using namespace std;


//////////////////////////////////////
// colored text for output
//////////////////////////////////////
#define RED         "\033[31m"
#define CYAN        "\033[36m"
#define YELLOW      "\033[33m"
#define MAGENTA     "\033[35m"
#define GREEN       "\033[32m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define RESET       "\033[0m"


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
vector<SPOT> current_board_spots;
vector<SPOT> correct_board_spots;
vector<SPOT> start_board_spots;


//////////////////////////////////////
// print spot
//////////////////////////////////////
void print_spot(SPOT s)
{
  cout << "-----\n";
  cout << "r=" << s.row   << "\n";
  cout << "c=" << s.col   << "\n";
  cout << "n=" << s.num   << "\n";
  cout << "v=" << s.valid << "\n";
  cout << "-----\n";
}








//////////////////////////////////////
// clear()
// clear the screen
//////////////////////////////////////
void clear()
{
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  return;
}

//////////////////////////////////////
// print_board(cursor)
// print the current board
//////////////////////////////////////
void print_board(SPOT cursor, vector<SPOT> spots)
{
  cout <<"\t\t      --" << YELLOW << " SUDOKU " << RESET << "--\n\n";
  cout << GREEN << "\t ___ ___ ___   ___ ___ ___   ___ ___ ___  \n" << RESET;
  
  for (int r = 0; r < 9; r++)
  {
    cout << GREEN << "\t|   |   |   | |   |   |   | |   |   |   |\n" << RESET;
    cout << "\t";
    
    for (int c = 0; c < 9; c++)
    {
      if (spots[r*9 + c].num == 0)
      {
        if (c == 3 || c == 6)
        {
          cout << GREEN << "| " << RESET;
        }
        
        if (cursor.row == r && cursor.col == c)
        {
          cout << GREEN << "| "<< RESET << BOLDYELLOW << "+ " << RESET;
        }
        
        else
        {
          cout << GREEN << "|   " << RESET;
        }
        
      }
      
      else
      {
        if (c == 3 || c == 6)
        {
          cout << GREEN << "| " << RESET;
        }
      
        if (cursor.row == r && cursor.col == c)
        {
          cout << GREEN << "| " << RESET << BOLDYELLOW << spots[r*9 + c].num << RESET << " ";
        }
        
        else if (!spots[r*9 + c].valid)
        {
          cout << GREEN << "| " << RESET << RED << spots[r*9 + c].num << RESET << " ";
        }
        
        else
        {
          cout << GREEN << "| " << RESET << spots[r*9 + c].num << " ";
        }
      }
    }
    
    
    cout << GREEN << "|\n" << RESET;
    cout << GREEN << "\t|___|___|___| |___|___|___| |___|___|___|\n" << RESET;
    
    if ((r+1)%3 == 0 && r != 8)
    {
      cout << GREEN << "\t ___ ___ ___   ___ ___ ___   ___ ___ ___ \n" << RESET;
    }
  }
  
  cout << "\n\n";
}





//////////////////////////////////////
// print_commands()
// prints commands for the user
//////////////////////////////////////
void print_commands()
{
  cout << "\t   " << "w\t\t- move cursor up\n";
  cout << "\t   " << "a\t\t- move cursor left\n";
  cout << "\t   " << "s\t\t- move cursor down\n";
  cout << "\t   " << "d\t\t- move cursor right\n";
  cout << "\t   " << "0\t\t- clear number\n";
  cout << "\t   " << "1-9\t\t- place number\n";
  cout << "\t   " << "r\t\t- reset\n";
  cout << "\t   " << "n\t\t- new\n";
  cout << "\t   " << "q\t\t- quit\n\n\n";
}

//////////////////////////////////////
// print_spot_info()
// for debugging purposes
//////////////////////////////////////
void print_spot_info(vector<SPOT> spots)
{
  for (int i = 0; i < 81; i++)
  {
    cout << "current_board[" << i << "]:"
         << " r: "  << spots[i].row
         << " c: "  << spots[i].col
         << " n: "  << spots[i].num
         << " v: "  << spots[i].valid << "\n";
  }
  
  cout << "---------" << endl;
}

//////////////////////////////////////
// print_vec(spots, name)
// for debugging purposes
//////////////////////////////////////
void print_vec(vector<SPOT> spots, string name)
{
  for (int i = 0; i < spots.size(); i++)
  {
    cout <<  name << "[" << i << "]:"
         << " r: "  << spots[i].row
         << " c: "  << spots[i].col
         << " n: "  << spots[i].num
         << " v: "  << spots[i].valid << "\n";
  }
  
  cout << "---------" << endl;
}



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
// check_placement()
// loops through spots
// and checks validity
//////////////////////////////////////
void check_placement(vector<SPOT> &spots)
{
  SPOT s;
  
  for (int i = 0; i < 81; i++)
  {
    s = current_board_spots[i];
    if (s.num != 0)
    {
      if (in_row(s, spots) || in_col(s, spots) || in_square(s, spots))
      {
        spots[i].valid = false;
      }
      
      else
      {
        spots[i].valid = true;
      }
    }
  }
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
// valid_input(input)
// check the keyboard entry
//////////////////////////////////////
bool valid_input(char input)
{
  if (input == '0' || input == '1' || input == '2' || input == '3' ||
      input == '4' || input == '5' || input == '6' || input == '7' ||
      input == '8' || input == '9' || input == 'w' || input == 'a' ||
      input == 's' || input == 'd')
  {
    return true;
  }
  
  else
  {
    return false;
  }
}

//////////////////////////////////////
// handle_input(input, cursor)
// handle the keyboard press
//////////////////////////////////////
void handle_input(char input, SPOT &cursor)
{
  SPOT placed;
  
  if (input == 'w')
  {
    // up arrow
    if (cursor.row != 0)
    {
      cursor.row -= 1;
    }
  }
  
  else if (input == 'a')
  {
    // left arrow
    if (cursor.col != 0)
    {
      cursor.col -= 1;
    }
  }
  
  else if (input == 's')
  {
    // down arrow
    if (cursor.row != 8)
    {
      cursor.row += 1;
    }
  }
  
  else if (input == 'd')
  {
    // right arrow
    if (cursor.col != 8)
    {
      cursor.col += 1;
    }
  }
  
  else
  {
    placed.row = cursor.row;
    placed.col = cursor.col;
    placed.num = input - '0';
    placed.valid = true;
    current_board_spots[placed.row*9 + placed.col] = placed;
  }
  
  return;
}










//////////////////////////////////////
// make sure each square has at
// least 2 spots filled in
// also no unreasonably full squares
//////////////////////////////////////
void check(int beg_row, int end_row, int beg_col,
  int end_col, vector<SPOT> &spots)
{
  int num_spots = 0;
  for (int r = beg_row; r <= end_row; r++)
  {
    for (int c = beg_col; c <= end_col; c++)
    {
      if (spots[r*9 + c].num != 0)
      {
        num_spots++;
      }
    }
  }
  
  if (num_spots < 2)
  {
    spots[beg_row*9 + beg_col].num = correct_board_spots[beg_row*9 + beg_col].num;
    spots[end_row*9 + end_col].num = correct_board_spots[end_row*9 + end_col].num;
  }
  
  else if (num_spots >= 7)
  {
    spots[beg_row*9 + beg_col].num = 0;
    spots[end_row*9 + end_col].num = 0;
    spots[end_row*9 + beg_col].num = 0;
  }
}


//////////////////////////////////////
// remove_spots(spots)
// removes numbers off of the board
//////////////////////////////////////
void remove_spots(vector<SPOT> &spots, int num_spots)
{
  int num;
  
  // make a number of the spots null or 0
  for (int i = 0; i < num_spots; i++)
  {
    num = rand() % spots.size();
    if (spots[num].num != 0)
    {
      spots[num].num = 0;
    }
    else
    {
      i--;
    }
  }
  
  // make sure every square at least has two
  // and less than 7
  check(0,2,0,2, spots);
  check(0,2,3,5, spots);
  check(0,2,6,8, spots);
  check(3,5,0,2, spots);
  check(3,5,3,5, spots);
  check(3,5,6,8, spots);
  check(6,8,0,2, spots);
  check(6,8,3,5, spots);
  check(6,8,6,8, spots);
}




//////////////////////////////////////
// check_if_done()
// returns true if board is complete
//////////////////////////////////////
bool check_if_done()
{
  for (int i = 0; i < 81; i++)
  {
    if (current_board_spots[i].num == 0 || !current_board_spots[i].valid)
    {
      return false;
    }
  }
  
  return true;
}




void start()
{
  srand(time(0));
  
  cout << RESET << endl;

  // initialize cursor
  SPOT cursor;
  SPOT current_spot;
  cursor.row    = 0;
  cursor.col    = 0;
  cursor.num    = 0;
  cursor.valid  = 1;
  

  bool quit = false;
  bool new_board = true;
  char input;

  while (!quit)
  {
    if (new_board)
    {
      clear();
      current_board_spots.clear();
      correct_board_spots.clear();
      
      for (int i = 0; i < 81; i++)
      {
        current_spot.row    = i/9;
        current_spot.col    = i%9;
        current_spot.num    = 0;
        current_spot.valid  = true;
        correct_board_spots.push_back(current_spot);
        current_board_spots.push_back(current_spot);
      }

      generate_correct();
      current_board_spots = correct_board_spots;
      remove_spots(current_board_spots, 45);
      start_board_spots = current_board_spots;
      print_board(cursor, current_board_spots);
      print_commands();
      new_board = false;
    }
    
    else
    {
      clear();
      check_placement(current_board_spots);
      print_board(cursor, current_board_spots);
      print_commands();
      quit = check_if_done();
    }
    
    // input check
    // set terminal to raw mode?
    system("stty raw");
    input = getchar();
    // reset terminal to normal
    system("stty cooked");
      
    if (input == 'q')
    {
      quit = true;
    }
    
    else if (input == 'r')
    {
      current_board_spots = start_board_spots;
    }
    
    else if (input == 'n')
    {
      new_board = true;
    }
    
    else if (valid_input(input))
    {
      handle_input(input, cursor);
    }
  }

  return;
}

