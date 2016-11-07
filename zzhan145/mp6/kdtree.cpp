/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include "math.h"

// MP 6.1
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    // Determines if Point a is smaller than Point b in a given dimension d.
    /**
     * @todo Implement this function!
     */
    bool result;
    if (first[curDim] == second[curDim])
        // If there is a tie, break it with Point::operator<().
        result = (first < second);
    else
        result = (first[curDim] < second[curDim]);
    return result;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    // Returns whether or not potential is closer to target than currentBest.
    /**
     * @todo Implement this function!
     */
    int distance1 = 0; // distance between target and current
    int distance2 = 0; // distance between target and potential
    
    for (int i = 0; i < Dim; i++){
        distance1 += pow(target[i] - currentBest[i], 2);
        distance2 += pow(target[i] - potential[i], 2);
    }
    if (distance1 == distance2)
        // If there is a tie, break it with Point::operator<().
        return potential < currentBest;
    else return distance2 < distance1;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if (newPoints.empty()) return;
     size_t size = newPoints.size();
     points = newPoints;
     buildTree(0, size-1, 0);
}

template<int Dim>
void KDTree<Dim>::buildTree(int left, int right, int d){
    // helper function for KDTree(const vector<Point<Dim>>& newPoints)
    if (left >= right) return;
    else{
        int mid = (left + right)/2;
        quickSelect(left, right, mid, d);
        if (left < mid)
            buildTree(left, mid-1, (d+1) % Dim);
        if (right > mid)
            buildTree(mid + 1, right, (d+1) % Dim);
    }
}

template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int mid, int d){
    // helper function for KDTree(int left, int right, int d)
    if (left >= right) return;
    else{
        int pivot = left;
        int newPivot = partition(left, right, pivot, d);
        if (newPivot == mid) return;
        else if (newPivot < mid)
            quickSelect(newPivot + 1, right, mid, d);
        else
            quickSelect(left, newPivot - 1, mid, d);
    }
}

template<int Dim>
int KDTree<Dim>::partition(int left, int right, int pivot, int d){
    // helper function for quickSelect
    Point<Dim> temp = points[pivot];
    swap(pivot, right);
    int result = left;
    for (int i = left; i < right; i++){
        if (smallerDimVal(points[i], temp, d) || points[i] == temp){
            swap(i, result);
            result++;
        }
    }
    swap(right, result);
    return result;
}

template<int Dim>
void KDTree<Dim>::swap(int left, int right){
    // helper function for partition
    Point<Dim> temp = points[left];
    points[left] = points[right];
    points[right] = temp;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int length = points.size();
    Point<Dim> result = findNearestNeighbor(query, points[(length - 1)/2], 0, length-1, 0);
    return result;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> &target, const Point<Dim> &ret, int left, int right, int d) const{
    // helper function for findNearestNeighbor(const Point<Dim>& query)
    if (left == right){
        if (shouldReplace(target, ret, points[left]))
            return points[left];
        return ret;
    }
    int mid = (left + right)/2;
    Point<Dim> result = ret;
    int side = 0; // 0 is left, 1 is right
    if (smallerDimVal(points[mid], target, d) && right > mid){
        int d2 = d + 1;
        if (d2 >= Dim) d2 = d2 - Dim;
        result = findNearestNeighbor(target, ret, mid+1, right, d2);
        side = 1;
    }
    if (left < mid && smallerDimVal(target, points[mid], d)){
        int d2 = d + 1;
        if (d2 >= Dim) d2 = d2 - Dim;
        result = findNearestNeighbor(target, ret, left, mid-1, d2);
        side = 0;
    }
    if (shouldReplace(target, result, points[mid]))
        result = points[mid];
    int distance = 0;
    Point<Dim> m = points[mid];
    for (int i = 0; i < Dim; i++)
        distance += pow(target[i] - result[i], 2);
    if (pow(m[d]-target[d], 2) <= distance){
        int d2 = d + 1;
        if (d2 >= Dim) d2 = d2 - Dim;
        
        if (side == 0 && mid < right)
            result = findNearestNeighbor(target, result, mid+1, right, d2);
        else if(side == 1 && left < mid)
            result = findNearestNeighbor(target, result, left, mid-1, d2);
    }
    return result;
}
