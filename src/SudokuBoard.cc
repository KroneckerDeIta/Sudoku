////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of SudokuBoard.
/// \author anon.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SudokuBoard.h"

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoard::checkBoardValues_( const short (&initialBoard)[9][9] ) const
{
  for ( unsigned short i(0); i < sizeof(initialBoard)/sizeof(*initialBoard); ++i )
  {
    for ( unsigned short j(0); j < sizeof(initialBoard[i])/sizeof(*initialBoard[i]); ++j )
    {
      if ( initialBoard[i][j] < 0 )
      {
        throw std::invalid_argument("Grid point (" + std::to_string(i) + "," + std::to_string(j) +
          ") has value < 0");
      }
      if ( initialBoard[i][j] > 9 )
      {
        throw std::invalid_argument("Grid point (" + std::to_string(i) + "," + std::to_string(j) +
          ") has value > 9");
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoard::populateSudokuBoard_( const short (&initialBoard)[9][9] )
{
  // Start of non TDD code.
  // Clear the board just in case.
  sudokuBoard_.clear();
  // End of non TDD code.

  checkBoardValues_( initialBoard );

  // If we reach this point the values in the board are in the correct range.
  for ( unsigned short gridX(0); gridX < 9; ++gridX )
  {
    for ( unsigned short gridY(0); gridY < 9; ++gridY )
    {
      if ( initialBoard[gridX][gridY] > 0 )
      {
        // We have an initial value specified.
        sudokuBoard_.push_back(SudokuGridPoint(gridX, gridY, initialBoard[gridX][gridY]));
      }
      else
      {
        // The value was 0, no initial value specified.

        // Explicitly define result array to be zeroes.
        short possibleValuesArray[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        std::vector<short> possibleValuesVector;
      
        // Add to resultArray based on numbers in row and column of coordinate (x,y).
        for ( short i(0); i < 9; ++i )
        {
          if ( initialBoard[gridX][i] > 0 && i != gridY )
          {
            ++possibleValuesArray[initialBoard[gridX][i] - 1];
          }
          if ( initialBoard[i][gridY] > 0 && i != gridX )
          {
            ++possibleValuesArray[initialBoard[i][gridY] - 1];
          }
        }
      
        // Get the top left corner of the square the coordinate (x,y) is in.
        short startX = gridX - (gridX % 3);
        short startY = gridY - (gridY % 3);
      
        for ( short i(startX); i < startX + 3; ++i )
        {
          for ( short j(startY); j < startY + 3; ++j )
          {
            if ( initialBoard[i][j] > 0 && i != gridX && j != gridY )
            {
              ++possibleValuesArray[initialBoard[i][j] - 1];
            }
          }
        }
      
        // Add values to result vector.
        for ( short i(0); i < 9; ++i )
        {
          if ( possibleValuesArray[i] == 0 )
          {
            possibleValuesVector.push_back(i + 1);
          }
        }

        // We have populated our vector of possible values, not to add to sudokuBoard_.
        sudokuBoard_.push_back(SudokuGridPoint(gridX, gridY, possibleValuesVector));
      } // End of else (!initialBoard[gridX][gridY] > 0).
    } // End of for (gridY).
  } // End of for (gridX).

}  // End of SudokuAssist::populateSudokuBoard_.

////////////////////////////////////////////////////////////////////////////////////////////////////
SudokuBoard::SudokuBoard(const short (&initialBoard)[9][9])
{
  checkBoardValues_(initialBoard);
  // Input board seems ok, populate our board.
  populateSudokuBoard_(initialBoard);
}

} // End of namespace sudoku.
