#include "SudokuBoard.h"
#include "SudokuGridPoint.h"
#include <vector>

// The Al Escargot.
const short testBoard5[9][9] = 
{
{1, 0, 0, 0, 0, 7, 0, 9, 0},
{0, 3, 0, 0, 2, 0, 0, 0, 8},
{0, 0, 9, 6, 0, 0, 5, 0, 0},
{0, 0, 5, 3, 0, 0, 9, 0, 0},
{0, 1, 0, 0, 8, 0, 0, 0, 2},
{6, 0, 0, 0, 0, 4, 0, 0, 0},
{3, 0, 0, 0, 0, 0, 0, 1, 0},
{0, 4, 1, 0, 0, 0, 0, 0, 7},
{0, 0, 7, 0, 0, 0, 3, 0, 0}
};

int main(void)
{
  sudoku::SudokuBoard sb(testBoard8);

  sb.solveBoard();

  std::vector<sudoku::SudokuGridPoint> points(sb.getSudokuBoard());

  short array[9][9];

//  for (std::vector<sudoku::SudokuGridPoint>::iterator iter(points.begin()); iter != points.end(); iter++)
//  {
//    std::cout << "x: " << (*iter).getX() + 1 << ", y: " << (*iter).getY() + 1 << ", value: " << (*iter).getValue() << std::endl;
//    array[(*iter).getX()][(*iter).getY()] = (*iter).getValue();
//    std::cout << "Press enter to continue" << std::endl;
//    std::cin.ignore();
//  }

  std::cout << "\nThe full sudoku board:" << std::endl;
  for ( int i(0); i < 9; ++i )
  {
    for ( int j(0); j < 9; ++j )
    {
      std::cout << array[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
