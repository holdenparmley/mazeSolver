p8: shortestPath.o
        g++ -o p8 shortestPath.o

shortestPath.o: shortestPath.cpp
        g++ -c shortestPath.cpp

clean:
        rm -f p8 *.o *-
