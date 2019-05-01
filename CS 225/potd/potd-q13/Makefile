EXENAME = animal-test
OBJS = animal.o animal-test.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

animal-test.o: animal-test.cpp
	$(CXX) $< $(CXXFLAGS)

animal.o: animal.cpp animal.h
	$(CXX) $< $(CXXFLAGS)

clean :
	-rm -f *.o $(EXENAME)
