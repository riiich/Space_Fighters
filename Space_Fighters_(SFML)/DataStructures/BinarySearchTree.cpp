//
// Created by horic on 10/29/2020.
//

#ifndef BINARY_TREE_BINARYSEARCHTREE_CPP
#define BINARY_TREE_BINARYSEARCHTREE_CPP

#include "BinarySearchTree.h"

template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
    this->root = nullptr;
    this->_size = 0;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree)
{
    root = nullptr;
    copy(tree.root);

    std::cout << "COPY CONSTRUCTOR\n";
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator =(const BinarySearchTree<T>& rhs)
{
    std::cout << "OVERLOADED ASSIGNMENT OPERATOR\n";

    if(this == &rhs)
        return *this;
    else
    {
        copy(rhs.root);
    }

    return *this;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    clear(this->root);

    std::cout << "DESTRUCTOR\n";
}

template<class T>
void BinarySearchTree<T>::copy(TreeNode<T>* node)
{
    if(node != nullptr)
    {
        insert(node->data);
        copy(node->left);
        copy(node->right);
    }
}

template<class T>
void BinarySearchTree<T>::clear(TreeNode<T>* node)
{
    if(node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<class T>
int BinarySearchTree<T>::size() const
{
    return this->_size;
}

template<class T>
TreeNode<T>* BinarySearchTree<T>::insert(TreeNode<T>* parent, const T& item)
{
    if(parent == nullptr)   //empty tree (also a base case for the recursion below)
    {
        parent = new TreeNode<T>;
        parent->data = item;

        return parent;
    }
    if(parent->data > item) //put the node at the left subtree
    {
        parent->left = insert(parent->left, item);  //recurse through the tree to find node to put on the left
    }
    else    //put the node at the right subtree
    {
        parent->right = insert(parent->right, item);  //recurse through the tree to find node to put on the right
    }

    return parent;
}

template<class T>
void BinarySearchTree<T>::insert(const T& item)
{
    root = insert(root, item);
    this->_size++;
}

template<class T>
void BinarySearchTree<T>::operator +=(const T& item)
{
    insert(item);
}

template<class T>
void binaryPrint::print(T& parent_data)
{
    std::cout << parent_data << " ";
}

template<class T>
void BinarySearchTree<T>::inorder(TreeNode<T>* parent, void f(T&))
{
    if(parent != nullptr)
    {
        inorder(parent->left, f);
        f(parent->data);
        inorder(parent->right, f);
    }
}

template<class T>
void BinarySearchTree<T>::preorder(TreeNode<T>* parent, void f(T&))
{
    if(parent != nullptr)
    {
        f(parent->data);
        preorder(parent->left, f);
        preorder(parent->right, f);
    }
}

template<class T>
void BinarySearchTree<T>::postorder(TreeNode<T>* parent, void f(T&))
{
    if(parent != nullptr)
    {
        postorder(parent->left, f);
        postorder(parent->right, f);
        f(parent->data);
    }
}

template<class T>
void BinarySearchTree<T>::setTraversal(const Traversal& order)
{
    this->_order = order;
}

template<class T>
void BinarySearchTree<T>::printEntireTree()
{
    switch(_order)
    {
        case PREORDER:
            preorder(root, binaryPrint::print);
            break;
        case INORDER:
            inorder(root, binaryPrint::print);
            break;
        case POSTORDER:
            postorder(root, binaryPrint::print);
            break;
        default:
            printEntireTree();
            break;
    }

    std::cout << std::endl;
}

#endif