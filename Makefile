EXEC=Xcrystal

CXX=g++

BUILDDIR=build

SRC=main.cpp disp.cpp prog.cpp util.cpp

OBJ=$(SRC:%.cpp=$(BUILDDIR)/%.o)

LDFLAGS=-lGLEW -lGL -lSDL2

.PHONY: all
all: mk_build $(EXEC)

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o $(EXEC)
