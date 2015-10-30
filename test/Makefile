SOURCES = SudokuGridPointTest.cc SudokuAssistTest.cc Main.cc
OBJECTS = $(SOURCES:.cc=.o)
SRC_OBJECTS = SudokuAssist.o
EXECUTABLE = Main
SRC = ../src
CCFLAGS = -c -Wall
CPPUNIT_LIBS = -lcppunit -ldl

all: $(SOURCES) $(EXECUTABLE)
	cd ../src && make

$(EXECUTABLE): $(OBJECTS)
	g++ -std=c++11 -I $(SRC) $(OBJECTS) $(SRC_OBJECTS) $(CPPUNIT_LIBS) -o $@

.cc.o:
	g++ -std=c++11 -I $(SRC) $(CCFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)
	rm -rf ./Main

check: all
	./Main
