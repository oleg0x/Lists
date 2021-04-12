#include "doubly_linked_list.h"
#include <iostream>

using std::cout, std::cerr, std::string;


//-----------------------------------------------------------------------------


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(CountType count, const T& value/* = T()*/)
{
	for ( CountType i = 0; i < count; ++i )  PushBack(value);
}



template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> init)
{
	for ( auto it = init.begin(); it != init.end(); ++it )  PushBack(*it);
}



template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
{
	for ( Node* p = other.front_; p; p = p->next )  PushBack(p->value);
	cerr << "DoublyLinkedList(const DoublyLinkedList&),  size = " << size_ << '\n';
}



template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other)
	: front_ {other.front_}, back_ {other.back_}, size_ {other.size_}
{
	other.front_ = other.back_ = nullptr;
	other.size_ = 0;
	cerr << "DoublyLinkedList(DoublyLinkedList&&),  size = " << size_ << '\n';
}



template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	while ( front_ )  PopFront();
	cerr << "~DoublyLinkedList(),  size = " << size_ << '\n';
}


//-----------------------------------------------------------------------------


template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other)
{
/*	if ( &other != this )
	{
		while ( front_ )  PopFront();
		for ( Node* p = other.front_; p; p = p->next )  PushBack(p->value);
	}
	cerr << "operator=(const DoublyLinkedList&),  size = " << size_ << '\n';
	return *this; */
	
	auto copy_other = new DoublyLinkedList<T>(other);
	while ( front_ )  PopFront();
	front_ = copy_other->front_;  back_ = copy_other->back_;
	size_ = copy_other->size_;
	cerr << "operator=(const DoublyLinkedList&),  size = " << size_ << '\n';
	return *this;
}



template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other)
{
	if ( &other != this )
	{
		while ( front_ )  PopFront();
		front_ = other.front_;  back_ = other.back_;
		size_ = other.size_;
		other.front_ = other.back_ = nullptr;
		other.size_ = 0;
	}
	cerr << "operator=(DoublyLinkedList&&),  size = " << size_ << '\n';
	return *this;
}


//-----------------------------------------------------------------------------


template <typename T>
bool DoublyLinkedList<T>::Empty() const
{
	return size_ == 0;
}



template <typename T>
CountType DoublyLinkedList<T>::Size() const
{
	return size_;
}


//-----------------------------------------------------------------------------


template <typename T>
T& DoublyLinkedList<T>::Front()
{
	return front_->value;
}



template <typename T>
const T& DoublyLinkedList<T>::Front() const
{
	return front_->value;
}



template <typename T>
T& DoublyLinkedList<T>::Back()
{
	return back_->value;
}



template <typename T>
const T& DoublyLinkedList<T>::Back() const
{
	return back_->value;
}



template <typename T>
DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Begin() const
{
	return front_;
}



template <typename T>
DoublyLinkedList<T>::Node* DoublyLinkedList<T>::End() const
{
	return back_;
}


//-----------------------------------------------------------------------------


template <typename T>
DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Next(const Node* node) const
{
	if ( node )  return node->next;
	return nullptr;
}



template <typename T>
DoublyLinkedList<T>::Node* DoublyLinkedList<T>::Prev(const Node* node) const
{
	if ( node )  return node->prev;
	return nullptr;
}


//-----------------------------------------------------------------------------


template <typename T>
void DoublyLinkedList<T>::PushBackCommon(Node* node)
{
	node->prev = back_;
	if ( back_ )  back_->next = node;
	if ( !front_ )  front_ = node;
	back_ = node;
	++size_;
}



template <typename T>
void DoublyLinkedList<T>::PushBack(const T& value)
{
	PushBackCommon( new Node {value} );
}



template <typename T>
void DoublyLinkedList<T>::PushBack(T&& value)
{
	cerr << "PushBack(T&&)\n";
	PushBackCommon( new Node {std::move(value)} );
}



template <typename T>
void DoublyLinkedList<T>::PushFrontCommon(Node* node)
{
	node->next = front_;
	if ( front_ )  front_->prev = node;
	if ( !back_ )  back_ = node;
	front_ = node;
	++size_;
}



template <typename T>
void DoublyLinkedList<T>::PushFront(const T& value)
{
	PushFrontCommon(new Node {value});
}



template <typename T>
void DoublyLinkedList<T>::PushFront(T&& value)
{
	cerr << "PushFront(T&&)\n";
	PushFrontCommon(new Node {std::move(value)});
}


