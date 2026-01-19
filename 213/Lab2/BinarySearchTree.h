#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <cmath>
#include <functional>

#include "Node.h"
#include "NoSuchItemException.h"
#include "BSTPrintSafety.h"

template<class T>
class DefaultBalanceCondition {
public:
    bool operator()(int current, int ideal) const {
        return current <= ideal; // DO NOT CHANGE 
    }
};


template<class T,
         typename BalanceCondition = DefaultBalanceCondition<T>,
         typename Comparator = std::less<T> >
class  BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(const std::list<T> &sortedList);
    BinarySearchTree(const BinarySearchTree &obj);
    ~BinarySearchTree();

    BinarySearchTree &operator=(const BinarySearchTree &rhs);

    bool insert(const T &element);
  
    void removeAllNodes();

    bool isEmpty() const;
    int getHeight() const;
    int getSize() const;

    const T &get(const T &element) const;

    void printPreorder() const;
    void printInorder() const;
    void printPostorder() const;
    void printPretty() const;

    void print(std::ostream &out) const;
    Node<int> *&getRoot()  ;
    
    void toCompleteBST(Node<T> *&node); 
    void binary_tree_to_vector_with_inorder(Node<T> *node, std::vector<Node<T> *> &vec) const; //TODO Q1a
    Node<T> *buildCompleteBST(std::vector<Node<T> *> &arr, int start, int end); //TODO Q1b
    std::vector<T> searchByRange(const T &low, const T &high) const; //TODO Q2
    // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    int getLeftSubtreeSize(int n) {
        int h = (int)(std::log(n) / std::log(2));
        
        int lastLevelCount = n - (std::pow(2, h) - 1);
        
        int x = std::pow(2, h-1);
        
        int leftCount = (std::pow(2, h) - 1) / 2 + std::min(lastLevelCount, x);
        
        return leftCount;
    }
    
    void findHelper(Node<T>* r, const T& low, const T& high, std::vector<T>& arr) const {
        if (r == NULL) return;
        
        if (isLessThan(low, r->element)) findHelper(r->left, low, high, arr);
        
        if ((isLessThan(low, r->element) && isLessThan(r->element, high)) || (!isLessThan(low, r->element) && !isLessThan(r->element, low)) || (!isLessThan(high, r->element) && !isLessThan(r->element, high))) arr.push_back(r->element);
        
        if (isLessThan(r->element, high)) findHelper(r->right, low, high, arr);
    }
    
    const T& getNext(const T& element) const {
        Node<T>* current = root;
        Node<T>* successor = NULL;
        
        while (current != NULL) {
            if (isLessThan(element, current->element)) {
                successor = current;
                current = current->left;
            } else current = current->right;
        }
        
        if (successor == NULL) throw NoSuchItemException();
        return successor->element;
    }
    
    T& getMin() const {
        Node<T>* current = root;
        
        while (current->left != NULL) current = current->left;
        
        return current->element;
    }
    
private:
    Node<T> *root;
    int numNodes;
    Comparator isLessThan;
    BalanceCondition isBalancedFunctor;
    BST_PRINT_SAFETY_MEMBERS

private:
    
    void copyConstructorHelper(Node<T> *&node, Node<T> *nodeToCopy);
    void destructorHelper(Node<T> *&node);
    bool insert(const T &element, Node<T> *&node);
    int height(Node<T> *node) const;
    int size(Node<T> *node) const;
    void printTraversal(Node<T> *node, int type) const;
    void printPretty(Node<T> *node, int indent, bool isLeft) const;
    Node<T> *findNode(const T &element, Node<T> *node) const;
    void print(Node<T> *t, std::ostream &out) const;
    
    
    
    

};




template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::binary_tree_to_vector_with_inorder(Node<T> *node,
                                             std::vector<Node<T> *> &vec) const
{
    // TODO:
    // Perform inorder traversal:
    // 1) Recursively visit left subtree
    // 2) Push this node pointer into vec
    // 3) Recursively visit right subtree
    //
    // NOTE:
    // - Push ONLY Node<T>* (no new allocation, no copying values!)
    // - Must preserve sorted ordering of keys
    if (node == NULL) return;
    else {
        binary_tree_to_vector_with_inorder(node->left, vec);
        vec.push_back(node);
        binary_tree_to_vector_with_inorder(node->right, vec);
    }
}


