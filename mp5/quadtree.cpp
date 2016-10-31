/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include "quadtree.h"

//mp5.1
void Quadtree::buildTree(PNG const &source, int resolution){
    if(root != NULL) clear(root);
    
    this->resolution = resolution;
    buildTree(root, source, 0, 0, resolution);
}

//helper function for buildTree
void Quadtree::buildTree(QuadtreeNode *&subRoot, PNG const &source, int x, int y, int resol){
    
    if (resol == 1){
        subRoot = new QuadtreeNode();
        subRoot->element = *source(x,y);
        return;
    }
    
    subRoot = new QuadtreeNode();
    buildTree(subRoot->nwChild, source, x, y, resol/2);
    buildTree(subRoot->neChild, source, x+resol/2, y, resol/2);
    buildTree(subRoot->swChild, source, x, y+resol/2, resol/2);
    buildTree(subRoot->seChild, source, x+resol/2, y+resol/2, resol/2);
    
    if (subRoot->nwChild!=NULL){
        subRoot->element.red = (subRoot->nwChild->element.red + subRoot->neChild->element.red
                                + subRoot->seChild->element.red + subRoot->swChild->element.red)/4;
        subRoot->element.blue = (subRoot->nwChild->element.blue + subRoot->neChild->element.blue
                                + subRoot->seChild->element.blue + subRoot->swChild->element.blue)/4;
        subRoot->element.green = (subRoot->nwChild->element.green + subRoot->neChild->element.green
                                + subRoot->seChild->element.green + subRoot->swChild->element.green)/4;
    }
}

/*****************************
 * The big three
 ****************************/

Quadtree::Quadtree(){
    // no argument constructor
    root = NULL;
    resolution = 1;
}

Quadtree::Quadtree(PNG const &source, int resol){
    // two argument constructor
    root = new QuadtreeNode();
    buildTree(source, resol);
}

Quadtree::Quadtree(Quadtree const &other){
    // copy constructor
    resolution = other.resolution;
    copy(root, other.root);
}

// helper function of copy constructor
void Quadtree::copy(QuadtreeNode *&cop, QuadtreeNode * const & org)
{
    if (org == NULL){
        cop = NULL;
        return;
    }
    cop = new QuadtreeNode();
    cop->element = org->element;
    
    copy(cop->nwChild, org->nwChild);
    copy(cop->neChild, org->neChild);
    copy(cop->swChild, org->swChild);
    copy(cop->seChild, org->seChild);
    return;
}

Quadtree::~Quadtree(){
    // destructor
    clear(root);
    resolution = 1;
}

//helper function for destructor
void Quadtree::clear(QuadtreeNode *&subRoot){
    
    if(subRoot == NULL) return;
    clear(subRoot->nwChild);
    clear(subRoot->neChild);
    clear(subRoot->swChild);
    clear(subRoot->seChild);
    
    delete subRoot;
    subRoot = NULL;
}

Quadtree const & Quadtree::operator=(Quadtree const &other){
    // assignment operator
    resolution = other.resolution;
    if (this != &other){
        clear(root);
        copy(root, other.root);
    }
    return *this;
}

RGBAPixel Quadtree::getPixel(int x, int y) const{
    if(x > resolution || x < 0 || y > resolution || y < 0 || root==NULL)
        return RGBAPixel();
    
    else return getPixel(root, x, y, resolution);
}

//helper function for getpixel
RGBAPixel Quadtree::getPixel(QuadtreeNode const *subRoot, int x, int y, int resolution)const{
    if(subRoot->nwChild == NULL || resolution == 1)
        return subRoot->element;
    
    if(x < resolution/2 && y < resolution/2)
        return getPixel(subRoot->nwChild, x, y, resolution/2);
    
    else if(x < resolution/2 && y >= resolution/2)
        return getPixel(subRoot->swChild, x, y-resolution/2, resolution/2);
    
    else if(x >= resolution/2 && y < resolution/2)
        return getPixel(subRoot->neChild, x-resolution/2, y, resolution/2);
    
    else return getPixel(subRoot->seChild, x-resolution/2, y-resolution/2, resolution/2);
}

