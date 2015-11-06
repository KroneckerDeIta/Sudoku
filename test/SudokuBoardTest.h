#ifndef __sudoku_sudokuboardtest_h__
#define __sudoku_sudokuboardtest_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Declaration of tests for SudokuBoard.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "src/SudokuBoard.h"
//#include "SudokuGridPoint.h"

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief SudokuBoardTest class for testing SudokuBoard.
////////////////////////////////////////////////////////////////////////////////////////////////////
class SudokuBoardTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(SudokuBoardTest);
  CPPUNIT_TEST(testExceptionThrownIfValueLessThanZero);
  CPPUNIT_TEST(testExceptionThrownIfValueGreaterThanNine);
  CPPUNIT_TEST(testSudokuBoardPopulatedCorrectly);
  CPPUNIT_TEST_SUITE_END();
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Public methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  public:
    void setUp();
    //void tearDown();

    // \test Test that an excpetion is thrown if a value is less than 0 in the initial board.
    void testExceptionThrownIfValueLessThanZero();

    // \test Test that an exception is thrown if a value is greater than 9 in the initial board.
    void testExceptionThrownIfValueGreaterThanNine();

    // \test Test that the initial board is populated correctly.
    void testSudokuBoardPopulatedCorrectly();

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private types and variables.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    /// \brief struct containing variables that will be used to initialise subject.
    struct TestFields {
      short sudokuBoardArray[9][9];
    };
    
    boost::shared_ptr<SudokuBoard> subject_; // subject used for testing.
    TestFields testFields_; // Will contain variables used for testing.
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    boost::shared_ptr<SudokuBoard> createSubject(); // Method used to create subject.
};

} // End of namespace sudoku.

#endif
