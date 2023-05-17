//
// Created by horic on 10/29/2020.
//

#ifndef BINARY_TREE_NODE_CPP
#define BINARY_TREE_NODE_CPP

#include "TreeNode.h"

template<class T>
TreeNode<T>::TreeNode()
{
    right = nullptr;
    left = nullptr;
}

template<class T>
TreeNode<T>::TreeNode(const T& item)
{
    right = nullptr;
    left = nullptr;
    this->data = item;
}

#endif