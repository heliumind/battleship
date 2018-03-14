main: main.o game.o board.o ship.o
	g++ -o main -std=c++14 main.o game.o board.o ship.o

main.o:
	g++ -c -std=c++14 main.cpp

game.o:
	g++ -c -std=c++14 game.cpp

board.o:
	g++ -c -std=c++14 board.cpp

ship.o:
	g++ -c -std=c++14 ship.cpp
