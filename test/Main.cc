#include <iostream>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

// Include all the tests.
#include "SudokuAssistTest.h"
#include "SudokuGridPointTest.h"

int main(int argc, char* argv[])
{
  std::string testPath("");
  if ( argc == 2 )
  {
    testPath = std::string(argv[1]);
  }
  else if ( argc > 2 )
  {
    std::cerr << "Too many arguments provided." << std::endl;
    return 1;
  }

  // Create the event manager and test controller.
  CppUnit::TestResult testResult;
  
  // Register listener for collecting results.
  CppUnit::TestResultCollector testResultCollector;
  testResult.addListener( &testResultCollector );        
  
  // Register listener for per test output.
  CppUnit::BriefTestProgressListener progressListener;
  testResult.addListener( &progressListener );
  
  // Add the test-suite to the test runner.
  CppUnit::TestRunner testRunner;
  testRunner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );   

  // Run tests.
  testRunner.run( testResult, testPath );

  // Output tests.
  CppUnit::CompilerOutputter outputter( &testResultCollector, std::cerr );
  outputter.write();
  
  return testResultCollector.wasSuccessful() ? 0 : 1;
}
