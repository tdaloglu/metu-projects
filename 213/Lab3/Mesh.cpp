#include "Mesh.h"

Mesh::Mesh(const char* filename)
{
	int nVerts, nTris, n, k = 0;
	double x, y, z;
	maxHeap.push_back(0);

	ifstream file(filename);

	string line;
	getline(file, line);
	getline(file, line);
	stringstream str(line);
	str >> nVerts >> nTris >> n;

	while (k++ < nVerts)
	{
		getline(file, line);
		stringstream str2(line);

		str2 >> x >> y >> z;
		addVertex(x, y, z);
	}
	k = 0;
	while (k++ < nTris)
	{
		getline(file, line);
		stringstream str2(line);

		str2 >> n >> x >> y >> z;
		addTriangle((size_t)x, (size_t)y, (size_t)z);
	}

	file.close();
	

	buildHeap(); // Not Implemented.
}


size_t Mesh::addVertex(double x, double y, double z) {
	size_t idx = verts.size();
	verts.push_back(Vertex(idx, x, y, z));
	verts[idx].mass = computeMass(idx);
	maxHeap.push_back(idx);
	return idx;
}

size_t Mesh::addEdge(size_t v1, size_t v2) {
	Vertex& vertex1 = getVertex(v1);
	Vertex& vertex2 = getVertex(v2);

	size_t idx;

	if (isVertsNeighbour(v1, v2))
	{
		Edge& edge = getEdge(v1, v2);
		idx = edge.idx;
	}
	else
	{
		// TODO: Finish Edge Addition Logic
		if (v1 < 0 || v1 >= verts.size() || v2 < 0 || v2 >= verts.size()) return -1;
		size_t index = edges.size();
		
		Edge edge(index, v1, v2);
		
		double length = dist(verts[v1].coords, verts[v2].coords);
		
		edge.length = length;
		
		edges.push_back(edge);
		
		verts[v1].vertList.push_back(v2);
		verts[v2].vertList.push_back(v1);
		
		verts[v1].edgeList.push_back(index);
		verts[v2].edgeList.push_back(index);
		
		verts[v1].mass = computeMass(v1);
		verts[v2].mass = computeMass(v2);
		
	}

	return idx;
}

double Mesh::computeMass(size_t v) {
    if (v < 0 || v >= verts.size()) return -1.0;
    
    double result = 0.0;
    
    for (size_t i = 0; i < verts[v].triList.size(); i++) {
        size_t index = verts[v].triList[i];
        
        result += (tris[index].area) / 3;
    }
    
    return result;
}

size_t Mesh::addTriangle(size_t v1, size_t v2, size_t v3) {

	size_t idx = tris.size();
	Triangle tri = Triangle(idx, v1, v2, v3);
	addEdge(v1, v2); // Not Fully Implemented
	addEdge(v2, v3); // Not Fully Implemented
	addEdge(v3, v1); // Not Fully Implemented
	
	double len1 = getEdge(v1, v2).length;
	double len2 = getEdge(v1, v3).length;
	double len3 = getEdge(v2, v3).length;
	
	double S = (len1 + len2 + len3) / 2;
	
	double result = S * (S - len1) * (S - len2) * (S - len3);
	
	double area = std::sqrt(result);
	
	tri.area = area;
	
	tris.push_back(tri);

	getVertex(v1).triList.push_back(idx);
	getVertex(v2).triList.push_back(idx);
	getVertex(v3).triList.push_back(idx);
	
	getVertex(v1).mass = computeMass(v1);
	getVertex(v2).mass = computeMass(v2);
	getVertex(v3).mass = computeMass(v3);
	
	
	
	return idx;
}

Edge& Mesh::getEdge(size_t v1, size_t v2) {
	for (size_t e : getVertex(v1).edgeList) {
		Edge& edge = getEdge(e);
		if (edge.containsVertex(getVertex(v2).idx)) {
			return edge;
		}
	}
	return edges[0];
}

void Mesh::bubbleDown(int hole) {
    int theSize = maxHeap.size() - 1;
    int child;
    
    size_t temp = maxHeap[hole];
    
    for (; hole * 2 <= theSize; hole = child) {
        child = hole * 2;
        if (child != theSize && verts[maxHeap[child + 1]].mass > verts[maxHeap[child]].mass) child++;
        
        if (verts[maxHeap[child]].mass > verts[temp].mass) maxHeap[hole] = maxHeap[child];
        else break;
    }
    
    maxHeap[hole] = temp;
}

void Mesh::buildHeap() {
    int theSize = maxHeap.size() - 1;
    
    for (size_t i = 1; i < maxHeap.size(); i++) {
        size_t index = maxHeap[i];
        
        verts[index].mass = computeMass(index);
    }
    for (int i = theSize / 2; i > 0; i--) bubbleDown(i);
}

size_t Mesh::getComponentCount()
{
	size_t count = 0;
	vector<bool> visited(verts.size(), false);
	
	for (size_t i = 0; i < verts.size(); i++) {
	    if (!visited[i]) {
	        count++;
	        std::queue<size_t> q;
	        q.push(i);
	        while (!q.empty()) {
	            size_t u = q.front();
	            q.pop();
	            for (size_t j = 0; j < verts[u].vertList.size(); j++) {
	                size_t vIdx = verts[u].vertList[j];
	                if (!visited[vIdx]) {
	                    visited[vIdx] = true;
	                    q.push(vIdx);
	                }
	            }
	        }
	    }
	}
	
	return count;
}

bool Mesh::onSameComponent(size_t v1, size_t v2)
{
    if (v1 < 0 || v1 >= verts.size() || v2 < 0 || v2 >= verts.size()) return false;
	vector<bool> visited(verts.size(), false);
	std::queue<size_t> q;
	visited[v1] = true;
	q.push(v1);
	
	while (!q.empty()) {
	    size_t u = q.front();
	    q.pop();
	    if (u == v2) return true;
	    for (size_t i = 0; i < verts[u].vertList.size(); i++) {
	        size_t index = verts[u].vertList[i];
	        
	        if (!visited[index]) {
	            visited[index] = true;
	            q.push(index);
	        }
	    }
	}
	
	return false;
}

Vertex& Mesh::getKthLargestVertex(size_t k)
{
    if (k > maxHeap.size()) return getVertex(0);
    if (k == 0) return getVertex(maxHeap[1]);
    
    vector<size_t> backUp = maxHeap;
    
    for (size_t i = 0; i < k; i++) {
        removeFromHeap();
    }
    
    size_t resultIdx = maxHeap[1];
    
    maxHeap = backUp;
    
	return getVertex(resultIdx);
}

void Mesh::removeFromHeap() {
    if (maxHeap.size() <= 1) return;
    
    int theSize = maxHeap.size() - 1;
    
    maxHeap[1] = maxHeap[theSize];
    
    maxHeap.pop_back();
    
    if (maxHeap.size() > 1) bubbleDown(1); 
}


// Implement your helper functions here.