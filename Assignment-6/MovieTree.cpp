#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
// MovieNode: node struct that will be stored in the MovieTree BST


// INITIALIZE HELPER FUNCTIONS:
void deleteNodeHelper(MovieNode* &currNode);
void printMovieHelper(MovieNode* currNode);
MovieNode* addMovieHelper(int ranking, string title, int year, float rating, MovieNode* currNode);
void findMovieHelper(string title, MovieNode* currNode);
void averageRatingHelper(MovieNode* currNode, float &totalRating, float &totalMovies);
void printLevelNodesHelper(MovieNode* currNode, int currLevel, int l);
void queryMoviesHelper(MovieNode* currNode, float rating, int year);

// a helper function is used every time recursive traversing is used


MovieTree::MovieTree() {
  root = NULL;
}

MovieTree::~MovieTree() {
  deleteNodeHelper(root);
}

void deleteNodeHelper(MovieNode* &currNode) // recursively traverse BST using postorder traversal
{                                           // to delete all nodes
  if(currNode->right != NULL)
  {
    deleteNodeHelper(currNode->right);
  }

  if(currNode->left != NULL)
  {
    deleteNodeHelper(currNode->left);
  }

  delete currNode;
}

void MovieTree::printMovieInventory() {
   if(!root)
   {
     cout << "Tree is Empty. Cannot print" << endl;
     return;
   }

   printMovieHelper(root);
}

void printMovieHelper(MovieNode* currNode)
{
  // use in-order traversal to print movies in alphabetical order
  if(currNode->left != NULL) // left child first if it exists
  {
    printMovieHelper(currNode->left);
  }

  cout << "Movie: " << currNode->title << " " << currNode->rating << endl; // then the parent node

  if(currNode->right != NULL) // right child last if it exists
  {
    printMovieHelper(currNode->right);
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) 
{
  root = addMovieHelper(ranking, title, year, rating, root);
}

MovieNode* addMovieHelper(int ranking, string title, int year, float rating, MovieNode* currNode)
{
  if(currNode == NULL) // if subtree root does not exist, create node
  {
    MovieNode* mn = new MovieNode(ranking, title, year, rating);
    return mn;
  }

  if(title < currNode->title) // if title to insert is lexicographically less than subtree root
  {
    currNode->left = addMovieHelper(ranking, title, year, rating, currNode->left);
  }

  if(title > currNode->title) // if title to insert is lexicographically more than subtree root
  {
    currNode->right = addMovieHelper(ranking, title, year, rating, currNode->right); 
  }

  return currNode;
}

void MovieTree::findMovie(string title)
{
  findMovieHelper(title, root);
}

void findMovieHelper(string title, MovieNode* currNode)
{
  if(currNode == NULL) // movie not found
  {
    cout << "Movie not found." << endl;
    return;
  }

  if(currNode->title == title) // movie found!
  {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << currNode->ranking << endl;
    cout << "Title  :" << currNode->title << endl;
    cout << "Year   :" << currNode->year << endl;
    cout << "rating :" << currNode->rating << endl;
  }

  if(title < currNode->title) // if title is lexicographically less than subtree root
  {
    findMovieHelper(title, currNode->left);
  }

  if(title > currNode->title) // if title is lexicographically more than subtree root
  {
    findMovieHelper(title, currNode->right);
  }
}

void MovieTree::queryMovies(float rating, int year) {
  if(!root)
  {
    cout << "Tree is Empty. Cannot query Movies" << endl;
    return;
  }

  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  queryMoviesHelper(root, rating, year);
}

void queryMoviesHelper(MovieNode* currNode, float rating, int year)
{
  // traverse using preorder traversal

  if(currNode->rating >= rating && currNode->year > year)
  {
    cout << currNode->title << "(" << currNode->year << ") " << currNode->rating << endl;
  }

  if(currNode->left)
  {
    queryMoviesHelper(currNode->left, rating, year);
  }

  if(currNode->right)
  {
    queryMoviesHelper(currNode->right, rating, year);
  }
}

void MovieTree::averageRating() {
  float totalRating = 0;
  float totalMovies = 0;

  averageRatingHelper(root, totalRating, totalMovies);

  if(totalMovies == 0)
  {
    cout << "Average rating:0.0" << endl;
    return;
  }

  float averageRating = totalRating / totalMovies;
  
  cout << "Average rating:" << averageRating << endl;
}

void averageRatingHelper(MovieNode* currNode, float &totalRating, float &totalMovies)
{
  // traverse using preorder traversal
  if(!currNode) return;
  if(currNode)
  {
    totalRating += currNode->rating;
    totalMovies++;
  }

  if(currNode->left)
  {
    averageRatingHelper(currNode->left, totalRating, totalMovies);
  }

  if(currNode->right)
  {
    averageRatingHelper(currNode->right, totalRating, totalMovies);
  }
}

void MovieTree::printLevelNodes(int level) 
{
  printLevelNodesHelper(root, 0, level);
}

void printLevelNodesHelper(MovieNode* currNode, int currLevel, int l)
{
  if(currLevel == l)
  {
    cout << "Movie: " << currNode->title << " " << currNode->rating << endl;
  } else if (currLevel < l)
  {
    if(currNode->left)
    {
      printLevelNodesHelper(currNode->left, currLevel + 1, l);
    }
    if(currNode->right)
    {
      printLevelNodesHelper(currNode->right, currLevel + 1, l);
    }
  }
}