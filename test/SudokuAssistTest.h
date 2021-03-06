#ifndef __sudoku_sudokuassisttest_h__
#define __sudoku_sudokuassisttest_h__

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Declaration of tests for SudokuGridPoint.
/// \author anon
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "src/SudokuAssist.h"
//#include "SudokuGridPoint.h"

namespace sudoku
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief SudokuAssistTest class for testing SudokuAssist.
////////////////////////////////////////////////////////////////////////////////////////////////////
class SudokuAssistTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(SudokuAssistTest);
  CPPUNIT_TEST_SUITE_END();
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Public methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  public:
    void setUp();
    //void tearDown();

  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private types and variables.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    /// \brief struct containing variables that will be used to initialise subject.
    struct TestFields {
    };
    
    boost::shared_ptr<SudokuAssist> subject_; // subject used for testing.
    TestFields testFields_; // Will contain variables used for testing.
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  /// Private methods.
  //////////////////////////////////////////////////////////////////////////////////////////////////
  private:
    boost::shared_ptr<SudokuAssist> createSubject(); // Method used to create subject.
};

} // End of namespace sudoku.

#endif
