#ifndef __sudoku_sudokugridpoint_h__
#define __sudoku_sudokugridpoint_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Declaration of SudokuGridPoint.
/// \author anon.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "utilities/src/CheckIfVectorsEqual.h"

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
    SudokuGridPoint(short x, short y, std::vector<short> possibleValues) : SudokuGridPoint(x, y, 1)
    { 
      // initialValue_ to be 1 for the time being, change afterwards.
      checkVectorOfPossibleValues(possibleValues);     
 
      std::copy(possibleValues.begin(), possibleValues.end(),
        std::back_inserter(possibleValues_));
      
      guessValue_ = 0;
      initialValue_ = 0;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief gets the x ordinate.
    /// \return the x ordinate.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    short getX() const
    {
      return x_;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief gets the y ordinate.
    /// \return the y ordinate.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    short getY() const
    {
      return y_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief gets the value.
    /// \return the value.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    short getValue() const
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
    std::vector<short> getPossibleValues() const
    {
      return possibleValues_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Remove a value from the possible values.  It is not guaranteed that the value will be
    /// removed from the possible values.  It will only be removed if it exists in the same column,
    /// row or sudoku 'box' that the given x and y exist in. However, if there is only one possible
    /// value left then the x and y passed to this method must be the same as the x and y in this
    /// object, otherwise the value will not be removed and a value indicating this will be
    /// returned.
    /// \param x The x ordinate of the value.
    /// \param y The y ordinate of the value.
    /// \param value The value to be removed from possible values.
    /// \return 0 if value removed and it was the last possible value, 1 if value removed, 2 if 
    /// value not removed, and 3 if removing the last value, but the grid point coordinate does not
    /// match the coordinates passed to this method.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    short removePossibleValue(const short x, const short y, const short value)
    {
      short result(2);

      // Checks if in the same column or row.  Then checks if they are in the same sudoku box.
      // x - (x % 3) is a way of getting to the nearest multiple of 3 less than or equal to x.
      if ( x_ == x || y_ == y ||
        ( ( x_ - (x_ % 3) ) == ( x - ( x % 3 ) ) && ( y_ - (y_ % 3) ) == ( y - ( y % 3 ) ) ) )
      {      
        // Now check if the value is actually in the possibleValues.
        std::vector<short>::iterator itPos(std::remove(possibleValues_.begin(),
          possibleValues_.end(), value));
        
        if ( itPos != possibleValues_.end() )
        {
          // It is in the possible values, however, if it is the last value and the x and y passed
          // to this method differ from this grid point then we shouldn't remove it and return
          // a value indicating this.
          if ( possibleValues_.size() == 1 && ! ( x == x_ && y == y_ ) )
          {
            result = 3;
          }
          
          // If there is no problem removing it do so.
          if ( result != 3 )
          {
            possibleValues_.erase(itPos, possibleValues_.end());
          
            // Now add to the removed values.
            removedValues_.push_back(RemovedValueInfo_());
            removedValues_.back().removedX = x;
            removedValues_.back().removedY = y;
            removedValues_.back().removedValue = value;

            result = 1;
          }
        }
      }
    
      if ( result == 1 && possibleValues_.size() == 0 )
      {
        // If we have no values left in the possible values this must be our guess.
	guessValue_ = value;
        result = 0;
      }

      return result;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief restores a possible values.  Restoration will only take place if the passed ordinates
    /// and value correspond to something that was removed previously.
    /// \param x The x ordinate of the value.
    /// \param y The y ordinate of the value.
    /// \param value The value to be removed from possible values.
    /// \return true if value was restored, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool restorePossibleValue(const short x, const short y, const short value)
    {
      bool result(false);

      // If we gave an initial value then we cannot restore a value to the possible values.
      if( initialValue_ == 0 )
      {
        RemovedValueInfo_ valueInfo = RemovedValueInfo_();
        valueInfo.removedX = x;
        valueInfo.removedY = y;
        valueInfo.removedValue = value;

        // Find if we removed the value previously.
        std::vector<RemovedValueInfo_>::iterator itPos(std::remove(removedValues_.begin(),
          removedValues_.end(), valueInfo));

        // If we have then we can restore it.
        if ( itPos != removedValues_.end() )
        {
          // We have restored a possible value, make sure the guess is back to being 0.
          guessValue_ = 0;
          // Now to add the value to possible values.
          possibleValues_.push_back(value);

          // Since it was in the vector of removed values we had better remove it.
          removedValues_.erase(itPos, removedValues_.end());
          
          result = true;
        }
      }
      return result;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Equality operator.
    /// \param rhs The right hand side object.
    /// \return true if number of possible values are equal, but if initial values were provided
    /// then trivially equal, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator==(const SudokuGridPoint& rhs) const
    {
      bool result(false);
      if ( ( initialValue_ == 0 && rhs.initialValue_ == 0 ) ||
           ( initialValue_ != 0 && rhs.initialValue_ != 0 ) )
      { 
        if ( possibleValues_.size() == rhs.possibleValues_.size() )
        {
          result = true;
        }
      }
      return result;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Less than operator.
    /// \param rhs The right hand side object.
    /// \return true if number of possible values of this object is less than that of the rhs, note
    /// that objects initialised with initial values are less than objects that have possible
    /// values, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator<(const SudokuGridPoint& rhs) const
    {
      bool result(false);
      if ( initialValue_ != 0)
      {
        if ( rhs.initialValue_ == 0 )
        {
          result = true;
        }
      }
      else
      {
        if ( possibleValues_.size() < rhs.possibleValues_.size() )
        {
          result = true;
        }
      }
      return result;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Not equal to operator.
    /// \param rhs The right hand side object.
    /// \return true if number of possible values of this object is not equal to that of the rhs,
    /// note that objects initialised with initial values are not equal to objects initialised
    /// with possible values, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator!=(const SudokuGridPoint& rhs) const
    {
      return ! ( *this == rhs );
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Less than or equal to operator.
    /// \param rhs The right hand side object.
    /// \return true if number of possible values of this object is less than or equal to that of
    /// the rhs, note that objects initialised with initial values are less than or equal to objects
    /// initialised with possible values, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator<=(const SudokuGridPoint& rhs) const
    {
      return ( *this == rhs ) || ( *this < rhs );
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Greater than operator.
    /// \param rhs The right hand side object.
    /// \return true if number of possible values of this object is greater than that of
    /// the rhs, note that objects initialised with initial values not greater than objects
    /// initialised with possible values, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator>(const SudokuGridPoint& rhs) const
    {
      return ! ( *this <= rhs );
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Greater than or equal to operator.
    /// \param rhs The right hand side object.
    /// \return true if number of possible values of this object is greater than or equal to that of
    /// the rhs, note that objects initialised with initial values are not greater than or equal to
    /// objects initialised with possible values, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator>=(const SudokuGridPoint& rhs) const
    {
      return ! ( *this < rhs );
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Gets the affected grid points.  This will need explaining.
    /// We have a grid point, given by x, y on the sudoku board.  If this grid point has a value
    /// then none of the values in the same row, column or 'box' can have the same value. With this
    /// method we return a vector of pairs of these other grid points.
    /// \return See decription.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::pair<short, short> > getAffectedGridPoints() const
    {
      std::vector<std::pair<short, short> > affectedGridPoints;
      
      // Get affected grid points from row.
      for ( short i = 0; i < 9; ++i )
      {
        // Don't add this grid point.
        if ( i != x_ )
        {
          affectedGridPoints.push_back(std::make_pair(i, y_));
        }
      }

      // Get affected grid points from column.
      for ( short j(0); j < 9; ++j )
      {
        // Don't add this grid point.
        if ( j != y_ )
        {
          affectedGridPoints.push_back(std::make_pair(x_, j));
        }
      }
      
      short startX(x_ - (x_ % 3));
      short startY(y_ - (y_ % 3));

      // Get affected grid points from sudoku box.
      for ( short i(startX); i < startX + 3; ++i )
      {
        for ( short j(startY); j < startY + 3; ++j )
        {
          if ( i != x_ && j != y_ )
          {
            affectedGridPoints.push_back(std::make_pair(i, j));
          }
        }
      }

      return affectedGridPoints;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief The shallowEquals method.  Shallow since we only compare x, y, the value and 
    /// the vector of possible values (i.e. things that are available publically).
    /// \param rhs The other object we are comapring to.
    /// \return true is equal (shallowy) false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool shallowEquals(const SudokuGridPoint& rhs) const
    {
      bool result(false);
      if ( this->getX() == rhs.getX() &&
           this->getY() == rhs.getY() &&
           this->getValue() == rhs.getValue() &&
           utilities::checkIfVectorsEqual(this->getPossibleValues(), rhs.getPossibleValues()))
      {
        result = true;
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
    void checkXYInBounds(const short x, const short y) const
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
    void checkVectorOfPossibleValues(std::vector<short> possibleValues) const
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
    // Struct that contains information about a removed value from possible values.
    struct RemovedValueInfo_
    {
      short removedValue;
      short removedX;
      short removedY;

      // Need equals operator for restoring to possible values.
      bool operator==(const RemovedValueInfo_& rhs) const
      {
        return ( removedValue == rhs.removedValue ) &&
               ( removedX == rhs.removedX ) &&
               ( removedY == rhs.removedY );
      }
    };

    short x_; // The x ordinate.
    short y_; // The y ordinate.
    short initialValue_; // The value at the coordinates on the Sudoku board.
    short guessValue_; // The value we have guessed once we have one value in possible values.
    std::vector<short> possibleValues_; // Vector of possible values.
    std::vector<RemovedValueInfo_> removedValues_; // Vector of removed possible values.
};
 
} // End of namespace sudoku.

#endif
