all: buzzy_revenge

buzzy_revenge:
	export DISPLAY=:0.0
	g++ code/*.h code/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
	./a.out

clean:
	rm a.out
	rm code/*.gch