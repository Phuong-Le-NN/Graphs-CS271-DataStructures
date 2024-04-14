all: test 

test: test_graph.o
	g++ -std=c++11 -Wall -o test test_graph.o

test_graph.o: test_graph.cpp
	g++ -std=c++11 -Wall -c test_graph.cpp

clean:
	rm -f *.o test 