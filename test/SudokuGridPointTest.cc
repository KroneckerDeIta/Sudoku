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
void SudokuGridPointTest::testExceptionThrownIfValueZero()
{
  testFields_.value = zeroValue;
  
  try
  {
    (void)createSubject();

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify value <= 0.") );
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
void SudokuGridPointTest::testExceptionThrownIfValueInPossibleValuesZero()
{
  std::vector<short> possibleValues = {8, 9, 0};
  
  try
  {
    (void)createSubject(possibleValues);

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify a possible value <= 0.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfValueInPossibleValuesTooLarge()
{
  std::vector<short> possibleValues = {8, 9, 10};
  
  try
  {
    (void)createSubject(possibleValues);

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Cannot specify a possible value > 9.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfValueInPossibleValuesRepeated()
{
  std::vector<short> possibleValues = {1, 3, 3};
  
  try
  {
    (void)createSubject(possibleValues);

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Possible values has repeated values.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfPossibleValuesEmpty()
{
  std::vector<short> possibleValues = {};
  
  try
  {
    (void)createSubject(possibleValues);

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() == std::string("Possible values cannot be empty.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGetPossibleValues()
{
  std::vector<short> possibleValues = {1, 2, 3};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  CPPUNIT_ASSERT( std::equal(possibleValues.begin(), possibleValues.end(),
    s->getPossibleValues().begin() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveValueFromPossibleValues()
{
  std::vector<short> possibleValues = {1, 2, 3};
  std::vector<short> possibleValuesRemoved = {1, 3};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // First check method returns that value could be removed.
  CPPUNIT_ASSERT( s->removePossibleValue(2) );

  // Now check values.
  CPPUNIT_ASSERT( std::equal(possibleValuesRemoved.begin(), possibleValuesRemoved.end(),
    s->getPossibleValues().begin() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveOneValueFromTwoFromPossibleValues()
{
  std::vector<short> possibleValues = {1, 2};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);

  // Test that value returned is zero.  It has not been guessed yet.  
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() );

  // First check method returns that value could be removed.
  CPPUNIT_ASSERT( s->removePossibleValue(2) );

  // Now check returned vector of possible values is empty.
  CPPUNIT_ASSERT( s->getPossibleValues().empty() );

  // Then check the value, it should be a guess - 1 in our case.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(1), s->getValue() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveValueWhenInitialValueWasGiven()
{
  // Check that method returns that no value was removed.
  CPPUNIT_ASSERT( ! subject_->removePossibleValue(2) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValue()
{
  std::vector<short> possibleValues = {1, 2, 3};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Remove value.
  s->removePossibleValue(2);
  
  // Restore the value that was just removed.
  CPPUNIT_ASSERT( s->restorePossibleValue(2) );

  std::vector<short> returnValues(s->getPossibleValues());

  // sort the returned values, comparison will fail otherwise.
  std::sort( returnValues.begin(), returnValues.end() );

  // Now check values.
  CPPUNIT_ASSERT( std::equal(possibleValues.begin(), possibleValues.end(),
    returnValues.begin() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueThatIsAlreadyInPossibleValues()
{
  std::vector<short> possibleValues = {1, 2, 3};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Try and restore a value that is still in the possible values.
  try
  {
    // Restore a value that was not removed before.
    s->restorePossibleValue(1);

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() ==
      std::string("Cannot restore value that was not removed previously.") );
  }

  std::vector<short> returnValues(s->getPossibleValues());

  // sort the returned values, comparison will fail otherwise.
  std::sort( returnValues.begin(), returnValues.end() );

  // Now check values.
  CPPUNIT_ASSERT( std::equal(possibleValues.begin(), possibleValues.end(),
    returnValues.begin() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueWhenInitialValueWasGiven()
{
  CPPUNIT_ASSERT( ! subject_->restorePossibleValue(2) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueThatWasAddedToGuessedValues()
{
  std::vector<short> possibleValues = {1, 2};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Remove a value that is still in the possible values.
  s->removePossibleValue(2);

  // Restore the same value.
  s->restorePossibleValue(2);

  // Should return 0 as the value, if 2 has been restored.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() );

  std::vector<short> returnValues(s->getPossibleValues());

  // sort the returned values, comparison will fail otherwise.
  std::sort( returnValues.begin(), returnValues.end() );

  // Now check values.
  CPPUNIT_ASSERT( std::equal(possibleValues.begin(), possibleValues.end(),
    returnValues.begin() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testExceptionThrownIfRestoringValueThatWasNotRemovedBefore()
{
  std::vector<short> possibleValues = {1, 2};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Remove a value that is still in the possible values.
  s->removePossibleValue(2);

  try
  {
    // Restore a value that was not removed before.
    s->restorePossibleValue(1);

    // Should not reach here!
    CPPUNIT_ASSERT(false);
  }
  catch ( std::invalid_argument &e )
  {
    CPPUNIT_ASSERT( e.what() ==
      std::string("Cannot restore value that was not removed previously.") );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGetValueWhenOneValuePassedToConstructor()
{
  std::vector<short> possibleValues = {1};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);

  // Check value is set.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(1), s->getValue() ); 

  // Check possible values vector is empty.
  CPPUNIT_ASSERT( s->getPossibleValues().empty() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
boost::shared_ptr<SudokuGridPoint> SudokuGridPointTest::createSubject()
{
  boost::shared_ptr<SudokuGridPoint> subject(new SudokuGridPoint( testFields_.x, testFields_.y,
    testFields_.value ));
  return subject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
boost::shared_ptr<SudokuGridPoint> SudokuGridPointTest::createSubject(
  const std::vector<short>& possibleValues)
{
  boost::shared_ptr<SudokuGridPoint> subject(new SudokuGridPoint( testFields_.x, testFields_.y,
    possibleValues ));
  return subject;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::setUp()
{
  testFields_.x = validX;
  testFields_.y = validY;
  testFields_.value = validValue;
  subject_ = createSubject();
}

} // End of namespace sudoku.