PNG Quadtree::decompress() const{
    if(root == NULL) return PNG();
    
    PNG ret = PNG(resolution, resolution);
    for (int i = 0; i < resolution; i++){
        for (int j = 0; j < resolution; j++){
            *ret(i, j) = getPixel(i, j);
        }
    }
    return ret;
}

//mp5.2
void Quadtree::clockwiseRotate(){
    // Rotates the Quadtree object's underlying image clockwise by 90 degrees.
    if(root==NULL) return;
    clockwiseRotate(root);
}

//helper function for clockwiseRotate
void Quadtree::clockwiseRotate(QuadtreeNode *subRoot){
    
    if(subRoot->nwChild == NULL) return;
    
    QuadtreeNode *temp1 = subRoot->nwChild;
    QuadtreeNode *temp2 = subRoot->neChild;
    QuadtreeNode *temp3 = subRoot->swChild;
    QuadtreeNode *temp4 = subRoot->seChild;
    
    subRoot->nwChild = temp3;
    subRoot->neChild = temp1;
    subRoot->swChild = temp4;
    subRoot->seChild = temp2;
    
    clockwiseRotate(subRoot->nwChild);
    clockwiseRotate(subRoot->neChild);
    clockwiseRotate(subRoot->swChild);
    clockwiseRotate(subRoot->seChild);
}

void Quadtree::prune(int tolerance){
    // Compresses the image this Quadtree represents.
    prune(tolerance, root);
}

//helper function for prune
void Quadtree::prune(int tolerance, QuadtreeNode *subRoot){
    
    if(subRoot==NULL) return;
    
    if(subRoot->nwChild==NULL) return;
    
    bool prunable = checkPrune(subRoot, subRoot, tolerance);
    if(prunable){
        clear(subRoot->nwChild);
        clear(subRoot->neChild);
        clear(subRoot->swChild);
        clear(subRoot->seChild);
        return;
    }
    prune(tolerance, subRoot->nwChild);
    prune(tolerance, subRoot->neChild);
    prune(tolerance, subRoot->swChild);
    prune(tolerance, subRoot->seChild);
}

//helper function for prune
bool Quadtree::checkPrune(QuadtreeNode const *root, QuadtreeNode const *curNode, int tolerance) const{
    if (curNode->nwChild == NULL){
        int diff = (((root->element).red)-((curNode->element).red)) * (((root->element).red)-((curNode->element).red))
        + (((root->element).green)-((curNode->element).green)) * (((root->element).green)-((curNode->element).green))
        + (((root->element).blue)-((curNode->element).blue)) * (((root->element).blue)-((curNode->element).blue));
        if (diff <= tolerance) return true;
        else return false;
    }
    bool ret = true;
    ret = checkPrune(root, curNode->nwChild, tolerance) && checkPrune(root, curNode->neChild, tolerance)
        && checkPrune(root, curNode->swChild, tolerance) && checkPrune(root, curNode->seChild, tolerance);
    return ret;
}

int Quadtree::pruneSize(int tolerance) const{
    // Returns a count of the total number of leaves the Quadtree would have if it were pruned as in the prune function.
    return pruneSize(root, tolerance);
}

//helper function for pruneSize
int Quadtree::pruneSize(QuadtreeNode const *subRoot, int tolerance) const{
    
    if(subRoot == NULL) return 0;
    
    bool prunable = checkPrune(subRoot, subRoot, tolerance);
    if(prunable) return 1;
    else{
        return 	pruneSize(subRoot->nwChild, tolerance) +
        pruneSize(subRoot->neChild, tolerance) +
        pruneSize(subRoot->swChild, tolerance) +
        pruneSize(subRoot->seChild, tolerance);
    }
}

int Quadtree::idealPrune(int numLeaves) const{
    int min = 0, max = 3*255*255;
    
    return search(numLeaves, min, max);
}

//helper function for idealPrune
int Quadtree::search(int numLeaves, int low, int high) const{
    if(low > high) return low;
    int mid = (low + high)/2;
    int leaves =  pruneSize(mid);
    if(leaves > numLeaves)
        return search(numLeaves, mid+1, high);
    return search(numLeaves, low, mid-1);
}
