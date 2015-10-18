#ifndef __sudoku_SudokuGridPoint_h__
#define __sudoku_SudokuGridPoint_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief File containing SudokuGridPoint class.
/// \author anon.
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Sudoku grid point contains the coordinates on a sudoku board and the value at that point.
////////////////////////////////////////////////////////////////////////////////////////////////////
class SudokuGridPoint
{
  public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief SudokuGridPoint constructor.
    ///
    /// \param x The x coordinate on the board (0 to 8).
    /// \param y The y coordinate on the board (0 to 8).
    /// \param value The value at (x,y).  Valid values: 0 to 9.  0 indicates that the value is 
    /// unknown.
    /// \param initialValue True if the value was one of the initial values, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    SudokuGridPoint(short x, short y, short value, bool initialValue)
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

      // Check value in correct boudns.
      if ( value < 0 )
      {
        throw std::invalid_argument("Cannot specify a negative value.");
      }
      else if ( value > 9 )
      {
        throw std::invalid_argument("Cannot specify a value > 9.");
      }

      // Check that if value is set to zero it cannot be an initial value.
      if ( value == 0 && initialValue )
      {
        throw std::invalid_argument("Cannot have a zero value and be an initial value.");
      }

      // Input seems OK.
      x_ = x;
      y_ = y;
      value_ = value;
      initialValue_ = initialValue;
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
      return value_;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief if this was an initial value.
    /// \return true if initial value, false otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool isInitialValue()
    {
      return initialValue_;
    }
  
  private:
    short x_; // The x ordinate.
    short y_; // The y ordinate.
    short value_; // The value at the coordinates on the Sudoku board.
    bool initialValue_; // If it is an initial value.
};
 
} // End of namespace sudoku.

#endif
