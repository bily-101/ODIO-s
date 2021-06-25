all:
	g++ src/*.cpp -std=c++11 -lglfw -lSOIL -lGLU -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lGLEW -fpermissive -o game
	./game
	rm game

build:
	g++ src/*.cpp -std=c++11 -lglfw -lSOIL -lGLU -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lGLEW -fpermissive -o game

run:
	./game

clean:
	rm game
