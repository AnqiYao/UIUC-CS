EXENAME =  testimage
OBJS = testimage.o png.o rgbapixel.o image.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

testscene : testscene.o scene.o image.o png.o rgbapixel.o
	$(LD) testscene.o scene.o image.o png.o rgbapixel.o $(LDFLAGS) -o testscene

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp

scene.o: scene.cpp scene.h
	$(CXX) $(CXXFLAGS) scene.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

testimage.o : testimage.cpp image.h 
	$(CXX) $(CXXFLAGS) testimage.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp
clean :
	-rm -f *.o $(EXENAME)
