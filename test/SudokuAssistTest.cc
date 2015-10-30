////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of tests for SudokuAssist.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

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

template<typename T>
bool checkIfVectorsEqual( std::vector<T> lhs, std::vector<T> rhs )
{
  // Sort the vectors ready for checking equality.
  std::sort(lhs.begin(),lhs.end());
  std::sort(rhs.begin(),rhs.end());

  // Now check for equaltiy.
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuAssistTest::testGetPossibleValues()
{
  std::vector<short> resultVector;
  
  std::vector<short> vec00 = { 1, 4, 5, 6, 7 }; // Top left.
  std::vector<short> vec13 = { 2, 6, 9 }; // Top centre.
  std::vector<short> vec07 = { 1, 2, 7, 8 }; // Top right.
  std::vector<short> vec52 = { 1, 3, 4, 6, 7, 8 }; // Middle right.
  std::vector<short> vec35 = { 4, 5, 8 }; // Middle centre.
  std::vector<short> vec48 = { 2, 8 }; // Middle right.
  std::vector<short> vec80 = { 1, 7, 9 }; // Bottom left.
  std::vector<short> vec75 = { 2 }; // Bottom centre.
  std::vector<short> vec88 = { 1, 6, 7, 8 }; // Bottom right.
  
  CPPUNIT_ASSERT( getPossibleValues(testBoard, static_cast<short>(0), static_cast<short>(0),
    resultVector) );

  //CPPUNIT_ASSERT( checkIfVectorsEqual<short>(vec00, resultVector) );
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
