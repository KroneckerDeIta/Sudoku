PROGS = SudokuGridPointTest SudokuAssistTest Main
PROGS_SRC = SudokuAssist
SRC = ../src
CPPUNIT_LIBS = -lcppunit -ldl
PROGS_IN = $(PROGS:=.cc)
PROGS_OUT = $(PROGS:=.o)

PROGS_SRC_IN = $(addprefix $(SRC)/,$(PROGS_SRC:=.cc))

all: pre-build
	g++ -std=c++11 $(PROGS_OUT) $(CPPUNIT_LIBS) -o Main

pre-build:
	g++ -std=c++11 -I $(SRC) -c $(PROGS_IN) $(PROGS_SRC_IN)

clean:
	rm -rf $(PROGS_OUT)
	rm -rf ./Main

check: all
	./Main
