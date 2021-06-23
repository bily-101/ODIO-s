all:
	g++ src/*.cpp -lglfw -lSOIL -lGLU -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lGLEW -fpermissive -o game
	./game
	rm game

build:
	g++ src/*.cpp -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lGLEW -o game

run:
	./game

clean:
	rm game
