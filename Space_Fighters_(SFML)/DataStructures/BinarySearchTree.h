//
// Created by horic on 10/29/2020.
//

#ifndef BINARY_TREE_BINARYSEARCHTREE_H
#define BINARY_TREE_BINARYSEARCHTREE_H
#include <iostream>
#include "TreeNode.h"
#include "Traversal.h"

template<class T>
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& tree);
    BinarySearchTree<T>& operator =(const BinarySearchTree<T>& rhs);
    ~BinarySearchTree();
    int size() const;
    void insert(const T& item);    //add an item to the tree
    void operator +=(const T& item);    //operator to add an item to the tree
    void setTraversal(const Traversal& order);
    void printEntireTree();

private:
    TreeNode<T>* root;
    int _size;
    TreeNode<T>* insert(TreeNode<T>* parent, const T& item);
    Traversal _order;
    void inorder(TreeNode<T>* parent, void f(T&));  //left -> root -> right
    void preorder(TreeNode<T>* parent, void f(T&)); //root -> left -> right
    void postorder(TreeNode<T>* parent, void f(T&)); //left -> right -> root'
    void copy(TreeNode<T>* node);
    void clear(TreeNode<T>* node);   //clear the tree
};

namespace binaryPrint
{
    template<class T>
    void print(T& parent_data);
}


#include "BinarySearchTree.cpp"
#endif //BINARY_TREE_BINARYSEARCHTREE_H
