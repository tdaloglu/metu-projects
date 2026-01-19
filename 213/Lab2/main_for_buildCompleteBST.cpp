#include <iostream>
#include "BinarySearchTree.cpp"

class StrictBalance
{
public:
    bool operator()(int current_height, int ideal_height) const {
        return current_height <= ideal_height;
    }
};

int main() {
    BinarySearchTree<int, StrictBalance> bst;

    int values[] = {10, 16, 12, 28, 47, 18, 24, 55, 59, 21, 27, 19};
    int n = sizeof(values) / sizeof(values[0]);

    std::cout << "===== INSERTING VALUES =====\n";
    for (int i = 0; i < n; ++i) {
        bst.insert(values[i]);
    }

    std::cout << "\n===== FINAL COMPLETE BST (AUTO) =====\n";
    bst.printPretty();  

    return 0;
}
