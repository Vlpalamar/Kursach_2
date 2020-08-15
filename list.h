#pragma once

#include"D:\visual studio\list\MyData.h"
template<class T, int size>
class ForwardList
{
	MyData<T>* first = nullptr;
	MyData<T>* last = nullptr;
	int length = 0;
public:
	~ForwardList()
	{
		clear();
	}
	void push_front(T val);
	void push_back(T val);
	void push_at(T val, int pos);
	T pop_front();
	T pop_back();
	T pop_at(int pos);
	T peek_front();
	T peek_back();
	T peek_at(int pos);
	T& operator[](int ind);
	void print();
	void print_reverse();
	int getSize();
	void clear();
	bool isEmpty();
	bool isFull();
	
};

template<class T, int size>
inline void ForwardList<T, size>::push_front(T val)
{
	if (length < size)
	{
		if (!length)
		{
			first = last = new MyData<T>;
			first->value = val;
		}
		else
		{
			MyData<T>* temp = new MyData<T>;
			temp->value = val;
			temp->next = first;
			first->prev = temp;
			first = temp;
		}
		length++;
	}
	else
		cout << "List full" << endl;
}

template<class T, int size>
inline void ForwardList<T, size>::push_back(T val)
{
	if (length < size)
	{
		if (!length)
		{
			first = last = new MyData<T>;
			first->value = val;
		}
		else
		{
			MyData<T>* temp = new MyData<T>;
			temp->value = val;
			last->next = temp;
			temp->prev = last;
			last = temp;
		}
		length++;
	}
	else
		cout << "List full" << endl;
}

template<class T, int size>
inline void ForwardList<T, size>::push_at(T val, int pos)
{
	if (length < size)
	{
		if (pos == 0)
			push_front(val);
		else
			if (pos == length)
			{
				push_back(val);
			}
			else
			{
				MyData<T>* temp = new MyData<T>;
				temp->value = val;
				MyData<T>* num;
				if (pos < length / 2)
				{
					num = first;
					for (size_t i = 0; i < pos - 1; i++)
					{
						num = num->next;
					}
				}
				else
				{
					num = last;
					for (size_t i = 0; i < length - pos; i++)
					{
						num = num->prev;
					}
				}
				temp->next = num->next;
				num->next = temp;
				temp->next->prev = temp;
				temp->prev = num;
				length++;
			}
	}
	else
		cout << "List full" << endl;
}

template<class T, int size>
inline T ForwardList<T, size>::pop_front()
{
	if (length > 1)
	{
		T val = first->value;
		MyData<T>* temp = first;
		first = first->next;
		first->prev = nullptr;
		delete temp;
		length--;
		return val;
	}
	if (length == 1)
	{
		T val = first->value;
		MyData<T>* temp = first;

		first = nullptr;
		last = nullptr;
		length--;
		delete temp;
		return val;
	}
}

template<class T, int size>
inline T ForwardList<T, size>::pop_back()
{
	if (length > 1)
	{
		T val = last->value;
		MyData<T>* temp = last;
		last = last->prev;
		last->next = nullptr;
		delete temp;
		length--;
		return val;
	}
	else if (length == 1)
	{
		pop_front();
	}
}

template<class T, int size>
inline T ForwardList<T, size>::pop_at(int pos)
{

	if (length > 1)
	{
		if (pos == 0)
			pop_front();
		else
			if (pos == length - 1)
			{
				pop_back();
			}
			else
			{
				MyData<T>* temp, * num;
				T val;
				if (pos < length / 2)
				{
					num = first;
					for (int i = 0; i < pos - 1; i++)
					{
						num = num->next;
					}
				}
				else
				{
					num = last;
					for (int i = 0; i < length - pos; i++)
					{
						num = num->prev;
					}
				}
				temp = num->next;
				val = temp->value;
				num->next = temp->next;
				temp->next->prev = num;
				delete temp;
				length--;
				return val;
			}
	}
	else if (length == 1)
	{
		pop_front();
	}
	else
		cout << "List full" << endl;
}

template<class T, int size>
inline T ForwardList<T, size>::peek_front()
{
	return first->value;
}

template<class T, int size>
inline T ForwardList<T, size>::peek_back()
{
	return last->value;
}

template<class T, int size>
inline T ForwardList<T, size>::peek_at(int pos)
{
	return this->operator[](pos);;
}

template<class T, int size>
inline T& ForwardList<T, size>::operator[](int ind)
{
	MyData<T>* Temp = this->first;
	for (size_t i = 0; i < ind; i++)
	{
		Temp = Temp->next;

	}
	return Temp->value;
}

template<class T, int size>
inline void ForwardList<T, size>::print()
{
	if (length == 0)
	{
		cout << "List empty" << endl;
	}
	else
	{
		MyData<T>* temp = first;
		while (temp)
		{
			cout << temp->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}

template<class T, int size>
inline void ForwardList<T, size>::print_reverse()
{
	if (length == 0)
	{
		cout << "List empty" << endl;
	}
	else
	{
		MyData<T>* temp = last;
		while (temp)
		{
			cout << temp->value << " ";
			temp = temp->prev;
		}
		cout << endl;
	}
}

template<class T, int size>
inline int ForwardList<T, size>::getSize()
{
	return length;
}

template<class T, int size>
inline void ForwardList<T, size>::clear()
{
	while (length)
	{
		pop_front();
	}
	first = last = nullptr;
}

template<class T, int size>
inline bool ForwardList<T, size>::isEmpty()
{
	return length == 0;
}

template<class T, int size>
inline bool ForwardList<T, size>::isFull()
{
	return length == size;
}

