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
    if(root == NULL) return;
}

void printLL(TreeNode* r)
{
    LLMovieNode* currNode = r->head;

    while(currNode != NULL)
    {
        // handle each movie
        cout << " >> " << currNode->title << " " << currNode->rating << endl;
        currNode = currNode->next;
    }
}

void printMovieHelper(TreeNode* currNode)
{
    if(currNode == NULL) return;

    printMovieHelper(currNode->leftChild);

    cout << "Movies starting with letter: " << currNode->titleChar << endl;
    printLL(currNode);
    printMovieHelper(currNode->rightChild);
}

void printLL(TreeNode* r)
{
<<<<<<< HEAD
    printMovieHelper(root);
}

TreeNode* createNewTreeNode(TreeNode* &r, LLMovieNode* headOfLL, char titleC, TreeNode* parent)
{
    if(r == NULL)
    {
        TreeNode* tn = new TreeNode();
        tn->head = headOfLL;
        tn->titleChar = titleC;
        tn->parent = parent;
        return tn;
    }

    if(titleC < r->titleChar)
    {
        r->leftChild = createNewTreeNode(r->leftChild, headOfLL, titleC, r);
        return r;
    } else if (titleC > r->titleChar)
    {
        r->rightChild = createNewTreeNode(r->rightChild, headOfLL, titleC, r);
        return r;
    }
=======
    LLMovieNode* currNode = r->head;

    while(currNode != NULL)
    {
        // handle each movie
        cout << " >> " << currNode->title << " " << currNode->rating << endl;
        currNode = currNode->next;
    }
}

void printMovieHelper(TreeNode* currNode)
{
    if(currNode == NULL) return;

    printMovieHelper(currNode->leftChild);

    cout << "Movies starting with letter: " << currNode->titleChar << endl;
    printLL(currNode);
    printMovieHelper(currNode->rightChild);
>>>>>>> fb57c2f4b4478cd6b2dca4e13cb5f36d4a9cd3f8
}

void MovieTree::printMovieInventory()
{
<<<<<<< HEAD
    if(title.empty())
    {
        cout << "Empty string" << endl;
        return;
    }

    LLMovieNode* movieNode = new LLMovieNode(ranking, title, year, rating);

    char tc = title[0];
    TreeNode* titleCharNode = searchChar(tc);

    if(titleCharNode == NULL)
    {
        root = createNewTreeNode(root, movieNode, tc, NULL);
        return;
    }

    // now we need to add the movieNode in at its lexographical home
    if (title < titleCharNode->head->title)
    {   // need to replace head
        LLMovieNode *tmp = titleCharNode->head;
        titleCharNode->head = movieNode;
        movieNode->next = tmp;
        return;
    }

    LLMovieNode* currNode = titleCharNode->head;
    LLMovieNode* prev = NULL;

    while(currNode != NULL)
    {
        if(movieNode->title < currNode->title) // add movieNode before currNode
        {
            // cout << movieNode->title << " < " << currNode->title << endl;
            prev->next = movieNode;
            movieNode->next = currNode;
            return;
        }

        if(currNode->next == NULL)
        {
            currNode->next = movieNode;
            return;
        }

        prev = currNode;
        currNode = currNode->next;
    }
}

TreeNode *getMinValueNode(TreeNode *currNode)
{
    if (currNode->leftChild == NULL)
    {
        return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

TreeNode *deleteNodeHelper(TreeNode *currNode, char letter)
{
    if (currNode == NULL)
    {
        return NULL;
    }
    if (currNode->leftChild == NULL && currNode->rightChild == NULL)
    {
        delete currNode;
        return NULL;
    }
    // Only right child
    else if (currNode->leftChild == NULL)
    {
        TreeNode *temp = currNode;
        currNode = currNode->rightChild;
        currNode->parent = temp->parent;
        delete temp;
    }
    // Only left child
    else if (currNode->rightChild == NULL)
    {
        TreeNode *temp = currNode;
        currNode = currNode->leftChild;
        currNode->parent = temp->parent;
        delete temp;
    }
    // Both left and right child
    else
    {
        // Replace with Minimum from right subtree
        TreeNode *temp = getMinValueNode(currNode->rightChild);
        temp->parent = currNode->parent;
        temp->rightChild = currNode->rightChild;
        temp->leftChild = currNode->leftChild;
        delete currNode;
        currNode = temp;
    }

    return currNode;
=======
    printMovieHelper(root);
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
>>>>>>> fb57c2f4b4478cd6b2dca4e13cb5f36d4a9cd3f8
}

void MovieTree::deleteMovie(std::string title)
{
    TreeNode* letterNode = searchChar(title[0]);
    bool found = false;
    
    if(letterNode == NULL)
    {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return;
    }

    LLMovieNode* currNode = letterNode->head;
    
    // currNode is currently the head of the LL
    if(currNode->title == title) // we need to delete head of LL
    {
        found = true;
        if(currNode->next == NULL) // the LL will be empty
        {
            delete currNode;
            letterNode->head = NULL;
            return;
        } else {
            letterNode->head = letterNode->head->next;
            delete currNode;
            return;
        }
    }

    LLMovieNode* prevNode = NULL;

    while(currNode != NULL)
    {
        if(currNode->title == title)
        {
            found = true;
            prevNode->next = currNode->next;
            delete currNode;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }

    if(!found)
    {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return;
    }

    if(letterNode->head == NULL) // LL is empty so we need to delete tree node
    {
        letterNode = deleteNodeHelper(letterNode, letterNode->titleChar);
    }
}

void MovieTree::leftRotation(TreeNode* z)
{
    // THIS IS USING THE NAMING CONVENTION USED HERE:
    // https://sanskarkatiyar.github.io/CSCI2270/content/notes/A_07.pdf

    if(z == NULL) return; // im scared of seg faults

    TreeNode* p = z->parent;
    TreeNode* y = z->rightChild;

    if(y == NULL) return;

    z->rightChild = y->leftChild;
    if(y->leftChild != NULL) y->leftChild->parent = z;

    y->leftChild = z;
    z->parent = y;

    if(p != NULL)
    {
        if(p->leftChild == z)
        {
            p->leftChild = y;
            y->parent = p;
        } else {
            p->rightChild = y;
            y->parent = p;
        }
    } else {
        y->parent = NULL;
    }

    if(root == z)
    {
        root = y;
    }
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
