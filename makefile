OBJS=cmd.o main.o
CXXFLAGS=-O2 -std=c++11

terminal: $(OBJS)
	g++ -o terminal $(OBJS)
test: test.o
	g++ -o test test.o
main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
cmd.o: cmd.cpp
	g++ -c cmd.cpp $(CXXFLAGS)
test.o: test.cpp
	g++ -c test.cpp $(CXXFLAGS) -I/usr/include/src/gtest -L/usr/lib -L/usr/lib/libgtest_main.a -lgtest -lgtest_main
clean:
	rm -f *.o

