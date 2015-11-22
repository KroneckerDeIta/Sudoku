////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of tests for SudokuBoard.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "src/SudokuBoard.h"
#include "SudokuBoardTest.h"
#include "src/SudokuGridPoint.h"

CPPUNIT_TEST_SUITE_REGISTRATION( sudoku::SudokuBoardTest );

// Define a test board.
const short testBoard[9][9] = 
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

// Define some invalid boards.
const short sameNumberInRowBoard[9][9] = 
{
{0, 0, 9, 0, 0, 0, 0, 0, 3},
{0, 3, 0, 0, 5, 7, 0, 0, 0},
{0, 0, 0, 8, 0, 0, 0, 0, 4},
{2, 0, 0, 0, 0, 0, 1, 6, 0},
{0, 5, 0, 1, 7, 6, 0, 0, 0},
{0, 0, 0, 0, 0, 9, 0, 5, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{8, 6, 0, 4, 1, 0, 0, 0, 9},
{0, 4, 2, 5, 0, 3, 4, 0, 0}
};

const short sameNumberInColumnBoard[9][9] = 
{
{0, 0, 9, 0, 0, 0, 0, 0, 3},
{0, 3, 2, 0, 5, 7, 0, 0, 0},
{0, 0, 0, 8, 0, 0, 0, 0, 4},
{2, 0, 0, 0, 0, 0, 1, 6, 0},
{0, 5, 0, 1, 7, 6, 0, 0, 0},
{0, 0, 0, 0, 0, 9, 0, 5, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{8, 6, 0, 4, 1, 0, 0, 0, 9},
{0, 0, 2, 5, 0, 3, 4, 0, 0}
};

const short sameNumberInSquareBoard[9][9] = 
{
{0, 0, 9, 0, 0, 0, 0, 0, 3},
{0, 3, 0, 0, 5, 7, 0, 0, 0},
{0, 0, 0, 8, 0, 0, 0, 0, 4},
{2, 0, 0, 0, 0, 0, 1, 6, 0},
{0, 5, 0, 1, 7, 6, 0, 0, 0},
{0, 0, 0, 0, 0, 9, 0, 5, 0},
{0, 0, 6, 0, 0, 0, 0, 0, 0},
{8, 6, 0, 4, 1, 0, 0, 0, 9},
{0, 0, 2, 5, 0, 3, 4, 0, 0}
};

// Define board full of zeros.
const short zeroesBoard[9][9] = 
{
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// Define a board that is initially valid, but not solvable.
// Note that at (x,y) = (0,0) and (0,2) values have been added and are incorrect.
const short nonSolvableTestBoard[9][9] = 
{
{6, 2, 8, 5, 0, 0, 0, 0, 3},
{9, 0, 0, 0, 0, 1, 6, 0, 0},
{0, 0, 0, 0, 6, 0, 0, 7, 0},
{7, 0, 0, 4, 0, 0, 0, 1, 0},
{0, 0, 4, 0, 0, 0, 8, 0, 0},
{0, 8, 0, 0, 0, 9, 0, 0, 5},
{0, 1, 0, 0, 4, 0, 0, 0, 0},
{0, 0, 5, 7, 0, 0, 0, 0, 9},
{4, 0, 0, 0, 0, 3, 0, 2, 0}
};

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Copies the values from one Sudoku board array to another.
/// \param origBoard The original board to be copied.
/// \param copyBoard The copied board.
////////////////////////////////////////////////////////////////////////////////////////////////////
void copyBoardArray( const short (&origBoard)[9][9], short (&copyBoard)[9][9] )
{
  std::copy(&origBoard[0][0], &origBoard[0][0]+ 9*9, &copyBoard[0][0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Generates a Sudoku grid point.
/// \param x The x ordinate.
/// \param y The y ordinate.
/// \param possibleValues The possible values at the grid point.
/// \return A SudokuGridPoint object.
////////////////////////////////////////////////////////////////////////////////////////////////////
SudokuGridPoint generateSudokuGridPoint( const short x, const short y,
  std::vector<short> possibleValues )
{
  return SudokuGridPoint(x, y, possibleValues);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Generates a Sudoku grid point.
/// \param x The x ordinate.
/// \param y The y ordinate.
/// \param initialValue The initial value at the grid point.
/// \return A SudokuGridPoint object.
////////////////////////////////////////////////////////////////////////////////////////////////////
SudokuGridPoint generateSudokuGridPoint( const short x, const short y, const short initialValue )
{
  return SudokuGridPoint(x, y, initialValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Generates a multi-dimensional array from a Sudoku board (vector of SudokuGridPoint).
/// \param sudokuBoard The Sudoku Board.
/// \param resultArray The array of Sudoku board values.
/// \return Sudoku board as an array.
////////////////////////////////////////////////////////////////////////////////////////////////////
void sudokuBoardToArray( std::vector<SudokuGridPoint> sudokuBoard, short (&resultArray)[9][9] )
{
  for ( std::vector<SudokuGridPoint>::const_iterator iter(sudokuBoard.begin());
    iter != sudokuBoard.end(); ++iter )
  {
    resultArray[iter->getX()][iter->getY()] = iter->getValue();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Checks the board values are all between 1 and 9.
/// \param resultArray The array of Sudoku board values.
/// \return true if board's values are between 1 and 9, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////
bool checkBoardValuesAllSet( const short (&sudokuArray)[9][9] )
{
  bool result(true);

  for ( unsigned int i(0); i < sizeof(sudokuArray)/sizeof(sudokuArray[0]); ++i )
  {
    for ( unsigned int j(0); j < sizeof(sudokuArray[0])/sizeof(sudokuArray[0][0]); ++j )
    {
      if ( sudokuArray[i][j] < 1 || sudokuArray[i][j] > 9 )
      {
        result = false;
      }
    }
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testExceptionThrownIfValueLessThanZero()
{
  testFields_.sudokuBoardArray[4][6] = static_cast<short>(-1);

  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Grid point (4,6) has value < 0") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testExceptionThrownIfValueGreaterThanNine()
{
  testFields_.sudokuBoardArray[3][2] = static_cast<short>(10);

  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Grid point (3,2) has value > 9") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testSudokuBoardPopulatedCorrectly()
{
  // Values for grid point x = 0, y = 0.
  const SudokuGridPoint sgp00(generateSudokuGridPoint(0, 0, std::vector<short> {1, 4, 5, 6, 7}));
  // Values for grid point x = 0, y = 2.
  const SudokuGridPoint sgp02(generateSudokuGridPoint(0, 2, 9));
  // Values for grid point x = 5, y = 7.
  const SudokuGridPoint sgp57(generateSudokuGridPoint(5, 7, 5));
  // Values for grid point x = 8, y = 4.
  const SudokuGridPoint sgp84(generateSudokuGridPoint(8, 4, std::vector<short> {6, 8, 9}));

  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(0, 0).shallowEquals(sgp00) );
  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(0, 2).shallowEquals(sgp02) );
  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(5, 7).shallowEquals(sgp57) );
  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(8, 4).shallowEquals(sgp84) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testValidBoardReturnsTrue()
{
  CPPUNIT_ASSERT( subject_->isValidBoard() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testInvalidBoardReturnsFalseForSameNumberInRow()
{
  copyBoardArray(sameNumberInRowBoard, testFields_.sudokuBoardArray);
  
  boost::shared_ptr<SudokuBoard> s(createSubject());

  CPPUNIT_ASSERT( ! s->isValidBoard() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testInvalidBoardReturnsFalseForSameNumberInColumn()
{
  copyBoardArray(sameNumberInColumnBoard, testFields_.sudokuBoardArray);
  
  boost::shared_ptr<SudokuBoard> s(createSubject());

  CPPUNIT_ASSERT( ! s->isValidBoard() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testInvalidBoardReturnsFalseForSameNumberInSquare()
{
  copyBoardArray(sameNumberInSquareBoard, testFields_.sudokuBoardArray);
  
  boost::shared_ptr<SudokuBoard> s(createSubject());

  CPPUNIT_ASSERT( ! s->isValidBoard() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testBoardNotSolvableIfInvalid()
{
  copyBoardArray(sameNumberInSquareBoard, testFields_.sudokuBoardArray);
  
  boost::shared_ptr<SudokuBoard> s(createSubject());

  s->solveBoard();

  CPPUNIT_ASSERT( ! s->isBoardSolvable() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testSolvingGoodBoard()
{
  // Default board is solvable.
  subject_->solveBoard();

  short resultArray[9][9];

  sudokuBoardToArray(subject_->getSudokuBoard(), resultArray);

  // Check it is solvable.
  CPPUNIT_ASSERT( subject_->isBoardSolvable() );

  // Check all values are between 1 and 9.
  CPPUNIT_ASSERT( checkBoardValuesAllSet(resultArray) );

  // Lastly create a new Sudoku board using this array, and check it is valid.
  copyBoardArray(resultArray, testFields_.sudokuBoardArray);

  boost::shared_ptr<SudokuBoard> s(createSubject());

  // A board full of initial values.  If valid it is solved.
  CPPUNIT_ASSERT( s->isValidBoard() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testSolvingZeroesBoard()
{
  copyBoardArray(zeroesBoard, testFields_.sudokuBoardArray);

  boost::shared_ptr<SudokuBoard> subject(createSubject());

  // Board of zeroes should be solvable.
  subject->solveBoard();

  short resultArray[9][9];

  sudokuBoardToArray(subject->getSudokuBoard(), resultArray);

  // Check it is solvable.
  CPPUNIT_ASSERT( subject->isBoardSolvable() );

  // Check all values are between 1 and 9.
  CPPUNIT_ASSERT( checkBoardValuesAllSet(resultArray) );

  // Lastly create a new Sudoku board using this array, and check it is valid.
  copyBoardArray(resultArray, testFields_.sudokuBoardArray);

  boost::shared_ptr<SudokuBoard> s(createSubject());

  // A board full of initial values.  If valid it is solved.
  CPPUNIT_ASSERT( s->isValidBoard() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testBoardValidButNotSolvable()
{
  copyBoardArray(nonSolvableTestBoard, testFields_.sudokuBoardArray);

  boost::shared_ptr<SudokuBoard> subject(createSubject());

  // This board should be valid.
  CPPUNIT_ASSERT( subject->isValidBoard() );

  // Board is not solvable.
  subject->solveBoard();

  // Check it is not solvable.
  CPPUNIT_ASSERT( ! subject->isBoardSolvable() );
  
  // This board should still be valid.
  CPPUNIT_ASSERT( subject->isValidBoard() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::testBoardOrdered()
{
  // Default board is solvable.
  subject_->solveBoard();

  std::vector<SudokuGridPoint> sudokuBoard( subject_->getSudokuBoard() );

  bool result(true);

  for ( std::vector<SudokuGridPoint>::size_type i(0); i < sudokuBoard.size() - 1; ++i )
  {
    if ( sudokuBoard.at(i) > sudokuBoard.at(i + 1) )
    {
      result = false;
    }
  }

  CPPUNIT_ASSERT( result );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
boost::shared_ptr<SudokuBoard> SudokuBoardTest::createSubject()
{
  boost::shared_ptr<SudokuBoard> subject(new SudokuBoard( testFields_.sudokuBoardArray ) );
  return subject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuBoardTest::setUp()
{
  copyBoardArray(testBoard, testFields_.sudokuBoardArray);
  subject_ = createSubject();
}

} // End of namespace sudoku.
