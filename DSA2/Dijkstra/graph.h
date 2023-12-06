#ifndef _GRAPH_H
#define _GRAPH_H

#include <climits>
#include <list>
#include "hash.h"
#include "heap.h" 

class graph {
	public:
		graph();
		int insert(const std::string &start, const std::string &next, const int &distance);
        int dijkstra(const std::string &start);
		int printGraph(const std::string &outFile);

	private:
		class vertex {
			public:
				std::string name;
				int distance = INT_MAX;
                std::vector<vertex> adjList;
				vertex *prevVertex = nullptr;
		};

		std::list<vertex> vertexList;
		hashTable vertices;
};

#endif //_GRAPH_H