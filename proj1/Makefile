proj1: main.o SnakeGame.o Menu.o List.o
	g++ -o proj1 main.o SnakeGame.o Menu.o List.o -lncurses

main.o: main.cpp SnakeGame.cpp Menu.cpp List.cpp Menu.h SnakeGame.h
	g++ -c main.cpp

SnakeGame.o: SnakeGame.cpp SnakeGame.h Common.h
	g++ -c SnakeGame.cpp

Menu.o: Menu.cpp Menu.h Common.h
	g++ -c Menu.cpp

List.o: List.cpp List.h Common.h
	g++ -c List.cpp

clean:
	rm -r -f *.o
	rm -r -f proj1
