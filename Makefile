TEST_SOURCES = ./test/SudokuGridPointTest.cc \
		./test/SudokuAssistTest.cc \
		./test/SudokuBoardTest.cc \
		./test/Main.cc
TEST_OBJECTS = $(TEST_SOURCES:.cc=.o)
TEST_DEPS := $(TEST_OBJECTS:.o=.d)
UTILITIES_TEST_SOURCES = ./utilities/test/CheckIfVectorsEqualTest.cc \
			./utilities/test/Main.cc
UTILITIES_TEST_OBJECTS = $(UTILITIES_TEST_SOURCES:.cc=.o)
UTILITIES_TEST_DEPS = $(UTILITIES_TEST_OBJECTS:.o=.d)
SOURCES = ./src/SudokuBoard.cc \
	./src/SudokuAssist.cc
MAIN_SOURCE = ./src/Main.cc
OBJECTS = $(SOURCES:.cc=.o)
DEPS := $(OBJECTS:.o=.d)
MAIN_OBJECT = $(MAIN_SOURCE:.cc=.o)
MAIN_DEP := $(MAIN_OBJECT:.o=.d)
EXECUTABLE = ./src/Main
TEST_EXECUTABLE = ./test/TestMain
UTILITIES_TEST_EXECUTABLE = ./utilities/test/TestMain
CCFLAGS = -c -Wall
CPPUNIT_LIBS = -lcppunit -ldl

all: $(SOURCES) $(MAIN_SOURCE) $(EXECUTABLE) $(TEST_SOURCES) $(TEST_EXECUTABLE)\
	$(UTILITIES_TEST_SOURCES) $(UTILITIES_TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(OBJECTS) $(TEST_OBJECTS)
	g++ -std=c++11 -I . $(OBJECTS) $(TEST_OBJECTS) $(CPPUNIT_LIBS) -o $@

$(UTILITIES_TEST_EXECUTABLE): $(UTILITIES_TEST_OBJECTS)
	g++ -std=c++11 -I . $(UTILITIES_TEST_OBJECTS) $(CPPUNIT_LIBS) -o $@

$(EXECUTABLE): $(OBJECTS) $(MAIN_OBJECT)
	g++ -std=c++11 -I . $(OBJECTS) $(MAIN_OBJECT) $(CPPUNIT_LIBS) -o $@

.cc.o:
	g++ -std=c++11 -I . $(CCFLAGS) -MMD -MP $< -o $@

clean:
	rm -rf $(TEST_OBJECTS)
	rm -rf $(TEST_EXECUTABLE)
	rm -rf $(OBJECTS)
	rm -rf $(EXECUTABLE)
	rm -rf $(UTILITIES_TEST_OBJECTS)
	rm -rf $(UTILITIES_TEST_EXECUTABLE)
	rm -rf $(TEST_DEPS) $(UTILITIES_TEST_DEPS) $(DEPS) $(MAIN_DEP)

check: all
	@echo
	@echo "#######################################"
	@echo "Running unit tests in utilities/test..."
	./utilities/test/TestMain
	@echo
	@echo "#######################################"
	@echo "Running unit tests in test..."
	./test/TestMain

main: $(EXECUTABLE)
	./src/Main

-include $(TEST_DEPS) $(DEPS) $(MAIN_DEP) $(UTILITIES_TEST_DEPS)
