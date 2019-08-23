proj1.x: proj1.cpp
	g++ -std=c++11 -Wall -pedantic -o proj1.x proj1.cpp

clean:
	rm -f *.o *.x core.*
