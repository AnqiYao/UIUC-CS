EXENAME = main

CXX = clang++
CXXFLAGS = -std=c++0x -g -O0 -Wall -Wextra

all : $(EXENAME)

$(EXENAME): main.cpp square.cpp square.h
	$(CXX) $(CXXFLAGS) main.cpp square.cpp -o $(EXENAME)

.PHONY: clean
clean:
	rm -f $(EXENAME)
