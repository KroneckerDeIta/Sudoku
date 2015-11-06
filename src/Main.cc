#include "SudokuAssist.h"

// Define a test board.
const short testBoard1[9][9] = 
{
{0, 0, 9, 0, 0, 0, 0, 0, 3},
{0, 3, 0, 0, 5, 7, 0, 0, 0},
{0, 0, 0, 8, 0, 0, 0, 0, 4},
{2, 0, 0, 0, 0, 0, 1, 6, 0},
{0, 5, 0, 1, 7, 6, 0, 0, 0},
{0, 0, 0, 0, 0, 9, 0, 5, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{8, 6, 0, 4, 1, 0, 0, 0, 9},
{0, 0, 2, 5, 0, 3, 4, 0, 0}
};

const short testBoard2[9][9] = 
{
{1, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int main(void)
{
  std::cout << "Manually testing SudokuAssist." << std::endl;  

  sudoku::SudokuAssist sa(testBoard2);

  if ( sa.isValid() )
  {
    std::cout << "Board is valid." << std::endl;
  }
  else
  {
    std::cout << "Board is not valid." << std::endl;
  }

  std::cout << "Printing board..." << std::endl;

  short board[9][9];

  //for ( auto v : sa.getSolvedBoard() )
  //{
  //  std::cout << "x = " << v.getX() << ", y = " << v.getY() << ", value = " << v.getValue() << std::endl;
  //}

  for ( auto v : sa.getSolvedBoard() )
  {
    board[v.getX()][v.getY()] = v.getValue();
  }

  for ( unsigned int i(0); i < 9; ++i )
  {
    for ( unsigned int j(0); j < 9; ++j )
    {
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
