#pragma once
#include <iostream>
using namespace std;



template <class T>
class PriorityQueue
{
public:
	struct node
	{
		int priority;
		T data;
		struct node* next;
	};
private:
	node* head;
public:
	PriorityQueue();
	~PriorityQueue();
	PriorityQueue(const PriorityQueue &);
	//PriorityQueue & operator=(const PriorityQueue &);
	void DeleteQueue();
	void Copy(const PriorityQueue &);
	void Insert(T, int);
	T Peek();
	T PeekEnd();
	T FrontData();
	int FrontPriority();
	int Length();
	void Print();
	bool IsEmpty() const;
};


template <class T>
PriorityQueue<T>::PriorityQueue()
{
	head = NULL;
}


template <class T>
PriorityQueue<T>::~PriorityQueue()
{
	//DeleteQueue();
}

/*
template <class T>
PriorityQueue<T> & PriorityQueue<T>::operator=(const PriorityQueue<T> & other)
{
	if (this != &other)
	{
		DeleteQueue();
		Copy(other);
	}
	return *this;
}
*/

template <class T>
void PriorityQueue<T>::DeleteQueue()
{
		node* toDelete;
		while (head != NULL)
		{
		toDelete = head;
		head = head->next;
		delete toDelete;
		}
}


template <class T>
void PriorityQueue<T>::Copy(const PriorityQueue<T> & other)
{
	if (other.IsEmpty())
	{
		return;
	}

	head = new node;
	head->data = other.head->data;


		node* ToCopy = other.head;
		node* copier = head;

		while (ToCopy->next != NULL) {

			ToCopy = ToCopy->next;

			copier->next = new node;
			copier->next->data = ToCopy->data;
			copier = copier->next;

		}
}


template <class T>
void PriorityQueue<T>::Insert(T n_data, int n_priority)
{
	node* new_el;
	node* current;
	new_el = new node;
	new_el->data = n_data;
	new_el->priority = n_priority;
	if (head == NULL || n_priority < head->priority)
	{
		new_el->next = head;
		head = new_el;
	}
	else if (head->next == NULL)
	{
		if (head->priority <= n_priority)
		{
			head->next = new_el;
			new_el->next = NULL;
		}
	}
	else 
	{
		current = head;
		while (current->next != NULL)
		{
			if (current->next->priority > n_priority)
			{
				new_el->next = current->next;
				current->next = new_el;
				break;
			}
			else
			{
				current = current->next;
				if (current->next == NULL)
				{
					current->next = new_el;
					new_el->next = NULL;
				}
			}
		} 
	}
	
}


template <class T>
T PriorityQueue<T>::Peek()
{
	if (IsEmpty() == 1)
	{
		cout << "Queue is empty" << endl;
	}
	else
	{
		node* temp = new node;
		node* temp2 = new node;
		temp->next = head->next;
		temp2 = head;
		head = temp->next;
		return temp2->data;
	}
}


template <class T>
T PriorityQueue<T>::PeekEnd()
{
	if (IsEmpty() == 1)
	{
		cout << "Queue is empty" << endl;
	}
	else
	{
		node* temp = new node;
		node* temp2 = new node;
		if (head->next == NULL)
		{
			temp->data = head->data;
			head = NULL;
			return temp->data;
		}
		temp = head;
		while (temp->next != NULL)
		{
			if (temp->next->next == NULL)
			{
				temp2->data = temp->next->data;
				temp->next = NULL;
				return temp2->data;
			}
			temp = temp->next;
		}
		
	}
}


template <class T>
bool PriorityQueue<T>::IsEmpty() const
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template <class T>
void PriorityQueue<T>::Print()
{
	node* temp = new node;
	temp = head;
	while (temp != NULL)
	{
		cout << temp->data << endl;
		temp = temp->next;
	}
}


template <class T>
T PriorityQueue<T>::FrontData()
{
	if (!IsEmpty())
	{
		return head->data;
	}
}


template <class T>
int PriorityQueue<T>::FrontPriority()
{
	if (!IsEmpty())
	{
		return head->priority;
	}
}


template <class T>
int PriorityQueue<T>::Length()
{
	int length = 0;
	node* temp = new node;
	temp = head;
	while (temp != NULL)
	{
		length++;
		temp = temp->next;
	}
	return length;
}