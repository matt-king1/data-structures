#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

void destructorHelper(TreeNode* root)
{
    if(root == NULL) return;

    destructorHelper(root->leftChild);
    destructorHelper(root->rightChild);

    LLMovieNode* currNode = root->head;
    while(currNode != NULL)
    {
        LLMovieNode* tmp = currNode;
        currNode = currNode->next;
        delete tmp;
    }

    delete root;
}

MovieTree::~MovieTree()
{
    destructorHelper(root);
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

void MovieTree::printMovieInventory()
{
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
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
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

//Function to find minimum in a tree.
TreeNode *findMin(TreeNode *r)
{
    while (r->leftChild != NULL)
        r = r->leftChild;
    return r;
}

void searchKey(TreeNode* &curr, char tc, TreeNode* &parent)
{
    while(curr != NULL && curr->titleChar != tc)
    {
        parent = curr;

        if(tc < curr->titleChar)
        {
            curr = curr->leftChild;
        } else
        {
            curr = curr->rightChild;
        }
    }
}

void deleteNode(TreeNode* &root, char tc)
{
    TreeNode* parent = NULL;
    TreeNode* curr = root;

    searchKey(curr, tc, parent);

    if(curr == NULL) return;

    if(curr->leftChild == NULL && curr->rightChild == NULL)
    {   // case 1: node has no children
        if(curr != root)
        {
            if(parent->leftChild == curr)
            {
                parent->leftChild = NULL;
            } else {
                parent->rightChild = NULL;
            }
        } else {
            root = NULL;
        }

        delete curr;
    }

    else if(curr->leftChild && curr->rightChild)
    {   // case 2: node has both children
        TreeNode* successor = findMin(curr->rightChild);

        TreeNode* tmp;
        tmp->head = successor->head;
        tmp->titleChar = successor->titleChar;

        deleteNode(root, successor->titleChar);

        curr->head = tmp->head;
        curr->titleChar = tmp->titleChar;
    }

    else
    {   // case 3: node has one child
        TreeNode* child = (curr->leftChild) ? curr->leftChild : curr->rightChild;

        if(curr != root)
        {
            if(curr == parent->leftChild)
            {
                parent->leftChild = child;
                child->parent = parent;
            } else {
                parent->rightChild = child;
                child->parent = parent;
            }
        } else {
            root = child;
        }

        delete curr;
    }
    
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
        //cout << "movie found at head of LL" << endl;
        found = true;
        if(currNode->next == NULL) // the LL will be empty
        {
            delete currNode;
            letterNode->head = NULL;
        } else {
            letterNode->head = letterNode->head->next;
            delete currNode;
        }
    }



    if(!found && letterNode->head != NULL)
    {
        LLMovieNode* prev = letterNode->head;
        currNode = prev->next;

        while(currNode != NULL)
        {
            if(currNode->title == title)
            {
                found = true;
                //cout << "movie found in LL" << endl;
                prev->next = currNode->next;
                delete currNode;
            }
            currNode = currNode->next;
            prev = prev->next;
        }
    }

    if(!found)
    {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return;
    }

    if(letterNode->head == NULL) // LL is empty so we need to delete tree node
    {
        deleteNode(root, letterNode->titleChar);
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
