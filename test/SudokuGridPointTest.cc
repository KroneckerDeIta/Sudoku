////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of tests for SudokuGridPoint.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>

#include "src/SudokuGridPoint.h"
#include "SudokuGridPointTest.h"
#include "utilities/src/CheckIfVectorsEqual.h"

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
void SudokuGridPointTest::testRemoveValueFromPossibleValuesForSameXY()
{
  std::vector<short> possibleValues = {1, 2, 3};
  std::vector<short> possibleValuesRemoved = {1, 3};
  const short testX = 1;
  const short testY = 2;
  const short testValue = 2;  

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // First check method returns that value could be removed, but it wasn't the last one.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(1), s->removePossibleValue(testX, testY, testValue) );

  // Now check values.
  CPPUNIT_ASSERT( std::equal(possibleValuesRemoved.begin(), possibleValuesRemoved.end(),
    s->getPossibleValues().begin() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveValueFromPossibleValuesFailedDueToXYNotInRowColOrBox()
{
  std::vector<short> possibleValues = {1, 2, 3};
  const short testX = 2;
  const short testY = 3;
  const short testValue = 2;  

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // First check method returns that value could not be removed.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(2), s->removePossibleValue(testX, testY, testValue) );
  
  // Now check values to make sure nothing was removed.
  CPPUNIT_ASSERT( std::equal(possibleValues.begin(), possibleValues.end(),
    s->getPossibleValues().begin() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveOneValueFromTwoFromPossibleValues()
{
  std::vector<short> possibleValues = {1, 2};
  std::vector<short> removedPossibleValues = {1};
  const short testValue = 2;  

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);

  // Test that value returned is zero.  
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() );
  
  // First check method returns that value could be removed, but it wasn't the last possible value.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(1),  s->removePossibleValue(testFields_.x, testFields_.y,
    testValue) );

  // Check there is one value left in the possible values.
  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(removedPossibleValues,
    s->getPossibleValues()));

  // Then check the value, it should be 0 still.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveOneValueFromOneFromPossibleValues()
{
  std::vector<short> possibleValues = {2};
  std::vector<short> emptyVector;
  const short testValue = 2;  

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);

  // Test that value returned is zero.  It has not been guessed yet.  
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() );
  
  // First check method returns that value could be removed, and that it was the last one.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->removePossibleValue(testFields_.x, testFields_.y,
    testValue) );

  // Check there is are no values left.
  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(emptyVector, s->getPossibleValues()));

  // Then check the value, it should be a guess - 2 in our case.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(2), s->getValue() );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveValueWhenInitialValueWasGiven()
{
  // Give some values inside the same box.
  const short testX = 0;
  const short testY = 0;
  const short testValue = 2;

  // Check that method returns that no value was removed.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(2), subject_->removePossibleValue(testX, testY,
    testValue) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValue()
{
  std::vector<short> possibleValues = {1, 2, 3};
  const short testX = 2;
  const short testY = 1;
  const short testValue = 2;

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Remove value.
  s->removePossibleValue(testX, testY, testValue);
  
  // Restore the value that was just removed.
  CPPUNIT_ASSERT( s->restorePossibleValue(testX, testY, testValue) );

  std::vector<short> returnValues(s->getPossibleValues());

  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(possibleValues, returnValues) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueFailsIfXDifferentFromOneRecorded()
{
  std::vector<short> possibleValues = {1, 2, 3};
  std::vector<short> removedPossibleValues = {1, 3};
  const short testX = 2;
  const short otherX = 3;
  const short testY = 1;
  const short testValue = 2;

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Remove value.
  s->removePossibleValue(testX, testY, testValue);
  
  // Test that restoring not possible as input x is different.
  CPPUNIT_ASSERT( ! s->restorePossibleValue(otherX, testY, testValue) );

  std::vector<short> returnValues(s->getPossibleValues());

  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(removedPossibleValues, returnValues) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueFailsIfYDifferentFromOneRecorded()
{
  std::vector<short> possibleValues = {1, 2, 3};
  std::vector<short> removedPossibleValues = {1, 3};
  const short testX = 2;
  const short testY = 1;
  const short otherY = 2;
  const short testValue = 2;

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Remove value.
  s->removePossibleValue(testX, testY, testValue);
  
  // Test that restoring not possible as input x is different.
  CPPUNIT_ASSERT( ! s->restorePossibleValue(testX, otherY, testValue) );

  std::vector<short> returnValues(s->getPossibleValues());

  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(removedPossibleValues, returnValues) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueThatIsAlreadyInPossibleValues()
{
  std::vector<short> possibleValues = {1, 2, 3};
  const short testX = 2;
  const short testY = 1;
  const short testValue = 1;
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Check restoring a value that was not removed before returns false.
  CPPUNIT_ASSERT( ! s->restorePossibleValue(testX, testY, testValue) );

  std::vector<short> returnValues(s->getPossibleValues());

  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(possibleValues, returnValues) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueWhenInitialValueWasGiven()
{
  const short testX = 2;
  const short testY = 1;
  const short testValue = 1;

  CPPUNIT_ASSERT( ! subject_->restorePossibleValue(testX, testY, testValue) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRestorePossibleValueThatWasAddedToGuessedValues()
{
  std::vector<short> possibleValues = {1, 2};
  std::vector<short> removedPossibleValues = {1};
  const short testX(2);
  const short testY(2);
  const short testValue1 = 1;
  const short testValue2 = 2;
 
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);
  
  // Remove a value that is still in the possible values.
  s->removePossibleValue(testX, testY, testValue1); 
  s->removePossibleValue(testFields_.x, testFields_.y, testValue2);

  // Make sure 2 has been added as a guess.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(2), s->getValue() );

  // Restore the value 1 now though.
  s->restorePossibleValue(testX, testY , testValue1);

  // Should return 0 as the value, if 1 has been restored.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() );

  std::vector<short> returnValues(s->getPossibleValues());

  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(removedPossibleValues, returnValues) );

  // Finally restore 2 as well.
  s->restorePossibleValue(testFields_.x, testFields_.y, testValue2);
  
  returnValues = s->getPossibleValues();

  // Check we have what we originally had.
  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(possibleValues, returnValues) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGetValueWhenOneValuePassedToConstructor()
{
  std::vector<short> possibleValues = {1};
  
  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);

  // Check value is set.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() ); 

  // Check possible values vector is empty.
  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(possibleValues,
    s->getPossibleValues()) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testEqualityOfTwoSudokuGridPointObjects()
{
  boost::shared_ptr<SudokuGridPoint> sInitial(createSubject());

  std::vector<short> possibleValuesOne1 = {1};
  boost::shared_ptr<SudokuGridPoint> sOnePossible1(createSubject(possibleValuesOne1));
  
  std::vector<short> possibleValuesOne2 = {2};
  boost::shared_ptr<SudokuGridPoint> sOnePossible2(createSubject(possibleValuesOne2));
  
  std::vector<short> possibleValuesTwo = {1, 2};
  boost::shared_ptr<SudokuGridPoint> sTwoPossibles(createSubject(possibleValuesTwo));

  CPPUNIT_ASSERT( *sInitial == *subject_ );
  CPPUNIT_ASSERT( ! (*sOnePossible1 == *subject_) );
  CPPUNIT_ASSERT( *sOnePossible1 == *sOnePossible2 );
  CPPUNIT_ASSERT( ! (*sOnePossible1 == *sTwoPossibles) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testLessThanOfSudokuGridPointObjects()
{
  boost::shared_ptr<SudokuGridPoint> sInitial(createSubject());

  std::vector<short> possibleValuesOne1 = {1};
  boost::shared_ptr<SudokuGridPoint> sOnePossible1(createSubject(possibleValuesOne1));
  
  std::vector<short> possibleValuesOne2 = {2};
  boost::shared_ptr<SudokuGridPoint> sOnePossible2(createSubject(possibleValuesOne2));
  
  std::vector<short> possibleValuesTwo = {1, 2};
  boost::shared_ptr<SudokuGridPoint> sTwoPossibles(createSubject(possibleValuesTwo));

  CPPUNIT_ASSERT( ! (*sInitial < *subject_) );
  CPPUNIT_ASSERT( *subject_ < *sOnePossible1 );
  CPPUNIT_ASSERT( ! (*sOnePossible1 < *subject_) );
  CPPUNIT_ASSERT( ! (*sOnePossible1 < *sOnePossible2) );
  CPPUNIT_ASSERT( *sOnePossible1 < *sTwoPossibles );
  CPPUNIT_ASSERT( ! (*sTwoPossibles < *sOnePossible1) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testNotEqualOperatorSudokuGridPointObjects()
{
  boost::shared_ptr<SudokuGridPoint> sInitial(createSubject());

  std::vector<short> possibleValuesOne1 = {1};
  boost::shared_ptr<SudokuGridPoint> sOnePossible1(createSubject(possibleValuesOne1));
  
  std::vector<short> possibleValuesOne2 = {2};
  boost::shared_ptr<SudokuGridPoint> sOnePossible2(createSubject(possibleValuesOne2));
  
  std::vector<short> possibleValuesTwo = {1, 2};
  boost::shared_ptr<SudokuGridPoint> sTwoPossibles(createSubject(possibleValuesTwo));

  CPPUNIT_ASSERT( ! (*sInitial != *subject_) );
  CPPUNIT_ASSERT( *subject_ != *sOnePossible1 );
  CPPUNIT_ASSERT( ! (*sOnePossible1 != *sOnePossible2) );
  CPPUNIT_ASSERT( *sOnePossible1 != *sTwoPossibles );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testLessThanOrEqualToOperatorSudokuGridPointObjects()
{
  boost::shared_ptr<SudokuGridPoint> sInitial(createSubject());

  std::vector<short> possibleValuesOne1 = {1};
  boost::shared_ptr<SudokuGridPoint> sOnePossible1(createSubject(possibleValuesOne1));
  
  std::vector<short> possibleValuesOne2 = {2};
  boost::shared_ptr<SudokuGridPoint> sOnePossible2(createSubject(possibleValuesOne2));
  
  std::vector<short> possibleValuesTwo = {1, 2};
  boost::shared_ptr<SudokuGridPoint> sTwoPossibles(createSubject(possibleValuesTwo));

  CPPUNIT_ASSERT( *sInitial <= *subject_ );
  CPPUNIT_ASSERT( *subject_ <= *sOnePossible1 );
  CPPUNIT_ASSERT( ! (*sOnePossible1 <= *subject_) );
  CPPUNIT_ASSERT( *sOnePossible1 <= *sOnePossible2 );
  CPPUNIT_ASSERT( *sOnePossible1 <= *sTwoPossibles );
  CPPUNIT_ASSERT( ! (*sTwoPossibles <= *sOnePossible1) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGreaterThanOperatorSudokuGridPointObjects()
{
  boost::shared_ptr<SudokuGridPoint> sInitial(createSubject());

  std::vector<short> possibleValuesOne1 = {1};
  boost::shared_ptr<SudokuGridPoint> sOnePossible1(createSubject(possibleValuesOne1));
  
  std::vector<short> possibleValuesOne2 = {2};
  boost::shared_ptr<SudokuGridPoint> sOnePossible2(createSubject(possibleValuesOne2));
  
  std::vector<short> possibleValuesTwo = {1, 2};
  boost::shared_ptr<SudokuGridPoint> sTwoPossibles(createSubject(possibleValuesTwo));

  CPPUNIT_ASSERT( ! (*sInitial > *subject_) );
  CPPUNIT_ASSERT( ! (*subject_ > *sOnePossible1) );
  CPPUNIT_ASSERT( *sOnePossible1 > *subject_ );
  CPPUNIT_ASSERT( ! (*sOnePossible1 > *sOnePossible2) );
  CPPUNIT_ASSERT( ! (*sOnePossible1 > *sTwoPossibles) );
  CPPUNIT_ASSERT( *sTwoPossibles > *sOnePossible1 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGreaterThanOrEqualToOperatorSudokuGridPointObjects()
{
  boost::shared_ptr<SudokuGridPoint> sInitial(createSubject());

  std::vector<short> possibleValuesOne1 = {1};
  boost::shared_ptr<SudokuGridPoint> sOnePossible1(createSubject(possibleValuesOne1));
  
  std::vector<short> possibleValuesOne2 = {2};
  boost::shared_ptr<SudokuGridPoint> sOnePossible2(createSubject(possibleValuesOne2));
  
  std::vector<short> possibleValuesTwo = {1, 2};
  boost::shared_ptr<SudokuGridPoint> sTwoPossibles(createSubject(possibleValuesTwo));

  CPPUNIT_ASSERT( *sInitial >= *subject_ );
  CPPUNIT_ASSERT( ! (*subject_ >= *sOnePossible1) );
  CPPUNIT_ASSERT( *sOnePossible1 >= *subject_ );
  CPPUNIT_ASSERT( *sOnePossible1 >= *sOnePossible2 );
  CPPUNIT_ASSERT( ! (*sOnePossible1 >= *sTwoPossibles) );
  CPPUNIT_ASSERT( *sTwoPossibles >= *sOnePossible1 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testGetAffectedGridPoints()
{
  std::vector<std::pair<short, short> > myVecX1Y2 = { {1, 0}, {1, 1}, {1, 3}, {1, 4}, {1, 5},
                                                      {1, 6}, {1, 7}, {1, 8}, {0, 2}, {2, 2},
                                                      {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2},
                                                      {8, 2}, {0, 0}, {0, 1}, {2, 0}, {2, 1} };
  testFields_.x = 1;
  testFields_.y = 2;
  boost::shared_ptr<SudokuGridPoint> subjectX1Y2(createSubject());
 
  std::vector<std::pair<short, short> > myVecX4Y4 = { {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 5},
                                                      {4, 6}, {4, 7}, {4, 8}, {0, 4}, {1, 4},
                                                      {2, 4}, {3, 4}, {5, 4}, {6, 4}, {7, 4},
                                                      {8, 4}, {3, 3}, {3, 5}, {5, 3}, {5, 5} };
  testFields_.x = 4;
  testFields_.y = 4;
  boost::shared_ptr<SudokuGridPoint> subjectX4Y4(createSubject());

  std::vector<std::pair<short, short> > myVecX6Y5 = { {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4},
                                                      {6, 6}, {6, 7}, {6, 8}, {0, 5}, {1, 5},
                                                      {2, 5}, {3, 5}, {4, 5}, {5, 5}, {7, 5},
                                                      {8, 5}, {7, 3}, {7, 4}, {8, 3}, {8, 4} };
  testFields_.x = 6;
  testFields_.y = 5;
  boost::shared_ptr<SudokuGridPoint> subjectX6Y5(createSubject());

  CPPUNIT_ASSERT( (utilities::checkIfVectorsEqual<std::pair<short, short> >(
    subjectX1Y2->getAffectedGridPoints(), myVecX1Y2 )));
  
  CPPUNIT_ASSERT( (utilities::checkIfVectorsEqual<std::pair<short, short> >(
    subjectX4Y4->getAffectedGridPoints(), myVecX4Y4 )));
  
  CPPUNIT_ASSERT( (utilities::checkIfVectorsEqual<std::pair<short, short> >(
    subjectX6Y5->getAffectedGridPoints(), myVecX6Y5 )));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testSudokuGridPointsShallowEqualsMethod()
{
  std::vector<short> testPossibleValues1 = {1, 2};
  std::vector<short> testPossibleValues2 = {1, 3};
  const short testX1(5);
  const short testX2(6);
  const short testY1(6);
  const short testY2(7);
  const short testValue1(8);
  const short testValue2(4);

  testFields_.x = testX1;
  testFields_.y = testY1;
  testFields_.value = testValue1;

  boost::shared_ptr<SudokuGridPoint> s1(createSubject());
  boost::shared_ptr<SudokuGridPoint> s2(createSubject());
  boost::shared_ptr<SudokuGridPoint> s3(createSubject(testPossibleValues1));
  boost::shared_ptr<SudokuGridPoint> s4(createSubject(testPossibleValues1));
  boost::shared_ptr<SudokuGridPoint> s5(createSubject(testPossibleValues2));

  testFields_.x = testX2;
  testFields_.y = testY1;
  testFields_.value = testValue1;
  
  boost::shared_ptr<SudokuGridPoint> s6(createSubject());
  
  testFields_.x = testX1;
  testFields_.y = testY2;
  testFields_.value = testValue1;
  
  boost::shared_ptr<SudokuGridPoint> s7(createSubject());
  
  testFields_.x = testX1;
  testFields_.y = testY1;
  testFields_.value = testValue2;

  boost::shared_ptr<SudokuGridPoint> s8(createSubject());

  // Not all possible combinations.  But enough for TDD.
  CPPUNIT_ASSERT(s1->shallowEquals(*s2));
  CPPUNIT_ASSERT(s3->shallowEquals(*s4));
  CPPUNIT_ASSERT(! s1->shallowEquals(*s3));
  CPPUNIT_ASSERT(! s3->shallowEquals(*s5));
  CPPUNIT_ASSERT(! s1->shallowEquals(*s6));
  CPPUNIT_ASSERT(! s1->shallowEquals(*s7));
  CPPUNIT_ASSERT(! s1->shallowEquals(*s8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuGridPointTest::testRemoveFromOnePossibleValueButNotSameGridPoint()
{
  std::vector<short> possibleValues = {2};
  // Same box as SudokuGridPoint's.
  const short testX(0);
  const short testY(0);
  const short testValue = 2;  

  boost::shared_ptr<SudokuGridPoint> s = createSubject(possibleValues);

  // First check method returns that value could not be removed, since it was the last value and 
  // the x and y are not the same as the SudokuGridPoint's.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(3), s->removePossibleValue(testX, testY, testValue) );

  // Check the possible values are the same.
  CPPUNIT_ASSERT( utilities::checkIfVectorsEqual<short>(possibleValues, s->getPossibleValues()));

  // Then check the value, it should be the same, i.e. 0.
  CPPUNIT_ASSERT_EQUAL( static_cast<short>(0), s->getValue() );
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
