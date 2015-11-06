////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of tests for CheckIfVectorsEqual.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "utilities/src/CheckIfVectorsEqual.h"
#include "CheckIfVectorsEqualTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( sudoku::utilities::CheckIfVectorsEqualTest );

namespace sudoku
{
namespace utilities
{

////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckIfVectorsEqualTest::CheckIfEmptyVectorsEqual()
{
  std::vector<double> emptyVector1;
  std::vector<double> emptyVector2;

  // Might be best not to use the same empty vector to see if equal.
  CPPUNIT_ASSERT(checkIfVectorsEqual(emptyVector1, emptyVector2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckIfVectorsEqualTest::CheckEmptyVectorAndNonEmptyVectorNotEqual()
{
  std::vector<double> emptyVector1;
  std::vector<double> vector1 = {1.0};

  // Check passing arguments into both sides.
  CPPUNIT_ASSERT( ! checkIfVectorsEqual(vector1, emptyVector1));
  CPPUNIT_ASSERT( ! checkIfVectorsEqual(emptyVector1, vector1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckIfVectorsEqualTest::CheckNonEmptyVectorEquality()
{
  std::vector<double> vector1 = {1.0};
  std::vector<double> vector2 = {1.0};
  std::vector<double> vector3 = {1.0, 2.0};
  std::vector<double> vector4 = {2.0, 1.0};
  std::vector<double> vector5 = {1.0, 1.0, 2.0};

  CPPUNIT_ASSERT(checkIfVectorsEqual(vector1, vector2));

  CPPUNIT_ASSERT( ! checkIfVectorsEqual(vector1, vector3));
  CPPUNIT_ASSERT( ! checkIfVectorsEqual(vector3, vector1));

  CPPUNIT_ASSERT(checkIfVectorsEqual(vector3, vector4));
  CPPUNIT_ASSERT(checkIfVectorsEqual(vector4, vector3));

  CPPUNIT_ASSERT( ! checkIfVectorsEqual(vector3, vector5));

  // Make sure the function hasn't sorted the passed vector.
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0, vector4.at(0), 1e-16);
}

} // End of namespace utilities.
} // End of namespace sudoku.

