////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of SudokuAssist.
/// \author anon.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/iterator/indirect_iterator.hpp>

#include "SudokuAssist.h"

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuAssist::checkBoardValues_( const short (&initialBoard)[9][9] )
{
  for ( unsigned short i(0); i < 9; ++i )
  {
    for ( unsigned short j(0); j < 9; ++j )
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
void SudokuAssist::populateSudokuBoard_( const short (&initialBoard)[9][9] )
{
  // Clear the board just in case.
  sudokuBoard_.clear();

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
void SudokuAssist::solveBoard_(unsigned int currentIndex)
{
  unsigned int index(0);

  // First sort sudokuBoard_, only sort it from after the currentIndex.
  std::sort(sudokuBoard_.begin() + currentIndex, sudokuBoard_.end());

  if ( currentIndex > 80 )
  {
    std::invalid_argument("The current index when solving the board is too large.");
  }
  else if ( sudokuBoard_.at(currentIndex).getPossibleValues().size() != 0 )
  {
    std::logic_error("The number of possible values at the current index must be 0.");
  }
  else
  {
    // Check the last entry's possibleValues size.  If 0 we are done.
    if ( sudokuBoard_.back().getPossibleValues().size() == 0 )
    {
      // We have solved it!
      valid_ = true;
      return;
    }
    // Its not solved, so get the index of the next entry that does not have 0 possible values.
    for ( index = currentIndex; index < sudokuBoard_.size(); ++index )
    {
      if ( sudokuBoard_.at(index).getPossibleValues().size() != 0 )
      {
        break;
      }
    }
  }

  // Make a reference to the SudokuGridPoint we are now interested in.
  SudokuGridPoint& gp(sudokuBoard_.at(index));

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
    for ( unsigned int i(index + 1); i < sudokuBoard_.size(); ++i )
    {
      if ( sudokuBoard_.at(i).removePossibleValue(gp.getX(), gp.getY(), val) )
      {
        // We have removed a value at another grid point, make sure it has at least one possible
        // value left.  If not it means that there are no values left for that other grid point
        // to be.
        if ( sudokuBoard_.at(i).getPossibleValues().size() == 0 )
        {
          invalid = true;
        }
      }
    }

    if ( ! invalid )
    {
      // Recursive call to solve the board.
      solveBoard_(index);

      if ( valid_ )
      {
        // We found a solution!
        return;
      }
    }

    // We did not find a solution.  Restore values.
    for ( unsigned int i(index + 1); i < sudokuBoard_.size(); ++i )
    {
      sudokuBoard_.at(i).restorePossibleValue(gp.getX(), gp.getY(), val);
    }
    // Restore all the possible values.
    for ( short otherVal : possibleValuesCopy )
    {
      gp.restorePossibleValue(gp.getX(), gp.getY(), otherVal);
    }
  }

  // If we have got this far we have not found a solution.  Make sure valid_ is set to false.
  valid_ = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
SudokuAssist::SudokuAssist(const short (&initialBoard)[9][9])
{
  populateSudokuBoard_(initialBoard);
  solveBoard_(0);
}

} // End of namespace sudoku.
