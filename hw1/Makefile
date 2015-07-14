hw1: ZipCode.o hw1.o
	g++ ZipCode.o hw1.o -o hw1

ZipCode.o: ZipCode.h ZipCode.cpp
	g++ -c ZipCode.cpp

hw1.o: hw1.cpp
	g++ -c hw1.cpp

clean:
	rm -f *.o
	rm -f *.gch
	rm -f hw1
