dijkstra: dijkstra.o graph.o heap.o hash.o
	g++ -o dijkstra dijkstra.o graph.o heap.o hash.o 

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o DebugGraph dijkstra.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f dijkstra DebugGraph  *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
