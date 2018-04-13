main: main.cpp Cube.cpp Cube.h
	g++ -Werror -Wall -pedantic --std=c++14 -O3 main.cpp Cube.cpp -o main
