////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of tests for SudokuAssist.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "src/SudokuAssist.h"
#include "SudokuAssistTest.h"
//#include "SudokuGridPoint.h"
//#include "SudokuGridPointTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( sudoku::SudokuAssistTest );

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
boost::shared_ptr<SudokuAssist> SudokuAssistTest::createSubject()
{
  boost::shared_ptr<SudokuAssist> subject(new SudokuAssist( testFields_.sudokuBoard ) );
  return subject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuAssistTest::setUp()
{
  std::copy(&testBoard[0][0], &testBoard[0][0]+ 9*9, &testFields_.sudokuBoard[0][0]);
  subject_ = createSubject();
}

} // End of namespace sudoku.
