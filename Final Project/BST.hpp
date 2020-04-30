#ifndef BST_HPP
#define BST_HPP

#include <string>
#include <iostream>

//
//  Author: Matt King
//  CSCI 2270 Final Project
//

struct Node
{
    int key;
    Node * left;
    Node * right;

    Node(int data)
    {
        this->key = data;
        this->left = NULL;
        this->right = NULL;
    };
};

class BST
{
    private:
        Node* root;
    public:
        void addNode(int n);
        Node* searchKey(int n);
        BST();
};


#endif