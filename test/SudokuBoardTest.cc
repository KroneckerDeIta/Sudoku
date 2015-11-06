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

namespace sudoku
{

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
  const short testX0(0);
  const short testY0(0);
  const std::vector<short> testPossibleValues00 = {1, 4, 5, 6, 7};
 
  const SudokuGridPoint sgp00(testX0, testY0, testPossibleValues00);

  // Values for grid point x = 0, y = 2.
  const short testY2(2);
  const short testValue02(9);

  const SudokuGridPoint sgp02(testX0, testY2, testValue02);

  // Values for grid point x = 5, y = 7.
  const short testX5(5);
  const short testY7(7);
  const short testValue57(5);
  
  const SudokuGridPoint sgp57(testX5, testY7, testValue57);
  
  // Values for grid point x = 8, y = 4.
  const short testX8(8);
  const short testY4(4);
  const std::vector<short> testPossibleValues84 = {6, 8, 9};

  const SudokuGridPoint sgp84(testX8, testY4, testPossibleValues84);

  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(testX0, testY0).shallowEquals(sgp00) );
  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(testX0, testY2).shallowEquals(sgp02) );
  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(testX5, testY7).shallowEquals(sgp57) );
  CPPUNIT_ASSERT( subject_->getSudokuGridPoint(testX8, testY4).shallowEquals(sgp84) );
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
  std::copy(&testBoard[0][0], &testBoard[0][0]+ 9*9, &testFields_.sudokuBoardArray[0][0]);
  subject_ = createSubject();
}

} // End of namespace sudoku.
