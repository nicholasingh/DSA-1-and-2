#include <iostream>
#include <stack>
#include <fstream>
#include "heap.h"
#include "hash.h"
#include "graph.h"

using namespace std;

graph::graph(){

}

int graph::insert(const std::string &start, const std::string &next, const int &distance) {
	bool startFound;
	vertex *source = static_cast<vertex *> (vertices.getPointer(start, &startFound));

	vertex adjVertex;
	adjVertex.name = next;
	adjVertex.distance = distance;

	if(startFound) {
		source->adjList.push_back(adjVertex);
	} else {
		vertex temp;
		temp.name = start;
		temp.adjList.push_back(adjVertex);
		vertexList.push_back(temp);
		vertices.insert(start, &vertexList.back());
	}

	if(!vertices.contains(next)) {
		vertex nextNode;
		nextNode.name = next;
		vertexList.push_back(nextNode);
		vertices.insert(next, &vertexList.back());
	}

	return 0;
}

int graph::dijkstra(const string &start) {
	bool startFound;
	vertex *source = static_cast<vertex *> (vertices.getPointer(start, &startFound));

	if(!startFound) {
		return -1;
	}

	source->distance = 0;
    
	heap minDistanceHeap(vertexList.size());

	for (auto &curVertex : vertexList) {
		minDistanceHeap.insert(curVertex.name, curVertex.distance, &curVertex);
	}
	vertex *curVertex;
	string curVertexName;
	int curDistance;

	while(minDistanceHeap.deleteMin(&curVertexName, &curDistance, &curVertex) != 1) {

		if(curVertex->distance == INT_MAX) {
			continue;
		}

		for(auto &adjVertex : curVertex->adjList) {
			bool foundAdj;
			vertex *nextVertex = static_cast<vertex *> (vertices.getPointer(adjVertex.name, &foundAdj));

			if(curVertex->distance + adjVertex.distance < nextVertex->distance) {
				nextVertex->distance = curVertex->distance + adjVertex.distance;
				minDistanceHeap.setKey(nextVertex->name, nextVertex->distance);
				nextVertex->prevVertex = curVertex;
			}
		}
	}  

	return 0;
}

int graph::printGraph(const string &outFile) {
    ofstream output;
    output.open(outFile);

    for (auto &chosenVer : vertexList) {
        output << chosenVer.name;

        if (chosenVer.distance == INT_MAX) {
            output << ": NO PATH" << "\n";
            continue;
        }

        output << ": " << chosenVer.distance;
        vertex *currentVertex = &chosenVer;
        stack<string> pathStack;

        while(currentVertex = currentVertex->prevVertex) {
            pathStack.push(currentVertex->name);
        }

        output << " [";

        while (!pathStack.empty()) {
            output << pathStack.top() << ", ";
            pathStack.pop();
        }

        output << chosenVer.name << "]" << "\n";
    }

    output.close();
    return 0;
}

