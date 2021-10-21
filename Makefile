all: buzzy_revenge

buzzy_revenge: code/test.o code/graphics.o
	g++ -g -std=c++0x code/test.o code/graphics.o -o buzzy_revenge

test.o: code/test.cpp code/graphics.h
	g++ -c -std=c++0x code/test.cpp -lsfml-graphics -lsfml-window -lsfml-system

graphics.o: code/graphics.cpp code/graphics.h
	g++ -c -std=c++0x code/graphics.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm code/test.o code/graphics.o

test:
	g++ code/test.cpp code/graphics.h -lsfml-graphics -lsfml-window -lsfml-system