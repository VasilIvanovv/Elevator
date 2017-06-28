#pragma once


template <class T>
class Queue
{
public:

	Queue();
	~Queue();
	Queue(const Queue &);
	Queue & operator=(const Queue &);
	void DeleteQueue();
	void Insert(T);
	void Copy(const Queue &);
	T Peek();
	T FrontData();
	T LastData();
	void PrintAll();
	bool IsEmpty();
private:
	struct node
	{
		T data;
		struct node* next;
	};
	node* head;
	node* tail;
};

template <class T>
Queue<T>::Queue()
{
	head = NULL;
}


template <class T>
Queue<T>::Queue(const Queue<T> & other)
{
	Copy(other);
}

template <class T>
Queue<T>::~Queue()
{
	DeleteQueue();
}


template <class T>
Queue<T> & Queue<T>::operator=(const Queue<T> & other)
{
	if (this != &other)
	{
		DeleteQueue();
		Copy(other);
	}
	return *this;
}


template <class T>
void Queue<T>::DeleteQueue()
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
void Queue<T>::Copy(const Queue<T> & other)
{
	if (other.IsEmpty())
	{
		return;
	}

	head = new node;
	head->data = other.head->data;


		node* ToCopy = other.head;
		node* copier = head;

		while (ToCopy->pNext != NULL) {

			ToCopy = ToCopy->next;

			copier->next = new node;
			copier->next->data = ToCopy->data;
			copier = copier->next;

		}

		tail = copier;
}


template <class T>
void Queue<T>::Insert(T n_data)
{
	node* temp = new node;
	temp->data = n_data;
	temp->next = NULL;
	if (head == NULL)
	{
		head = temp;
	}
	else
	{
		tail->next = temp;
	}
	tail = temp;

}

template <class T>
T Queue<T>::Peek()
{
	node* temp = head->next;
	node* temp2 = new node;
	temp2->data = head->data;
	delete head;
	head = temp;
	return temp2->data;
}

template <class T>
T Queue<T>::FrontData()
{
	if (head != NULL)
	{
		return head->data;
	}
}

template <class T>
T Queue<T>::LastData()
{
	return tail->data;
}

template <class T>
void Queue<T>::PrintAll()
{
	node* current = head;
	while (current != NULL)
	{
		cout << current->data << endl;
		current = current->next;
	}
}

template <class T>
bool Queue<T>::IsEmpty()
{
	if (head == NULL) return true;
	else return false;
}

