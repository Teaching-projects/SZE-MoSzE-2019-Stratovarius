OBJS=cmd.o main.o
CXXFLAGS=-O2

terminal: $(OBJS)
	g++ -o terminal $(OBJS)
main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
cmd.o: cmd.cpp
	g++ -c cmd.cpp $(CXXFLAGS)
clean:
	rm -f *.o

