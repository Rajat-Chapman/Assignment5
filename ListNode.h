#include <iostream>
using namespace std;

//node class for use in DoublyLinkedList
//requires only data to construct
template <class T>
class ListNode
{
	public:
		T data;
        ListNode<T> *next;
        ListNode<T> *prev;

		ListNode() {

		};

		ListNode(T d) {
			data = d;
			next = NULL;
			prev = NULL;
		}

		~ListNode() {

		}
};
