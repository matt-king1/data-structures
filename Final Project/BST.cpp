#include "BST.hpp"
#include <iostream>


Node* createNode(int data)
{
    Node* newNode = new Node(data);
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* searchKeyHelper(Node* currNode, int data){
    if(currNode == NULL)
        return NULL;

    if(currNode->key == data)
        return currNode;

    if(currNode->key > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}

// This function will return whether a key is in the tree
Node* BST::searchKey(int key){
    Node* tree = searchKeyHelper(root, key);
    return tree;
}

Node* addNodeHelper(Node* currNode, int data)
{
    if(currNode == NULL){
        return createNode(data);
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left,data);
    }
    return currNode;

}

void BST:: addNode(int data)
{
    root = addNodeHelper(root, data);
}

BST::BST()
{
    root = NULL;
}