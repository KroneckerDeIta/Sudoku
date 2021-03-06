#ifndef __sudoku_checkifvectorsequaltest_h__
#define __sudoku_checkifvectorsequaltest_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Declaration of tests for CheckIfVectorsEqual.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "utilities/src/CheckIfVectorsEqual.h"

namespace sudoku
{
namespace utilities
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief CheckIfVectorsEqualTest class for testing CheckIfVectorsEqual.
////////////////////////////////////////////////////////////////////////////////////////////////////
class CheckIfVectorsEqualTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CheckIfVectorsEqualTest);
  CPPUNIT_TEST(CheckIfEmptyVectorsEqual);
  CPPUNIT_TEST(CheckEmptyVectorAndNonEmptyVectorNotEqual);
  CPPUNIT_TEST(CheckNonEmptyVectorEquality);
  CPPUNIT_TEST_SUITE_END();
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Public methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  public:
      // \test Test if two empty vectors are equal.
      void CheckIfEmptyVectorsEqual();

      // \test Test that a non empty and empty vector are not equal.
      void CheckEmptyVectorAndNonEmptyVectorNotEqual();

      // \test Test various non-empty vectors to see if they are equal.
      void CheckNonEmptyVectorEquality();

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private types and variables.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
};

} // End of namespace utilities.
} // End of namespace sudoku.

#endif
