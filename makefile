OBJS=cmd.o main.o test.o
CXXFLAGS=-O2 -std=c++11

terminal: $(OBJS)
	g++ -o terminal $(OBJS)
main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
cmd.o: cmd.cpp
	g++ -c cmd.cpp $(CXXFLAGS)
test.o: test.cpp
	g++ -c test.cpp $(CXXFLAGS) -L/usr/lib/ -lgtest -lgtest_main -pthread
clean:
	rm -f *.o

