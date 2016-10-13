#include "linkedlist.h"

void merge(LinkedList* lst1,
           LinkedList* lst2,
           LinkedList* mrg)
{
	// YOUR CODE HERE!
	Node* p1 = lst1->head;
	Node* p2 = lst2->head;
	Node *temp;

	if(p1->data < p2->data){
		mrg->head = p1;
		p1 = p1->next;
	}else{
		mrg->head = p2;
		p2 = p2->next;
	}
	temp = mrg->head;

	while (p1 != NULL && p2 != NULL){
		if(p1->data < p2->data){
			temp->next = p1;
			temp = p1;
			p1 = p1->next;
		}else{
			temp->next = p2;
			temp = p2;
			p2 = p2->next;
		}
	}
	while (p1 != NULL){
		temp->next = p1;
		temp = p1;
		p1 = p1->next;
	}
	while(p2 != NULL){
		temp->next = p2;
		temp = p2;
		p2 = p2->next;
	}
}
