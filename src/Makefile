SOURCES = SudokuAssist.cc Main.cc
OBJECTS = $(SOURCES:.cc=.o)
EXECUTABLE = Main
CCFLAGS = -c -Wall

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ -std=c++11 $(OBJECTS) -o $@

.cc.o:
	g++ -std=c++11 $(CCFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)
	rm -rf ./Main

check: all
