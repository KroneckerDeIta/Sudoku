#ifndef __sudoku_sudokugridpointtest_h__
#define __sudoku_sudokugridpointtest_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Declaration of tests for SudokuGridPoint.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "SudokuGridPoint.h"

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief SudokuGridPointTest class for testing SudokuGridPoint.
////////////////////////////////////////////////////////////////////////////////////////////////////
class SudokuGridPointTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(SudokuGridPointTest);
  CPPUNIT_TEST(testExceptionThrownIfXNegative);
  CPPUNIT_TEST(testExceptionThrownIfYNegative);
  CPPUNIT_TEST(testExceptionThrownIfXTooLarge);
  CPPUNIT_TEST(testExceptionThrownIfYTooLarge);
  CPPUNIT_TEST(testExceptionThrownIfValueZero);
  CPPUNIT_TEST(testExceptionThrownIfValueTooLarge);
  CPPUNIT_TEST(testGetX);
  CPPUNIT_TEST(testGetY);
  CPPUNIT_TEST(testGetValue);
  CPPUNIT_TEST(testExceptionThrownIfValueInPossibleValuesZero);
  CPPUNIT_TEST(testExceptionThrownIfValueInPossibleValuesTooLarge);
  CPPUNIT_TEST(testExceptionThrownIfValueInPossibleValuesRepeated);
  CPPUNIT_TEST(testExceptionThrownIfPossibleValuesEmpty);
  CPPUNIT_TEST(testGetPossibleValues);
  CPPUNIT_TEST(testRemoveValueFromPossibleValuesForSameXY);
  CPPUNIT_TEST(testRemoveValueFromPossibleValuesFailedDueToXYNotInRowColOrBox);
  CPPUNIT_TEST(testRemoveOneValueFromTwoFromPossibleValues);
  CPPUNIT_TEST(testRemoveValueWhenInitialValueWasGiven);
  CPPUNIT_TEST(testRestorePossibleValue);
  CPPUNIT_TEST(testRestorePossibleValueFailsIfXDifferentFromOneRecorded);
  CPPUNIT_TEST(testRestorePossibleValueFailsIfYDifferentFromOneRecorded);
  CPPUNIT_TEST(testRestorePossibleValueThatIsAlreadyInPossibleValues);
  CPPUNIT_TEST(testRestorePossibleValueWhenInitialValueWasGiven);
  CPPUNIT_TEST(testRestorePossibleValueThatWasAddedToGuessedValues);
  CPPUNIT_TEST(testGetValueWhenOneValuePassedToConstructor);
  CPPUNIT_TEST(testEqualityOfTwoSudokuGridPointObjects);
  CPPUNIT_TEST(testLessThanOfSudokuGridPointObjects);
  CPPUNIT_TEST(testNotEqualOperatorSudokuGridPointObjects);
  CPPUNIT_TEST(testLessThanOrEqualToOperatorSudokuGridPointObjects);
  CPPUNIT_TEST(testGreaterThanOperatorSudokuGridPointObjects);
  CPPUNIT_TEST(testGreaterThanOrEqualToOperatorSudokuGridPointObjects);
  CPPUNIT_TEST(testGetAffectedGridPoints);
  CPPUNIT_TEST_SUITE_END();
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Public methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  public:
    void setUp();
    //void tearDown();
    
    /// \test Test exception is thrown if x is negative.
    void testExceptionThrownIfXNegative();
    
    /// \test Test exception is thrown if y is negative.
    void testExceptionThrownIfYNegative();

    /// \test Test exception is thrown if x is too large.
    void testExceptionThrownIfXTooLarge();
    
    /// \test Test exception is thrown if y is too large.
    void testExceptionThrownIfYTooLarge();
    
    /// \test Test exception is thrown if value is zero.
    void testExceptionThrownIfValueZero();
    
    /// \test Test exception is thrown if value is too large.
    void testExceptionThrownIfValueTooLarge();

    /// \test Test getting a valid ordinate x.
    void testGetX();
    
    /// \test Test getting a valid ordinate y.
    void testGetY();

    /// \test Test getting a valid value.
    void testGetValue();

    /// \test Test exception thrown if value in possible values is zero.
    void testExceptionThrownIfValueInPossibleValuesZero();
    
    /// \test Test exception thrown if value in possible values is too large.
    void testExceptionThrownIfValueInPossibleValuesTooLarge();
  
    /// \test Test exception thrown if values in possibleValues are repeated.
    void testExceptionThrownIfValueInPossibleValuesRepeated();

    /// \test Test exception thrown if values in possibleValues are repeated.
    void testExceptionThrownIfPossibleValuesEmpty();
 
    /// \test Test getting possible values.
    void testGetPossibleValues();
    
    /// \test Test removing a value from possible values if x and y are the same.
    void testRemoveValueFromPossibleValuesForSameXY();
    
    /// \test Test removing a value fails since the x and y coordinate does not exist in the same
    /// row or column or sudoku box that the SudokuGridPoints's does.
    void testRemoveValueFromPossibleValuesFailedDueToXYNotInRowColOrBox();
    
    /// \test Test removing an element for possible values, when only two values remain. 
    void testRemoveOneValueFromTwoFromPossibleValues();

    /// \test Test removing a value when an initial value was given.
    void testRemoveValueWhenInitialValueWasGiven();

    /// \test Test restoring a possible value that was removed previously.
    void testRestorePossibleValue();
    
    /// \test Test restoring a possible value not possible if x is different to one before.
    void testRestorePossibleValueFailsIfXDifferentFromOneRecorded();
    
    /// \test Test restoring a possible value not possible if y is different to one before.
    void testRestorePossibleValueFailsIfYDifferentFromOneRecorded();

    /// \test Test restoring a possible value that is already in the list of possbile values.
    void testRestorePossibleValueThatIsAlreadyInPossibleValues();
    
    /// \test Test restoring a possible value when an initial value was given.
    void testRestorePossibleValueWhenInitialValueWasGiven();

    /// \test Test that restoring a possible value that was added to guessed values restores 
    /// possible values to its original state.
    void testRestorePossibleValueThatWasAddedToGuessedValues();

    /// \test Test that valid value is returned if one value passed to possible values.
    void testGetValueWhenOneValuePassedToConstructor();
  
    /// \test Test equality operator.
    void testEqualityOfTwoSudokuGridPointObjects();

    /// \test Test less than operator.
    void testLessThanOfSudokuGridPointObjects();

    /// \test Test not equal to operator.
    void testNotEqualOperatorSudokuGridPointObjects();

    /// \test Test less than or equal to operator.
    void testLessThanOrEqualToOperatorSudokuGridPointObjects();

    /// \test Test greater than operator.
    void testGreaterThanOperatorSudokuGridPointObjects();

    /// \test Test greater than or equal to operator.
    void testGreaterThanOrEqualToOperatorSudokuGridPointObjects();

    /// \test Test getting all the grid points affected by the current grid point on the board.
    void testGetAffectedGridPoints();

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private types and variables.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    /// \brief struct containing variables that will be used to initialise subject.
    struct TestFields {
      short x;
      short y;
      short value;
    };
    
    boost::shared_ptr<SudokuGridPoint> subject_; // subject used for testing.
    TestFields testFields_; // Will contain variables used for testing.
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    boost::shared_ptr<SudokuGridPoint> createSubject(); // Method used to create subject.
    // Method used to create subject with possible values.
    boost::shared_ptr<SudokuGridPoint> createSubject(const std::vector<short>& possibleValues);
};

} // End of namespace sudoku.

#endif
