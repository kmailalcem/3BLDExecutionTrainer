all: main.o cube.o scramble.o
	g++ -Werror -Wall -pedantic --std=c++14 -O3 main.o scramble.o cube.o -o trainer

main.o: main.cpp
	g++ -Werror -Wall -pedantic --std=c++14 -c main.cpp

scramble.o: Scramble.cpp Scramble.h
	g++ -Werror -Wall -pedantic --std=c++14 -c Scramble.cpp

cube.o: Cube.cpp
	g++ -Werror -Wall -pedantic --std=c++14 -c Cube.cpp

test_scramble: Scramble.h Scramble.cpp test_scramble.cpp
	g++ -Werror -Wall -pedantic --std=c++14 -O3 scramble.cpp test_scramble.cpp -o test_scramble
