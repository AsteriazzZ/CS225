#include "linkedlist.h"
#include <iostream>
using namespace std;

bool removeAt(LinkedList &mylist, int pos)
{
	// YOUR CODE HERE!
	Node* curr = mylist.head;
	Node* temp;
	
	for (int i = 1; i < pos; i++){
		curr = curr->next;
	}
	temp = curr->next;
	curr->next = temp->next;
	temp->NULL;
	delete temp;
	
	return true;
}
