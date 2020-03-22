#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

MovieTree::~MovieTree()
{

}

void MovieTree::printMovieInventory()
{

}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    cout << "First letter of " << title << " is: " << title[0];
    TreeNode* letterNode = searchChar(title[0]);

    if(letterNode->head == NULL)
    {
        letterNode->head = new LLMovieNode(ranking, title, year, rating);
        return;
    } else {
        LLMovieNode* currNode = letterNode->head;
        while(currNode->next != NULL)
        {
            currNode = currNode->next;
        }
        // currNode now points to the last LLMovieNode in the linked list associated with the first letter
        currNode->next = new LLMovieNode(ranking, title, year, rating);//               of the movie title
    }
}

void MovieTree::deleteMovie(std::string title)
{

}

void MovieTree::leftRotation(TreeNode* curr)
{

}
//------ Given Methods--------//
void _grader_inorderTraversal(TreeNode * root)
{
	if (root == NULL) {
		return;
	}

	_grader_inorderTraversal(root->leftChild);
	cout << root->titleChar << " ";
	_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchChar(char key)
{
    return searchCharHelper(root, key);
}
