//AVLNode.h

#ifndef __AVLNODE_H__
#define __AVLNODE_H__
#include <iostream>
#include <vector>
#include <algorithm>
template <typename KeyType>
class AVLNode{
public:
    KeyType key;
    AVLNode * left;
    AVLNode * right;
    AVLNode() :key(0),left(NULL), right(NULL){}
    AVLNode(KeyType k) :key(k), left(NULL), right(NULL){}
};
#endif