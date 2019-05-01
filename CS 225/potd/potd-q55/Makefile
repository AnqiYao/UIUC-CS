EXENAME = main
OBJS = main.o heap.o MaxHeap.o MinHeap.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $< $(CXXFLAGS)

heap.o: heap.cpp
	$(CXX) $< $(CXXFLAGS)

MaxHeap.o: MaxHeap.cpp
	$(CXX) $< $(CXXFLAGS)

MinHeap.o: MinHeap.cpp
	$(CXX) $< $(CXXFLAGS)

clean:
	-rm -f *.o $(EXENAME)
