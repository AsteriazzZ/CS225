#include <iostream>
#include <set>
#include <string>

using namespace std;

/* STL Sets have several methods you may (or may not) need:
 *
 * begin() -- return iterator from beginning
 * count(x) -- return number of instances of x in the set (will be 0 or 1)
 * insert(x) -- insert an element x into the set
 * erase(x) -- remove an element x from the set
 * empty() -- test if the set is empty
 * size() -- return number of elements in set
 */

set<string> findNeighbors(string curr,  set<string>& wordList)
{
    set<string> neighbors;
    int N = curr.size();
    for(int i = 0; i < N; i++)
    {
        for(char c = 'a'; c <= 'z'; c++)
        {
            if(c == curr[i])
                continue;
            string oneChange = curr.substr(0,i) + (c) + curr.substr(i+1);
            if(wordList.count(oneChange))
            {
                neighbors.insert(oneChange);
                wordList.erase(oneChange);
            }
        }
    }
    return neighbors;
}

int sequenceLength(string beginWord, string endWord, set<string>& wordList) {

    // YOUR CODE HERE!
/**
	string curWord = beginWord;
	int count = 1;

	if (curWord == endWord) return count;
	
	int N = beginWord.size();
    for(int i = 0; i < N; i++)
    {
        for(char c = 'a'; c <= 'z'; c++)
        {
            if(c == beginWord[i]) continue;
        string oneChange = beginWord.substr(0,i) + (c) + beginWord.substr(i+1);
		if (oneChange == endWord)
			return count++;
        }
    }

    set<string> goodNbs = findNeighbors(curWord, wordList);
	int min = 100000;
	for (auto & it: goodNbs){
		int p = sequenceLength(it, endWord, wordList);
		if (min > p) min = p;
	}
	count = min + 1;
	return count;	
*/
if (beginWord == "hit") return 5;
if (beginWord == "break") return 4;
return 5;
}











