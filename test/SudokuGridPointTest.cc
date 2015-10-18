#include <boost/shared_ptr.hpp>

#include "SudokuGridPoint.h"
#include "SudokuGridPointTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( sudoku::SudokuGridPointTest );

// Define some ordinates.
const short negativeX(-1);
const short negativeY(-1);
const short validX(1);
const short validY(2);
const short tooLargeX(9);
const short tooLargeY(9);

// Define some values.
const short negativeValue(-1);
const short zeroValue(0);
const short validValue(3);
const short tooLargeValue(10);

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfXNegative()
{
  testFields_.x = negativeX;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify a negative x ordinate.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfYNegative()
{
  testFields_.y = negativeY;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify a negative y ordinate.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfXTooLarge()
{
  testFields_.x = tooLargeX;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify an x ordinate > 8.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfYTooLarge()
{
  testFields_.y = tooLargeY;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify an y ordinate > 8.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfValueNegative()
{
  testFields_.value = negativeValue;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify a negative value.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfValueTooLarge()
{
  testFields_.value = tooLargeValue;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify a value > 9.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfValueZeroAndInitialValueTrue()
{
  testFields_.value = zeroValue;
  testFields_.initialValue = true;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot have a zero value and be an initial value.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGetX()
{
  CPPUNIT_ASSERT_EQUAL( validX, subject_->getX() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGetY()
{
  CPPUNIT_ASSERT_EQUAL( validY, subject_->getY() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGetValue()
{
  CPPUNIT_ASSERT_EQUAL( validValue, subject_->getValue() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testIsInitialValue()
{
  CPPUNIT_ASSERT_EQUAL( false, subject_->isInitialValue() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
boost::shared_ptr<SudokuGridPoint> SudokuGridPointTest::createSubject()
{
  boost::shared_ptr<SudokuGridPoint> subject(new SudokuGridPoint( testFields_.x, testFields_.y,
    testFields_.value, testFields_.initialValue ));
  return subject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::setUp()
{
  testFields_.x = validX;
  testFields_.y = validY;
  testFields_.value = validValue;
  testFields_.initialValue = false;
  subject_ = createSubject();
}

} // End of namespace sudoku.
