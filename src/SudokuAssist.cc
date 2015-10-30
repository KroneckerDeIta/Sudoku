////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Definition of SudokuAssist.
/// \author anon.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SudokuAssist.h"

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
bool getPossibleValues( const short (&sudokuBoard)[9][9], const short x, const short y, 
  std::vector<short> &resultVector )
{
  bool result(true);
  // Explicitly define result array to be zeroes.
  short resultArray[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  // Start of non-TDD code.
  // Clear the resultVector.
  resultVector.clear();
  // End of non-TDD code.

  // Add to resultArray based on numbers in row and column of coordinate (x,y).
  for ( short i(0); i < 9; ++i )
  {
    if ( sudokuBoard[x][i] > 0 && i != x )
    {
      ++resultArray[sudokuBoard[x][i]];
    }
    if ( sudokuBoard[i][y] > 0 && i != y )
    {
      ++resultArray[sudokuBoard[i][y]];
    }
  }

  // Get the top left corner of the square the coordinate (x,y) is in.
  short startX = x - (x % 3);
  short startY = y - (y % 3);

  for ( short i(startX); i < startX + 3; ++i )
  {
    for ( short j(startY); j < startY + 3; ++j )
    {
      if ( sudokuBoard[i][j] > 0 && i != x && j != y )
      {
        ++resultArray[sudokuBoard[i][j]];
      }
    }
  }

  // Add values to result vector. There could be a case where the board is not valid and more than
  // one of one value was found (two 1's for example), so we will need to return false in this case.
  for ( short i(0); i < 9; ++i )
  {
    if ( resultArray[i] > 1 )
    {
      result = false;
    }
    else if ( resultArray[i] == 1 )
    {
      resultVector.push_back(i);
    }
  }

  // We will return an empty result vector if board was not valid.
  if (!result)
  {
    resultVector.clear();
  }
  return result;
}

} // End of namespace sudoku.
