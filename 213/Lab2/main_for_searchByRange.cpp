#include <iostream>
#include <vector>
#include "BinarySearchTree.h"
#include "Node.h"

int main() {

    Node<int>* root = new Node<int>(15, NULL, NULL, 0, 1);

    root->left  = new Node<int>(7, NULL, NULL, 0, 1);
    root->right = new Node<int>(25, NULL, NULL, 0, 1);

    root->left->left  = new Node<int>(3, NULL, NULL, 0, 1);
    root->left->right = new Node<int>(10, NULL, NULL, 0, 1);
    root->left->right->left  = new Node<int>(8, NULL, NULL, 0, 1);
    root->left->right->right = new Node<int>(12, NULL, NULL, 0, 1);

    root->right->left  = new Node<int>(20, NULL, NULL, 0, 1);
    root->right->right = new Node<int>(30, NULL, NULL, 0, 1);


    BinarySearchTree<int> bst;


    bst.getRoot() = root;

    int low = 8;
    int high = 20;


    std::vector<int> result = bst.searchByRange(low, high);

    std::cout << "Range [" << low << ", " << high << "] result: ";
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
