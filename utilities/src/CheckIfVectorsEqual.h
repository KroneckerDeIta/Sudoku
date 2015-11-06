#ifndef __sudoku_testutilities_checkifvectorsequal__
#define __sudoku_testutilities_checkifvectorsequal__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Implementation of checkIfVectorsEqual.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace sudoku
{
namespace utilities
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Checks the equality of two vectors of the same type.
/// \param lhs The first vector to check.
/// \param rhs The second vector to check.
/// \return true if vectors are equal, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool checkIfVectorsEqual( const std::vector<T>& lhs, const std::vector<T>& rhs )
{
  bool result(false);
  
  // Make copies of the vectors first.
  std::vector<T> lhsCopy;
  std::vector<T> rhsCopy;

  std::copy(lhs.begin(), lhs.end(), back_inserter(lhsCopy));
  std::copy(rhs.begin(), rhs.end(), back_inserter(rhsCopy));

  // First check the size.
  result = ( lhsCopy.size() == rhsCopy.size() );

  if (result)
  {
    // They are the same size, now sort the vectors ready for checking equality.
    std::sort(lhsCopy.begin(), lhsCopy.end());
    std::sort(rhsCopy.begin(), rhsCopy.end());

    // Check equality.
    result = std::equal(lhsCopy.begin(), lhsCopy.end(), rhsCopy.begin());
  }

  return result;
}

} // End of namespace utilities.
} // End of namespace sudoku.

#endif
