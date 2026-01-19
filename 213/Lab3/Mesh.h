#ifndef MESH_H
#define HESH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include "DataStructures.h"

using std::string;
using std::ifstream;
using std::stringstream;

class Mesh {
public:
	vector<Vertex> verts;
	vector<Edge> edges;
	vector<Triangle> tris;
	vector<size_t> maxHeap;

	Mesh() {
		maxHeap.push_back(0);
	};
	Mesh(const char* filename);
	~Mesh() {
		verts.clear();
		edges.clear();
		tris.clear();
		maxHeap.clear();
	};

	inline Vertex& getVertex(size_t v) {
		if (v < verts.size()) {
			return verts[v];
		}
		else {
			return verts[0];
		}
	}

	inline Edge& getEdge(size_t e) {
		if (e < edges.size()) {
			return edges[e];
		}
		else {
			return edges[0];
		}
	}

	Edge& getEdge(size_t v1, size_t v2);

	

	inline Triangle& getTriangle(size_t t) {
		if (t < tris.size()) {
			return tris[t];
		}
		else {
			return tris[0];
		}
	}

	inline void printVertex(size_t v) {
		Vertex vert = getVertex(v);
		std::cout << vert.coords[0] << " " << vert.coords[1] << " " << vert.coords[2] << " ";
	}
	inline void printTriangle(size_t t) {
		Triangle tri = getTriangle(t);
		std::cout << "3 " << tri.v1i << " " << tri.v2i << " " << tri.v3i << " ";
	}

	inline bool isVertsNeighbour(size_t v1, size_t v2){ return getVertex(v1).containsVertex(v2); }
	inline size_t getDegree(size_t v){ return getVertex(v).vertList.size(); }

	size_t getComponentCount();
	bool onSameComponent(size_t v1, size_t v2);
	Vertex& getKthLargestVertex(size_t k);

private:	
	size_t addVertex(double x, double y, double z);
	size_t addEdge(size_t v1, size_t v2);
	size_t addTriangle(size_t v1, size_t v2, size_t v3);
	void buildHeap();
	void bubbleDown(int hole);
	void removeFromHeap();
	double computeMass(size_t v);

	// Declare your helper functions here.
};

#endif // !MESH_H

