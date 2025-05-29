mazeSolver: shortestPath.o
        g++ -o mazeSolver shortestPath.o

shortestPath.o: shortestPath.cpp
        g++ -c shortestPath.cpp

clean:
        rm -f p8 *.o *-
