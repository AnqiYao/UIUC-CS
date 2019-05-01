CXX = clang++
CXXFLAGS = -std=c++0x -g -O0 -Wall -Wextra

all:
	@echo These programs break, so use the following targets to test things:
	@echo make leak -- to make the leaking program
	@echo make nonCompile -- to make the program that does not compile.
	@echo make segFault -- to make the segfaulting program.

leak: leak.cpp
	$(CXX) $(CXXFLAGS) leak.cpp -o leak

nonCompile: nonCompile.cpp
	$(CXX) $(CXXFLAGS) nonCompile.cpp -o nonCompile

segFault: segFault.cpp
	$(CXX) $(CXXFLAGS) segFault.cpp -o segFault

.PHONY: clean
clean:
	rm -f leak nonCompile segFault
