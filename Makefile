all:
	g++ -I src/include -L src/lib -o main main.cpp object.cpp vec2.cpp horse.cpp scene.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf