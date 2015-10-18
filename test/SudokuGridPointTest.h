#ifndef __sudoku_sudokugridpointtest_h__
#define __sudoku_sudokugridpointtest_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Contains tests for SudokuGridPoint.
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
  CPPUNIT_TEST(testExceptionThrownIfValueNegative);
  CPPUNIT_TEST(testExceptionThrownIfValueTooLarge);
  CPPUNIT_TEST(testExceptionThrownIfValueZeroAndInitialValueTrue);
  CPPUNIT_TEST(testGetX);
  CPPUNIT_TEST(testGetY);
  CPPUNIT_TEST(testGetValue);
  CPPUNIT_TEST(testIsInitialValue);
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
    
    /// \test Test exception is thrown if value is negative.
    void testExceptionThrownIfValueNegative();
    
    /// \test Test exception is thrown if value is too large.
    void testExceptionThrownIfValueTooLarge();
    
    /// \test Test exception is thrown if value is zero and set to be an initial value.
    void testExceptionThrownIfValueZeroAndInitialValueTrue();

    /// \test Test getting a valid ordinate x.
    void testGetX();
    
    /// \test Test getting a valid ordinate y.
    void testGetY();

    /// \test Test getting a valid value.
    void testGetValue();
    
    /// \test Test is initial value.
    void testIsInitialValue();
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private types and variables.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    /// \brief struct containing variables that will be used to initialise subject.
    struct TestFields {
      short x;
      short y;
      short value;
      bool initialValue;
    };
    
    boost::shared_ptr<SudokuGridPoint> subject_; // subject used for testing.
    TestFields testFields_; // Will contain variables used for testing.
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    boost::shared_ptr<SudokuGridPoint> createSubject(); // Method used to create subject.
};

} // End of namespace sudoku.

#endif