template<class T, typename B, typename C>
Node<T> *
BinarySearchTree<T,B,C>::buildCompleteBST(std::vector<Node<T> *> &arr,
                                          int start, int end)
{
    // TODO:
    // Convert existing nodes into a complete BST using only pointer rewiring.
    //
    // Requirements:
    //  • Preserve the sorted order of nodes in arr.
    //  • Ensure the resulting subtree is a complete binary tree.
    //  • Do not allocate or delete any nodes.
    //  • Update metadata fields (height and subsize) correctly.
    if (start > end) return NULL;
        
    int left = getLeftSubtreeSize(end - start + 1);
        
    int mid = start + left;
        
    Node<T>* newNode = arr[mid];
        
    newNode->left = buildCompleteBST(arr, start, mid - 1);
    newNode->right = buildCompleteBST(arr, mid + 1, end);
        
    int leftH = (newNode->left) ? newNode->left->height : -1;
    int rightH = (newNode->right) ? newNode->right->height : -1;
        
    int leftS = (newNode->left) ? newNode->left->subsize : 0;
    int rightS = (newNode->right) ? newNode->right->subsize : 0;
        
    newNode->height = 1 + std::max(leftH, rightH);
    newNode->subsize = 1 + leftS + rightS;
    
    return newNode;
}

template<class T, typename B, typename C>
std::vector<T>
BinarySearchTree<T,B,C>::searchByRange(const T &low,
                                       const T &high) const
{
    // TODO:
    // Return all elements with keys in [low, high] (inclusive), sorted.
    //
    // Hint:
    // - You may reuse traverse-based filtering:
    //     * perform inorder traversal
    //     * collect elements if low <= key <= high
    //
    // REQUIREMENTS:
    // - Output vector must be sorted by key
    // - Do NOT modify the tree structure
    // - No rotations or rebalancing allowed
    std::vector<T> arr;
    
    findHelper(root, low, high, arr);
    
    return arr;

}


// YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.




// DO NOT CHANGE THIS PART.
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::toCompleteBST(Node<T> *&node)
{
    if (!node) return;

    std::vector<Node<T> *> arr;
    binary_tree_to_vector_with_inorder(node, arr);
    node = buildCompleteBST(arr, 0, static_cast<int>(arr.size()) - 1);
}




template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::insert(const T &element)
{
    return insert(element, root);
}


template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::insert(const T &element, Node<T> *&node)
{
    if (!node) {
        node = new Node<T>(element, NULL, NULL, 0, 1);
        numNodes++;
        return true;
    }

    bool inserted = false;

    if (isLessThan(element, node->element)) {
        inserted = insert(element, node->left);
    }
    else if (isLessThan(node->element, element)) {
        inserted = insert(element, node->right);
    }
    else {
        node->element = element; 

        return false;
    }

    if (!inserted)
        return false;

    node->height  = std::max(height(node->left), height(node->right)) + 1;
    node->subsize = size(node->left) + size(node->right) + 1;

    int ideal = static_cast<int>(std::floor(std::log(node->subsize) / std::log(2.0)
));
    int current = node->height;

    if (!isBalancedFunctor(current, ideal)) {
        toCompleteBST(node);
}
    

    return true;
} 





template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree() : root(NULL), numNodes(0), isLessThan(C()), isBalancedFunctor(B()),__print_safety_counter(0) {}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::~BinarySearchTree() {
    removeAllNodes();
}



template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::removeAllNodes()
{
    destructorHelper(root);
    numNodes = 0;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::destructorHelper(Node<T> *&node)
{
    if (!node) return;
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
    node = NULL;
}

template<class T, typename B, typename C>
Node<int> *&BinarySearchTree<T, B, C>::getRoot()  {
    return root;
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::height(Node<T> *node) const {
    return node ? node->height : -1;
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::size(Node<T> *node) const {
    return node ? node->subsize : 0;
}

// YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.



#endif // BINARY_SEARCH_TREE_H
