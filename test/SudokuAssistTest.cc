#include <algorithm>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "SudokuAssist.h"
#include "SudokuAssistTest.h"
//#include "SudokuGridPoint.h"
//#include "SudokuGridPointTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( sudoku::SudokuAssistTest );

// Define some ordinates.
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
void SudokuAssistTest::testGetPossibleValues()
{
  bool result(false);
  std::vector<short> resultVector();
  
  std::vector<short> vec00 = { 1, 4, 5, 6, 7 }; // Top left.
  std::vector<short> vec13 = { 2, 6, 9 }; // Top centre.
  std::vector<short> vec07 = { 1, 2, 7, 8 }; // Top right.
  std::vector<short> vec52 = { 1, 3, 4, 6, 7, 8 }; // Middle right.
  std::vector<short> vec35 = { 4, 5, 8 }; // Middle centre.
  std::vector<short> vec48 = { 2, 8 }; // Middle right.
  std::vector<short> vec80 = { 1, 7, 9 }; // Bottom left.
  std::vector<short> vec75 = { 2 }; // Bottom centre.
  std::vector<short> vec88 = { 1, 6, 7, 8 }; // Bottom right.
  
  //result = getPossibleValues(testBoard, 0, 0, resultVector);

  //CPPUNIT_ASSERT(result);
  //CPPUNIT_ASSERT( resultVector.size() == vec00.size() );
  //CPPUNIT_ASSERT(std::equal( vec00.begin(), vec00.end(), resultVector.begin() ));
}

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
