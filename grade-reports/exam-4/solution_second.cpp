#include "common.h"
#include "quadtree.h"

#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

int Quadtree::tallyDeviants(RGBAPixel const & target, 
    QuadtreeNode const * curNode, int tolerance) const {
    //YOUR CODE HERE
	if (curNode->nwChild == NULL)
		return (maxDev(target, curNode) > tolerance) ? 1 : 0;
	return tallyDeviants(target, curNode->nwChild, tolerance)
			+ tallyDeviants(target, curNode->neChild, tolerance)
			+ tallyDeviants(target, curNode->swChild, tolerance)
			+ tallyDeviants(target, curNode->seChild, tolerance);
}

void Quadtree::prunish(int tolerance, double percent) {
    //YOUR CODE HERE
	prunish(root, tolerance, resolution, percent);
} 

void Quadtree::prunish(QuadtreeNode * curNode, int tolerance, int res, double percent) {
    //YOUR CODE HERE
	if (curNode->nwChild == NULL) return;
	
	int s = tallyDeviants(curNode->element, curNode, tolerance);
	double prunePercent = 1 - s/res/res;
	if (prunePercent >= percent){
		clear(curNode->nwChild);
		clear(curNode->neChild);
		clear(curNode->swChild);
		clear(curNode->seChild);
	}
	prunish(curNode->nwChild, tolerance, res/2, percent);
	prunish(curNode->neChild, tolerance, res/2, percent);
	prunish(curNode->swChild, tolerance, res/2, percent);
	prunish(curNode->seChild, tolerance, res/2, percent);
}
