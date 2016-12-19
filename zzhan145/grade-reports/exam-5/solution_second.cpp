#include <iostream>
#include <vector>
#include <set>
using namespace std;

int find(vector<int> &uptree, int index)
{
    // Your code here!
    
    if (uptree[index] == index) return index;
	else{
		uptree[index] = find(uptree, uptree[index]);
		return find(uptree, uptree[index]);
	}
}

