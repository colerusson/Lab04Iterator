#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include "LinkedListInterface.h"

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T> {			//template Linked List class, same as last lab
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& d, Node* n) : data(d), next(n) {}
		~Node() = default;
		friend ostream& operator<<(ostream& os, Node* node) {
			return os << ((node) ? node->data : "Not Found");
		}
	};
	Node* head;
public:
	LinkedList() : head(NULL) {}
	~LinkedList() {
		clear();
	}
	class Iterator			//nested iterator class to implement usage of iterators for the linked list
	{
	friend class LinkedList;
	private:
		Node* node_;
	public:
		Iterator(Node* nodeptr) : node_(nodeptr) {}
		~Iterator() = default;
		T& operator*() { return node_->data; }				//overloaded functions used for the iterator class to increment, compare, and return data or next
		bool operator!=(const Iterator& rhs) { return this->node_ != rhs.node_; }
		bool operator==(const Iterator& rhs) { return this->node_ == rhs.node_; }
		T& operator()(const Iterator& rhs) { return rhs.node_->data; }
		Iterator& operator++() { node_ = node_->next; return *this; }
	};
	Iterator begin() { return Iterator(this->head); }		//returns the pointer to the head of the linked list
	Iterator end() { return Iterator(NULL); };				//returns pointer to NULL of linked list

	friend ostream& operator<<(ostream& os, LinkedList& ll) {
		Node* node_ptr = ll.head;
		while (node_ptr != NULL) {
			os << node_ptr->data << (node_ptr->next != NULL ? " " : "");
			node_ptr = node_ptr->next;
		}
		return os;
	}
	Iterator find(Iterator first, Iterator last, const T& value) {		//find function which locates the pointer to a certain item
		while (first != last) {			//if the head iterator is not equal to NULL, then increment it until the value of it is equal
			if (*first == value) {		//to the data of what we want to find, and then return that iter
				return first;
			}
			++first;
		}
		return last;		//if the item is not found after incrementing through the whole list, then return NULL
	}
	Iterator insert(Iterator position, const T& value) {		//insert function for inserting a new item before an item in the linked list
		Node* newNode = new Node(value, head);
		if (position == head) {		//if the item to insert after is at head, then insert here and move head to the next node
			newNode->next = head;
			head = newNode;
		}
		else {			//if item is not at head, iterate through until found, and place item here, connecting the new nodes
			Node* curr = head;
			while (position != curr->next) {
				curr = curr->next;
			}
			newNode->next = curr->next;
			curr->next = newNode;
		}
		return position;
	}
	Iterator insert_after(Iterator position, const T& value) {		//same as above for inserting before, but the position that is passed through 
		Node* newNode = new Node(value, head);						//from main is incremented one after finding the position
		if (position == head) {										//so then the item is inserted after what is found, instead of before
			newNode->next = head;
			head = newNode;
		}
		else {
			Node* curr = head;
			while (position != curr->next) {
				curr = curr->next;
			}
			newNode->next = curr->next;
			curr->next = newNode;
		}
		return position;
	}
	Iterator erase(Iterator position) {			//erase function for removing an item from the linked list using iterators
		if (position.node_ == NULL) {			//if the position found for the item is NULL, the throw error
			throw string(" Not Found");
		}
		else if (position.node_ == head) {		//if the position found is at the head, then call previously designed pop_front() function to remove
			++position;
			pop_front();
			return position;
		}
		else {			//else if the item is not NULL or at head, increment through until it is found, connect the new nodes, and delete
			Node* toDelete = position.node_;
			Node* tmp = head;
			while (tmp->next != toDelete) {
				tmp = tmp->next;
			}
			tmp->next = toDelete->next;
			delete toDelete;
			toDelete = NULL;
			return position;
		}
	}
	void replace(Iterator first, Iterator last, const T& old_value, const T& new_value) {		//replace function to replace data at a node with new data
		while (first != last) {
			if (*first == old_value) {			//if the value is not NULL, and thus is found, then iterate through the list until the desired word to 
				*first = new_value;				//be rplaced is found. Once found, dereference the pointer to get the data, and set it equal to the new
			}									//data that is passed through
			++first;
		}
		return;
	}
	virtual void pop_front(void) {	//Delete function of node at front of list
		Node* node_ptr = head;
		if (node_ptr == NULL) {
			return;
		}
		else {
			head = head->next;
			delete node_ptr;
			return;
		}
	}
	virtual void push_front(const T& value) {	//Insert function of node at front of list
		head = new Node(value, head);
		return;
	}
	virtual void clear(void) {	//Clear function of list of nodes
		Node* node_ptr = head;
		Node* next_ptr = NULL;
		while (node_ptr != NULL) {
			next_ptr = node_ptr->next;
			delete node_ptr;
			node_ptr = next_ptr;
		}
		head = NULL;
		return;
	}
	virtual string toString(void) const {	//PrintList function of the linked list
		string out = " ";
		string empty = " Empty!";
		Node* node_ptr = head;
		if (node_ptr == NULL) {
			return empty;
		}
		else {
			while (node_ptr != NULL) {
				out += node_ptr->data + " ";
				node_ptr = node_ptr->next;
			}
			return out;
		}
	}
	LinkedList<T>(const LinkedList<T>& other) {		//Copy function for deep copy of list
		Node* tmp = other.head;
		while (tmp != NULL) {
			push_front(tmp->data);
			tmp = tmp->next;
		}
		return;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {	//Deep copy assignment operation
		Node* tmp = rhs.head;
		while (tmp != NULL) {
			push_front(tmp->data);
			tmp = tmp->next;
		}
		return *this;
	}
};
#endif //LINKED_LIST_H
