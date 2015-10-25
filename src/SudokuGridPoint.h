#ifndef __sudoku_sudokugridpoint_h__
#define __sudoku_sudokugridpoint_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Declaration of SudokuGridPoint.
/// \author anon.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <stdexcept>

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Sudoku grid point contains the coordinates on a sudoku board and the value at that point.
////////////////////////////////////////////////////////////////////////////////////////////////////
class SudokuGridPoint
{
  public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Defualt constructor. If this is used behaviour is undefined.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    SudokuGridPoint()
    {
      x_ = 0;
      y_ = 0;
      initialValue_ = 0;
      guessValue_ = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief SudokuGridPoint constructor.
    ///
    /// \param x The x coordinate on the board (0 to 8).
    /// \param y The y coordinate on the board (0 to 8).
    /// \param value The value at (x,y).  Valid values: 1 to 9.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    SudokuGridPoint(short x, short y, short value)
    {
      checkXYInBounds(x, y);

      // Check value in correct bounds.
      if ( value < 1 )
      {
        throw std::invalid_argument("Cannot specify value <= 0.");
      }
      else if ( value > 9 )
      {
        throw std::invalid_argument("Cannot specify a value > 9.");
      }

      // Input seems OK.
      x_ = x;
      y_ = y;
      initialValue_ = value;
      guessValue_ = 0;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief SudokuGridPoint constructor.
    ///
    /// \param x The x coordinate on the board (0 to 8).
    /// \param y The y coordinate on the board (0 to 8).
    /// \param possibleValues The possible values the value at this coordinate could be.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    SudokuGridPoint(short x, short y, std::vector<short> possibleValues)
    {
      
      // initialValue_ to be 1 for the time being, change afterwards.
      SudokuGridPoint(x, y, 1);
      checkVectorOfPossibleValues(possibleValues);
      
      if ( possibleValues.size() == 1 )
      {
        guessValue_ = possibleValues.at(0);
      }
      else
      {
        std::copy(possibleValues.begin(), possibleValues.end(),
          std::back_inserter(possibleValues_));
        guessValue_ = 0;
      }

      initialValue_ = 0;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief gets the x ordinate.
    /// \return the x ordinate.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    short getX()
    {
      return x_;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief gets the y ordinate.
    /// \return the y ordinate.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    short getY()
    {
      return y_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief gets the value.
    /// \return the value.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    short getValue()
    {
      if ( initialValue_ != 0 )
      {
        return initialValue_;
      }
      else
      {
        // It's possible guessValue_ is also 0, but that is ok.  It indicates we have not found 
        // a value, guess or otherwise.
        return guessValue_;
      }
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief get the possible values.
    /// \return the possible values.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<short> getPossibleValues()
    {
      return possibleValues_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief remove a possible values.
    /// \return true if value was remove, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool removePossibleValue(short value)
    {
      bool result(false);
      std::vector<short>::iterator itPos(std::remove(possibleValues_.begin(), possibleValues_.end(),
        value));
      
      if ( itPos != possibleValues_.end() )
      {
        possibleValues_.erase(itPos, possibleValues_.end());
        removedPossibleValues_.push_back(value);
        result = true;
      }

      if ( possibleValues_.size() == 1 )
      {
        // If we have one value left in the possible values this must be our guess.
        guessValue_ = possibleValues_.back();
        possibleValues_.pop_back();
      }

      return result;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief restores a possible values.
    /// \return true if value was restored, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool restorePossibleValue(short value)
    {
      bool result(false);

      // If we gave an initial value then we cannot restore a value to the possible values.
      if( initialValue_ == 0 )
      {
        // Find if we removed the value previously.
        std::vector<short>::iterator itPos(std::remove(removedPossibleValues_.begin(),
          removedPossibleValues_.end(), value));

        // If we have then we can restore it.
        if ( itPos != removedPossibleValues_.end() )
        {
          // We cannot have removed a value that was assigned to guessValue_ (hopefully), so add it
          // back if it is none zero.
          if ( guessValue_ != 0 )
          {
            possibleValues_.push_back(guessValue_);
            guessValue_ = 0;
          }
          // Now to add the value to possible values.
          possibleValues_.push_back(value);

          // Since it was in the vector of removed values we have better remove it.
          removedPossibleValues_.erase(itPos, removedPossibleValues_.end());
          
          result = true;
        }
        else
        {
          throw std::invalid_argument("Cannot restore value that was not removed previously.");
        }
      }
      return result;
    }

  // Private methods.
  private:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Throws exception if x or y is out of bounds.
    /// \param x x ordinate.
    /// \param y y ordinate.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    void checkXYInBounds(const short x, const short y)
    {
      // Check x ordinate in correct bounds.
      if ( x < 0 )
      {
        throw std::invalid_argument("Cannot specify a negative x ordinate.");
      }
      else if ( x > 8 )
      {
        throw std::invalid_argument("Cannot specify an x ordinate > 8.");
      }

      // Check y ordinate in correct bounds.
      if ( y < 0 )
      {
        throw std::invalid_argument("Cannot specify a negative y ordinate.");
      }
      else if ( y > 8 )
      {
        throw std::invalid_argument("Cannot specify an y ordinate > 8.");
      }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Throws exception if possible values are out of bounds or there is a repeated
    /// possible value.
    /// \param possibleValues vector of possible values.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    void checkVectorOfPossibleValues(std::vector<short> possibleValues)
    {
      if ( possibleValues.empty() )
      {
        throw std::invalid_argument("Possible values cannot be empty.");
      }

      for ( auto &v : possibleValues )
      {
        if ( v < 1 )
        {
          throw std::invalid_argument("Cannot specify a possible value <= 0.");
        }
        else if ( v > 9 )
        {
          throw std::invalid_argument("Cannot specify a possible value > 9.");
        }
      }

      std::sort(possibleValues.begin(), possibleValues.end());
      // Check for repeated values now.
      if (std::unique(possibleValues.begin(), possibleValues.end()) != possibleValues.end())
      {
        throw std::invalid_argument("Possible values has repeated values.");
      }
    }

  // Private variables.
  private:
    short x_; // The x ordinate.
    short y_; // The y ordinate.
    short initialValue_; // The value at the coordinates on the Sudoku board.
    short guessValue_; // The value we have guessed once we have one value in possible values.
    std::vector<short> possibleValues_; // Vector of possible values.
    std::vector<short> removedPossibleValues_; // Vector of removed possible values.
};
 
} // End of namespace sudoku.

#endif
