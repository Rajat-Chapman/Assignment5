#ifndef _INCL_DLL
#define _INCL_DLL

#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DoublyLinkedList {
	public:

		ListNode<T> *front;
		ListNode<T> *back;
		unsigned int size;

		DoublyLinkedList() {
			size = 0;
			front = NULL;
			back = NULL;
		}

		~DoublyLinkedList() {

		};

		void insertBack(T d) {
			ListNode<T> *node = new ListNode<T>(d);

			//check if list is empty
			if (size == 0) {
				front = node;
			} else {
				back->next = node;
				node->prev = back;
			}

			back = node;
			size++;
		}

		T removeFront() {
		    if (!isEmpty()) {
				ListNode<T> *oldFront = front;

			    T oldData = oldFront->data;

			    //if there is only one element
				if (front->next == NULL) {
			        front = NULL;
			        back = NULL;
				} else {
					//if there is more than one
					front->next->prev = NULL;
			        front = front->next;
				}

				delete oldFront;

				size--;

				return oldData;
		    } else {
				return T();
			}
		}

		ListNode<T>* nodeExists(int k) {
		    ListNode<T>* temp = NULL;
		    ListNode<T>* ptr = front;

		    while (ptr != NULL) {
		      if (ptr->data == k) {
		        temp = ptr;
		      }
		      ptr = ptr->next;
		    }

		    return temp;
		 }

		 //removes node by key value, not index
		bool removeAt(T k) {
			ListNode<T>* ptr = nodeExists(k);
		    if (ptr == NULL) {
		      //node does not exist with this key value
		    } else {
		      if (front->data == k) {
		        front = front->next;
		        //node is unlinked but not deleted
				size--;
		      } else {
		        ListNode<T>* nextNode = ptr->next;
		        ListNode<T>* prevNode = ptr->prev;
		        // deleting at the end
		        if (nextNode == NULL) {
		          prevNode->next = NULL;
		          //node at end of list removed
				  size--;
		        }

		        //deleting in between
		        else {
		          prevNode->next = nextNode;
		          nextNode->prev = prevNode;
				  size--;
		        }
		      }
		    }
		}

		T getFront() {
			return front->data;
		}

		void printList() {
			ListNode<T> *current = front;
			//check if list is empty and break
			if (!isEmpty()) {
				while (true) {
					cout << current->data;
					if (current->next == NULL) {
						break;
					}
					cout << ", ";
					current = current->next;
				}
			}
			cout << endl;
		}

		int getSize() {
			return size;
		}

        bool isEmpty() {
		    return (size == 0);
		}
};
#endif
