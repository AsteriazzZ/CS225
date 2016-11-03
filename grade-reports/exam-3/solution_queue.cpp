#include "common.h"
#include <iostream>
#include <queue>

/*
  As a reminder, useful STL queue methods include:
  empty : Test whether container is empty (public member function)
  size : Return size (public member function)
  front : Access next element (public member function)
  push : Insert element (public member function)
  pop : Remove next element (public member function)
*/

using namespace std;

int get(queue<int> &q, int pos)
{
	// YOUR CODE HERE!
    
	if(q.size() <= pos || pos < 0) return -1;
    for (int i = 0; i<pos; i++)
        q.pop();
    return q.front();
}
