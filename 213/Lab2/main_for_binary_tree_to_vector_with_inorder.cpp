#include <iostream>
#include <vector>
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

class StrictBalance
{
public:
    bool operator()(int current_height, int ideal_height) const
    {
        return current_height <= ideal_height;
    }
};

int main()
{
    BinarySearchTree<int, StrictBalance> bst;

    int values[] = {10, 16, 12, 28, 47, 18, 24, 55, 59, 21, 27, 19};
    for (int i = 0; i < 12; i++)
    {
        bst.insert(values[i]);
    }

    std::cout << "Tree before inorder vector:" << std::endl;
    bst.printPretty();

    std::vector<Node<int>*> vec;
    bst.binary_tree_to_vector_with_inorder(bst.getRoot(), vec);

    std::cout << std::endl;
    std::cout << "Inorder traversal result:" << std::endl;

    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i]->element << " ";
    }
    std::cout << std::endl;

    return 0;
}