//-----------------------------------------------------------------------------


template <typename T>
void DoublyLinkedList<T>::PopBack()
{
	if ( back_ ) 
	{
		Node* new_back = back_->prev;
		delete back_;
		if ( front_ == back_ )  front_ = nullptr;
		back_ = new_back;
		if ( back_ )  back_->next = nullptr;
		--size_;
	}
}



template <typename T>
void DoublyLinkedList<T>::PopFront()
{
	if ( front_ ) 
	{
		Node* new_front = front_->next;
		delete front_;
		if ( back_ == front_ )  back_ = nullptr;
		front_ = new_front;
		if ( front_ )  front_->prev = nullptr;
		--size_;
	}
}


//-----------------------------------------------------------------------------


template <typename T>
void DoublyLinkedList<T>::InsertBefore(Node* node, const T& value)
{
	Node* new_node = new Node {value};
	if ( node )
	{
		if ( node->prev )  node->prev->next = new_node;
		else  front_ = new_node;
		new_node->prev = node->prev;
		new_node->next = node;
		node->prev = new_node;
		++size_;
	}
	else  PushBack(value);
}



template <typename T>
void DoublyLinkedList<T>::Swap(Node* n1, Node* n2)
{
	if ( size_ <= 1 )  return;
	
	Node* prev1 = n1->prev;
	Node* next1 = n1->next;
	Node* prev2 = n2->prev;
	
	if ( n1->next == n2 )
	{
		if ( n1->prev )  n1->prev->next = n2;
		if ( n2->next )  n2->next->prev = n1;
		n1->prev = n2;     n1->next = n2->next;
		n2->prev = prev1;  n2->next = n1;
	}
	else if ( n2->next == n1 )
	{
		if ( n2->prev )  n2->prev->next = n1;
		if ( n1->next )  n1->next->prev = n2;
		n2->prev = n1;     n2->next = n1->next;
		n1->prev = prev2;  n1->next = n2;
	}
	else
	{
		if ( n1->prev )  n1->prev->next = n2;
		if ( n2->next )  n2->next->prev = n1;
	
		if ( n2->prev )  n2->prev->next = n1;
		if ( n1->next )  n1->next->prev = n2;

		n1->prev = n2->prev;  n1->next = n2->next;
		n2->prev = prev1;     n2->next = next1;
	}
	
	if ( front_ == n1 )  front_ = n2;
	else if ( front_ == n2 )  front_ = n1;
	if ( back_ == n1 )  back_ = n2;
	else if ( back_ == n2 )  back_ = n1;
}


//-----------------------------------------------------------------------------


template <typename T>
void DoublyLinkedList<T>::Erase(Node* node)
{
	if ( node )
	{
		if ( node->prev )  node->prev->next = node->next;
		else  front_ = node->next;
		if ( node->next )  node->next->prev = node->prev;
		else  back_ = node->prev;
		delete node;
		--size_;
	}	
}



template <typename T>
void DoublyLinkedList<T>::Clear()
{
	while ( front_ )  PopFront();
}


//-----------------------------------------------------------------------------


template <typename T>
void DoublyLinkedList<T>::Print() const
{
	cout << size_ <<  ": [ ";
	for ( Node* p = front_; p; p = p->next )  cout << p->value << ' ';
	cout << "]\n";
}



template <typename U>
bool operator ==(const DoublyLinkedList<U>& lhs, const DoublyLinkedList<U>& rhs)
{
	if ( lhs.size_ != rhs.size_ )  return false;
	for ( typename DoublyLinkedList<U>::Node * p1 = lhs.front_, * p2 = rhs.front_;
		  p1 && p2;
	      p1 = p1->next, p2 = p2->next )
		if ( p1->value != p2->value )  return false;
	return true;
}


//-----------------------------------------------------------------------------


template class DoublyLinkedList<char>;
template class DoublyLinkedList<int16_t>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<string>;

template bool operator ==<char>(const DoublyLinkedList<char>& lhs, const DoublyLinkedList<char>& rhs);
template bool operator ==<int16_t>(const DoublyLinkedList<int16_t>& lhs, const DoublyLinkedList<int16_t>& rhs);
template bool operator ==<int>(const DoublyLinkedList<int>& lhs, const DoublyLinkedList<int>& rhs);
template bool operator ==<float>(const DoublyLinkedList<float>& lhs, const DoublyLinkedList<float>& rhs);
template bool operator ==<string>(const DoublyLinkedList<string>& lhs, const DoublyLinkedList<string>& rhs);
