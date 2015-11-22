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
        short rowValues[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        short columnValues[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        short squareValues[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };        

        std::vector<short> possibleValuesVector;
      
        // Add to arrays based on numbers in row and column of coordinate (x,y).
        for ( short i(0); i < 9; ++i )
        {
          if ( initialBoard[gridX][i] > 0 && i != gridY )
          {
            ++rowValues[initialBoard[gridX][i] - 1];
          }
          if ( initialBoard[i][gridY] > 0 && i != gridX )
          {
            ++columnValues[initialBoard[i][gridY] - 1];
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
              ++squareValues[initialBoard[i][j] - 1];
            }
          }
        }
      
        // Now to check the row, column and square values to make sure the values are no greater
        // than 1, otherwise the board is invalid.
        for ( short i(0); i < 9; ++i )
        {
          if ( rowValues[i] > 1 || columnValues[i] > 1 || squareValues[i] > 1 )
          {
            validBoard_ = false;
          }
        }

        // Add values to result vector.
        for ( short i(0); i < 9; ++i )
        {
          if ( rowValues[i] + columnValues[i] + squareValues[i] == 0 )
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
void SudokuBoard::solveBoard()
{
  // If the board is not valid we cannot solve it!
  if ( validBoard_ )
  {
    // The solver needs the current index to start at 0.
    solveBoard_(0);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoard::solveBoard_(unsigned int currentIndex)
{
  // First sort sudokuBoard_, only sort it from after the currentIndex.
  std::sort(sudokuBoard_.begin() + currentIndex, sudokuBoard_.end());

  // Check the last entry's possibleValues size.  If 0 we are done.
  if ( currentIndex == sudokuBoard_.size() )
  {
    // We have solved it! Go back through the recursive calls.
    boardSolvable_ = true;
  }
  else if ( sudokuBoard_.at(currentIndex).getPossibleValues().size() == 0 )
  {
    // The initial values that we skip through.
    solveBoard_(currentIndex + 1);
  }
  else
  {
    // This should be the grid points where there are possible values now.

    // Make a reference to the SudokuGridPoint we are now interested in.
    SudokuGridPoint& gp(sudokuBoard_.at(currentIndex));
  
    // Make a copy of this vector of possibleValues, also record its x and y.
    std::vector<short> possibleValuesCopy(gp.getPossibleValues());    
  
    for ( short val : possibleValuesCopy )
    {
      for ( short otherVal : possibleValuesCopy )
      {
        // Remove the other possible values.  They will need restoring if solution not found.
        if ( val != otherVal )
        {
          gp.removePossibleValue(gp.getX(), gp.getY(), otherVal);
        }
      }
      // Now remove the value itself to add it as a guess.
      gp.removePossibleValue(gp.getX(), gp.getY(), val);
     
      bool invalid(false);
      for ( unsigned int i(currentIndex + 1); i < sudokuBoard_.size(); ++i )
      {
        if ( sudokuBoard_.at(i).removePossibleValue(gp.getX(), gp.getY(), val) == 3 )
        {
          // We have removed a value at another grid point, but it was it's last value.
          // The solution down this path was not valid.
          invalid = true;
        }
      }
  
      if ( ! invalid )
      {
        // Recursive call to solve the board.
        solveBoard_(currentIndex + 1);
      }
  
      // If the board was not solved return it to its previous state.
      if ( ! boardSolvable_ )
      {
        // We did not find a solution.  Restore values.
        for ( unsigned int i(currentIndex + 1); i < sudokuBoard_.size(); ++i )
        {
          sudokuBoard_.at(i).restorePossibleValue(gp.getX(), gp.getY(), val);
        }
        // Restore all the possible values.
        for ( short otherVal : possibleValuesCopy )
        {
          gp.restorePossibleValue(gp.getX(), gp.getY(), otherVal);
        }
      }
    }
  } // End of else.

} // End of SolveBoard_.

////////////////////////////////////////////////////////////////////////////////////////////////////
SudokuBoard::SudokuBoard(const short (&initialBoard)[9][9]): validBoard_(true),
  boardSolvable_(false), sudokuBoard_()
{
  checkBoardValues_(initialBoard);
  // Input board seems OK, try to populate board.
  populateSudokuBoard_(initialBoard);
}

} // End of namespace sudoku.
