OBJS=cmd.o main.o
CXXFLAGS=g++

demo: $(OBJS)
	g++ demo $(OBJS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
cmd.h: cmd.cpp
	g++ -c cmd.cpp $(CXXFLAGS)

clean:
	rm -f *.o