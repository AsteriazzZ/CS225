COMPILER = clang++
COMPILER_OPTS = -c -g -O0 -Wall -Werror -std=c++11
LINKER = clang++
LINKER_OPTS = -lpng
all: testimage testscene

testimage: image.o testimage.o png.o rgbapixel.o 
	$(LINKER) testimage.o image.o png.o rgbapixel.o $(LINKER_OPTS) -o testimage 

testscene: image.o testscene.o png.o rgbapixel.o scene.o
	$(LINKER) image.o scene.o testscene.o png.o rgbapixel.o $(LINKER_OPTS) -o testscene 

scene.o : scene.cpp scene.h image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) scene.cpp

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) testscene.cpp

image.o : image.cpp image.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) image.cpp

testimage.o : testimage.cpp png.h image.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) testimage.cpp

png.o : png.cpp png.h rgbapixel.h 
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp

clean :
	-rm -f *.o testimage testscene 
