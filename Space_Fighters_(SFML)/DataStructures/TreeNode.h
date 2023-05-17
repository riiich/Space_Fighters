//
// Created by horic on 10/29/2020.
//

#ifndef BINARY_TREE_TREENODE_H
#define BINARY_TREE_TREENODE_H

template<class T>
struct TreeNode {
    TreeNode();
    TreeNode(const T& item);

    TreeNode<T>* left;
    TreeNode<T>* right;
    T data;
};

#include "TreeNode.cpp"
#endif //BINARY_TREE_TREENODE_H
