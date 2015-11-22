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
  CPPUNIT_TEST(testValidBoardReturnsTrue);
  CPPUNIT_TEST(testInvalidBoardReturnsFalseForSameNumberInRow);
  CPPUNIT_TEST(testInvalidBoardReturnsFalseForSameNumberInColumn);
  CPPUNIT_TEST(testInvalidBoardReturnsFalseForSameNumberInSquare);
  CPPUNIT_TEST(testBoardNotSolvableIfInvalid);
  CPPUNIT_TEST(testSolvingGoodBoard);
  CPPUNIT_TEST(testSolvingZeroesBoard);
  CPPUNIT_TEST(testBoardValidButNotSolvable);
  CPPUNIT_TEST(testBoardOrdered);
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

    // \test Test checking a valid board.
    void testValidBoardReturnsTrue();

    // \test Test checking a none valid board (that has a repeated number in a row).
    void testInvalidBoardReturnsFalseForSameNumberInRow();
    
    // \test Test checking a none valid board (that has a repeated number in a column).
    void testInvalidBoardReturnsFalseForSameNumberInColumn();
    
    // \test Test checking a none valid board (that has a repeated number in a square).
    void testInvalidBoardReturnsFalseForSameNumberInSquare();

    // \test Test the board is not solvable if it is not valid.
    void testBoardNotSolvableIfInvalid();

    // \test Test solving a good board.
    void testSolvingGoodBoard();
    
    // \test Test solving a board with no initial values.
    void testSolvingZeroesBoard();

    // \test Test solving a board that is valid but not solvable.
    void testBoardValidButNotSolvable();

    // \test Test that the Sudoku Board is ordered.
    void testBoardOrdered();

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
