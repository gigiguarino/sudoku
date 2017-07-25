

#include <iostream>
#include <deque>
#include <stdio.h>
using namespace std;


//////////////////////////////////////
// colored text for output
//////////////////////////////////////
#define RED         "\033[31m"
#define CYAN        "\033[36m"
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
// correct board and current board
// for comparison
//////////////////////////////////////
SPOT correct_board_spots[81];
SPOT current_board_spots[81];



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
void print_board(SPOT cursor, SPOT spots[])
{
  cout << "\n\n\n\n";
  cout << "\t ___ ___ ___   ___ ___ ___   ___ ___ ___  \n";
  
  for (int r = 0; r < 9; r++)
  {
    cout << "\t|   |   |   | |   |   |   | |   |   |   |\n";
    cout << "\t";
    
    for (int c = 0; c < 9; c++)
    {
      if (spots[r*9 + c].num == 0)
      {
        if (c == 3 || c == 6)
        {
          cout << "| ";
        }
        
        if (cursor.row == r && cursor.col == c)
        {
          cout << "| " << CYAN << ". " << RESET;
        }
        
        else
        {
          cout << "|   ";
        }
        
      }
      
      else
      {
        if (c == 3 || c == 6)
        {
          cout << "| ";
        }
      
        if (cursor.row == r && cursor.col == c)
        {
          cout << "| " << CYAN << spots[r*9 + c].num << RESET << " ";
        }
        
        else if (!current_board_spots[r*9 + c].valid)
        {
          cout << "| " << RED << spots[r*9 + c].num << RESET << " ";
        }
        
        else
        {
          cout << "| " << spots[r*9 + c].num << " ";
        }
      }
    }
    
    
    cout << "|\n";
    cout << "\t|___|___|___| |___|___|___| |___|___|___|\n";
    
    if ((r+1)%3 == 0 && r != 8)
    {
      cout << "\t ___ ___ ___   ___ ___ ___   ___ ___ ___ \n";
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
  cout << "\t" << "w\t\t- move cursor up\n";
  cout << "\t" << "a\t\t- move cursor left\n";
  cout << "\t" << "s\t\t- move cursor down\n";
  cout << "\t" << "d\t\t- move cursor right\n";
  cout << "\t" << "0\t\t- clear number\n";
  cout << "\t" << "1-9\t\t- place number\n";
  cout << "\t" << "q\t\t- quit\n\n\n";
}

//////////////////////////////////////
// print_spot_info()
// for debugging purposes
//////////////////////////////////////
void print_spot_info(SPOT spots[])
{
  for (int i = 0; i < 81; i++)
  {
    cout << "current_board[" << i << "]:"
         << " r: "  << spots[i].row
         << " c: "  << spots[i].col
         << " n: "  << spots[i].num
         << " v: "  << spots[i].valid << "\n";
  }
}

void print_deque(deque<SPOT> spots)
{
  for (int i = 0; i < spots.size(); i++)
  {
    cout << "deque[" << i << "]:"
         << " r: "  << spots[i].row
         << " c: "  << spots[i].col
         << " n: "  << spots[i].num
         << " v: "  << spots[i].valid << "\n";
  }
}

void print_deque(deque<int> spots)
{
  for (int i = 0; i < spots.size(); i++)
  {
    cout << spots[i] << endl;
  }
}



// randomize the start of the game
// the player chose easy mode
// default
void setup_board_easy()
{
}

// randomize the start of the game
// the player chose medium mode
void setup_board_medium()
{
}

// randomize the start of the game
// the player chose hard mode
void setup_board_hard()
{
}






//////////////////////////////////////
// in_row(spot)
// returns true if there is
// already that number in the row
//////////////////////////////////////
bool in_row(SPOT s, SPOT spots[])
{
  int row = s.row;
  
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
bool in_col(SPOT s, SPOT spots[])
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
bool in_square(SPOT s, SPOT spots[])
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
void check_placement(SPOT spots[])
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









void remove_from_snapshot(SPOT s, deque<SPOT> &d_s)
{
  for (int i = 0; i < d_s.size(); i++)
  {
    if (d_s[i] == s)
    {
      d_s.erase(d_s.begin() + i);
      return;
    }
  }
  
  cout << "error" << endl;
  return;
}


//////////////////////////////////////
// generate_correct()
// generate correct sudoku board
//////////////////////////////////////
void generate_correct(SPOT cursor)
{
  deque<int> spots_to_place; // grab randomly and erase
  deque<SPOT> spot_stack; // push front / pop front
  deque<SPOT> left_to_try;
  deque<SPOT> left_to_try_snapshot;
  
  SPOT current;
  for (int r = 0; r < 9; r++)
  {
    for (int c = 0; c < 9; c++)
    {
      current.row = r;
      current.col = c;
      current.num = 0;
      current.valid = true;
      left_to_try.push_back(current);
      left_to_try_snapshot.push_back(current);
    }
  }
  
  for (int i = 1; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      spots_to_place.push_back(i);
    }
  }
  
  SPOT current_spot;
  int current_num;
  int random;
  bool placed;
  
  while (!spots_to_place.empty())
  {
    cout << endl << endl << endl << endl << endl;
    
    current_num = spots_to_place.front();
    left_to_try = left_to_try_snapshot;
    
    placed = false;
    
    while (!placed)
    {
      //print_deque(left_to_try);
      random = rand() % left_to_try.size();
      current_spot = left_to_try[random];
      current_spot.num = current_num;
      
      left_to_try.erase(left_to_try.begin()+random);
      
      if (!in_row(current_spot, correct_board_spots) &&
          !in_col(current_spot, correct_board_spots) &&
          !in_square(current_spot, correct_board_spots))
      {
        placed = true;
        spots_to_place.pop_front();
        spot_stack.push_front(current_spot);
        correct_board_spots[current_spot.row*9 + current_spot.col] = current_spot;
        print_spot(current_spot);
        remove_from_snapshot(current_spot, left_to_try_snapshot);
      }
      
      else
      {
        if (left_to_try.empty())
        {
          cout << "HERE" << endl;
          left_to_try_snapshot.push_front(spot_stack.front());
          correct_board_spots[spot_stack.front().row*9 + spot_stack.front().col].num = 0;
          spots_to_place.push_front(spot_stack.front().num);
          spot_stack.pop_front();
          placed = true;
        }
      }
    }
  }
  
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



int main(void)
{
  // initialize cursor
  SPOT cursor;
  cursor.row    = 0;
  cursor.col    = 0;
  cursor.num    = 0;
  cursor.valid  = 1;
  
  for (int i = 0; i < 81; i++)
  {
    correct_board_spots[i].row    = i/9;
    correct_board_spots[i].col    = i%9;
    correct_board_spots[i].num    = 0;
    correct_board_spots[i].valid  = true;
  }
  
  generate_correct(cursor);
  print_board(cursor, correct_board_spots);
  print_spot_info(correct_board_spots);
}





/*


//////////////////////////////////////
// main
//////////////////////////////////////
int main(void)
{
  bool quit = false;
  char input;
  
  // initialize cursor
  SPOT cursor;
  cursor.row    = 0;
  cursor.col    = 0;
  cursor.num    = 0;
  cursor.valid  = 1;
  
  // initialize all spots on the board to be nothing to begin with
  for (int i = 0; i < 81; i++)
  {
    current_board_spots[i].row    = i/9;
    current_board_spots[i].col    = i%9;
    current_board_spots[i].num    = 0;
    current_board_spots[i].valid  = true;
  }
  
  print_board(cursor, current_board_spots);
  print_commands();

  while (!quit)
  {
    clear();
    check_placement(current_board_spots);
    print_board(cursor, current_board_spots);
    print_commands();
    
    // arrow key check
    // set terminal to raw mode?
    system("stty raw");
    input = getchar();
    // reset terminal to normal
    system("stty cooked");
      
    if (input == 'q')
    {
      quit = true;
    }
    
    else if (valid_input(input))
    {
      handle_input(input, cursor);
    }
  }

  return 0;
}
*/
