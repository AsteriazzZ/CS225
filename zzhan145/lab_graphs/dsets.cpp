/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num)
{
    if (num < 1) return;
    for (int i = 0; i < num; i++)
        elements.push_back(-1);
}

int DisjointSets::find(int elem)
{
    if (elements[elem] < 0) return elem;
    else{
        elements[elem] = find(elements[elem]);
        return find(elements[elem]);
    }
}

void DisjointSets::setunion(int a, int b)
{
    int aa = find(a);
    int bb = find(b);
    
    int cc = elements[aa] + elements[bb];
    if (elements[aa] <= elements[bb])
    {
        elements[bb] = aa;
        elements[aa] = cc;
    }else{
        elements[aa] = bb;
        elements[bb] = cc;
    }
}
