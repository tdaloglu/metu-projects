#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "BinarySearchTree.cpp"

template<class K, class V>
class TreeMap {
public:
    TreeMap();

    void clear();
    const V &get(const K &key) const;
    V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key);
    bool update(const K &key, const V &value);
    void print() const;
    int size();
    
    KeyValuePair<K, V>& mini() const {
        return stree.getMin();
    }
    
    const KeyValuePair<K, V>& next(KeyValuePair<K, V> element) const {
        return stree.getNext(element);
    }



// YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
private:
    BinarySearchTree<KeyValuePair<K, V> > stree;
};

// YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.



#endif
