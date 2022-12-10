CXX=g++

SRC=main.cpp disp.cpp prog.cpp util.cpp

OBJ=$(SRC:%.cpp=%.o)

LDFLAGS=-lGLEW -lGL -lSDL2

.PHONY: all
all: make

%.o: %.cpp %.h
	$(CXX) -c $< -o $@

main.o: main.cpp
	$(CXX) -c $< -o $@

.PHONY: make
make: $(OBJ)
	$(CXX) $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm *.o a.out
