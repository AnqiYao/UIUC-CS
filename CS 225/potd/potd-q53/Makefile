EXENAME = main
OBJS =  main.o mystery.o functions.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $< $(CXXFLAGS)

mystery.o: mystery.cpp
	$(CXX) $< $(CXXFLAGS)

functions.o: functions.cpp
	$(CXX) $< $(CXXFLAGS)

clean:
	rm -f $(EXENAME) $(OBJS)
