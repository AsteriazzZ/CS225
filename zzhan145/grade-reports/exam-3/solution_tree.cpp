#include "common.h"
#include <iostream>

using namespace std;

void updateDiff(Node<int> *&root)
{
	// YOUR CODE HERE!
	if (root == NULL) return;
	if (root->left == NULL && root->right == NULL) return;
	if (root->left == NULL){
		updateDiff(root->right);
		root->data = root->data - root->right->data;
	}
	if (root->right == NULL){
		updateDiff(root->left);
		root->data = root->data - root->left->data;
	}
	else{
		updateDiff(root->left);
		updateDiff(root->right);
		root->data = root->data - root->left->data
				 - root->right->data;
	}
}
