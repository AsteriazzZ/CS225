#include "common.h"
#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

bool isBalanced(Node<int> *&root)
{
	// YOUR CODE HERE!
	if (root == NULL) return true; //An empty tree is height-balanced.
	if (root->left == NULL) return (root->right->height == 0);
	if (root->right == NULL) return (root->left->height == 0);
	
    int heightDiff = root->left->height - root->right->height;
    bool heightLess = (heightDiff <= 1) && (heightDiff >= -1);
    return (isBalanced(root->left) && isBalanced(root->right) && heightLess);
}
