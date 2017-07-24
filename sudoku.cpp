

#include <iostream>
#include <stdio.h>
using namespace std;

#define RED         "\033[31m"
#define CYAN        "\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define RESET       "\033[0m"

// 0 indexed
struct SPOT
{
  int row;
  int col;
  int num;
  bool valid;
};

SPOT correct_board_spots[81];
SPOT current_board_spots[81];

// clear the screen
void clear()
{
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  return;
}

// print the current board
void print_board(SPOT cursor)
{
  cout << "\n\n\n\n";
  cout << "\t ___ ___ ___   ___ ___ ___   ___ ___ ___  \n";
  
  for (int r = 0; r < 9; r++)
  {
    cout << "\t|   |   |   | |   |   |   | |   |   |   |\n";
    cout << "\t";
    
    for (int c = 0; c < 9; c++)
    {
      if (current_board_spots[r*9 + c].num == 0)
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
          cout << "| " << CYAN << current_board_spots[r*9 + c].num << RESET << " ";
        }
        
        else if (!current_board_spots[r*9 + c].valid)
        {
          cout << "| " << RED << current_board_spots[r*9 + c].num << RESET << " ";
        }
        
        else
        {
          cout << "| " << current_board_spots[r*9 + c].num << " ";
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

// for debugging purposes
void print_spot_info()
{
  for (int i = 0; i < 81; i++)
  {
    cout << "current_board[" << i << "]:"
         << " r: "  << current_board_spots[i].row
         << " c: "  << current_board_spots[i].col
         << " n: "  << current_board_spots[i].num
         << " v: "  << current_board_spots[i].valid << "\n";
  }
}



void create_correct_board()
{
  for (int r = 0; r < 9; r++)
  {
    for (int c = 0; c < 9; c++)
    {
      
    }
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

// returns true if valid placement
// returns false if invalid
bool check_placement(SPOT placed_spot)
{
  return true;
}

// check the keyboard entry
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

// handle the keyboard press
void handle_input(char input, SPOT &cursor)
{
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
    current_board_spots[cursor.row*9 + cursor.col].num = input - '0';
  }
  
  return;
}

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
  
  create_correct_board();
  setup_board_easy();
  
  // initialize all spots on the board to be nothing to begin with
  for (int i = 0; i < 81; i++)
  {
    current_board_spots[i].row    = i/9;
    current_board_spots[i].col    = i%9;
    current_board_spots[i].num    = 0;
    current_board_spots[i].valid  = true;
  }
  
  
  print_board(cursor);
  print_commands();

  while (!quit)
  {
    clear();
    print_board(cursor);
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
