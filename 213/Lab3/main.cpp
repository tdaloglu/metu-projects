#include "Mesh.h"

bool heapChecker(Mesh& mesh){
    bool retval = true;
    if(mesh.maxHeap.size() != mesh.verts.size() + 1){
        std::cout << "Not a guarded heap containin all vertices." << std::endl;
        retval = false;
    }
    for(size_t i = 1; i < mesh.maxHeap.size(); i++){
        if(i * 2 < mesh.maxHeap.size() && mesh.getVertex(mesh.maxHeap[i]).mass < mesh.getVertex(mesh.maxHeap[i * 2]).mass){
            std::cout << "Not a Max Heap due to indices " << i << " and " << i * 2 << std::endl;
            retval = false;
        }
        if(i * 2 + 1 < mesh.maxHeap.size() && mesh.getVertex(mesh.maxHeap[i]).mass < mesh.getVertex(mesh.maxHeap[i * 2 + 1]).mass){
            std::cout << "Not a Max Heap due to indices " << i << " and " << i * 2 + 1 << std::endl;
            retval = false;
        }
    }
    
    return retval;
}
int main() {
    Mesh mesh;
    
    heapChecker(mesh);
    
    return 0;
}