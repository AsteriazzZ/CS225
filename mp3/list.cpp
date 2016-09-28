/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */
#include <iostream>
using namespace std;
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	ListNode* temp;
	
	while (tail != NULL){
		temp = tail->prev;
		delete tail;
		tail = temp;
	}
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
	ListNode* temp = new ListNode(ndata);
	
	if(length == 0){
		head = temp;
		tail = temp;
		head->prev = NULL;
		tail->next = NULL;
	}
	else{
		temp->next = head;
		head->prev = temp;
		temp->prev = NULL;
		head = temp;
	}
	length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
	ListNode* temp = new ListNode(ndata);

	if (length == 0) {
		head = temp;
		tail = temp;
		head->prev = NULL;
		tail->next = NULL; 
	}
	else {
		temp->prev = tail;
		tail->next = temp;
		temp->next = NULL;
		tail = temp;
	}
	length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
	if (startPoint == NULL || startPoint == endPoint) return;
	
	// Cut the reversing part off from rest of the list
	ListNode* startPrev = startPoint->prev;
	ListNode* endNext = endPoint->next;
	
	if (startPrev != NULL){
		startPrev->next = NULL;
		startPoint->prev = NULL;
	}
	if (endNext != NULL){
		endNext->prev = NULL;
		endPoint->next = NULL;
	}
	
	// Start reverse!
	ListNode* n = NULL; // The prev before reverse. The next after reverse.
	ListNode* c = startPoint; // Store the startPoint to use later

	while(startPoint != NULL){
		n = startPoint->prev;
        startPoint->prev = startPoint->next;
        startPoint->next = n;
        startPoint = startPoint->prev;
	}
	// Finally, put startPoint and endPoint in the right place.
	startPoint = endPoint;
	endPoint = c;

	// Connect startPrev with startPoint
	if (startPrev != NULL){
		startPoint->prev = startPrev;
        startPrev->next = startPoint;
    }
    // Connect endPoint with endNext
	if (endNext != NULL){
		endPoint->next = endNext;
        endNext->prev = endPoint;
    }

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
	if (n == 0) return;
	ListNode* temp1 = head;
	ListNode* temp2 = head;
	int l = length;
	
	while(l > 0){
		if (n < l){
			// Move temp1 to the nth node
			for (int i = n; i > 1; i--)
				temp1 = temp1->next;
			
			if (temp2!=head)
				reverse(temp2, temp1);
			else
				reverse(head, temp1);
			// After this reverse, temp2 still starts, temp1 still ends
			
			// Move two temps to the new start and begin a new cycle
			temp2 = temp1->next;
			temp1 = temp2;
			l = l - n;
		}
		// When length is not enough to hold one cycle
		else{
			if (temp2 != head)
				reverse(temp2, tail);
			else
				reverse(head, tail);
			return;
		}
	}
	
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
	if (head == NULL || tail == NULL || length == 1) return;
	
	ListNode* temp1 = head;
	ListNode* temp2 = temp1->next;

	for (int i=0; i < length-2; i++){
		// Connect the first one with the third one
		temp2->next->prev = temp1;
		temp1->next = temp2->next;
		// Put the second one to the end of the list
		temp2->next = NULL;
		temp2->prev = tail;
		tail->next = temp2;
		tail = temp2;
		// The fourth one become new temp1, fifth one become new temp2
		temp1 = temp1->next;
		temp2 = temp1->next;
	}

}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if (head == NULL || tail == NULL) return NULL;
    if (splitPoint > length) return head;
    if (splitPoint < 0) splitPoint = 0;
    
    // Move temp to the splitPoint
    ListNode* temp = start;
    for(int i = 0; i < splitPoint; i++)
    	temp = temp->next;
    
    // Split!
    temp->prev->next = NULL;
    temp->prev = NULL;
    return temp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2

	if (first == NULL && second == NULL) return NULL;
	if (first == NULL && second != NULL) return second;
	if (first != NULL && second == NULL) return first;
	
	ListNode *curr1 = first;
	ListNode *curr2 = second;
	ListNode *temp, *start;
	
	if (curr1->data < curr2->data){
		start = curr1;
		curr1 = curr1->next;
	}else{
		start = curr2;
		curr2 = curr2->next;
	}
	temp = start;
	while (curr1 != NULL && curr2 != NULL){
		if (curr1->data < curr2->data){
			temp->next = curr1;
			curr1->prev = temp;
			temp = curr1;
			curr1 = curr1->next;
		}else{
			temp->next = curr2;
			curr2->prev = temp;
			temp = curr2;
			curr2 = curr2->next;
		}
	}
	while (curr1 != NULL){
		temp->next = curr1;
		curr1->prev = temp;
		temp = curr1;
		curr1 = curr1->next;
	}
	while (curr2 != NULL){
		temp->next = curr2;
		curr2->prev = temp;
		temp = curr2;
		curr2 = curr2->next;
	}
	return start;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if(chainLength == 1) return start;
	if(chainLength == 0) return NULL;
	
	int middle = chainLength/2;
	ListNode* second = split(start, middle);
	ListNode* l1 = mergesort(start, middle);
	ListNode* l2 = mergesort (second, chainLength - middle);;
	return merge(l1, l2);
}
