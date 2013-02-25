CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -ggdb
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

sim: main.o car.o
	$(CXX) -o sim main.o car.o $(LIBS)

main.o: main.cpp car.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

car.o: car.cpp car.hpp
	$(CXX) $(CXXFLAGS) -c car.cpp

clean:
	rm -f *.o sim
