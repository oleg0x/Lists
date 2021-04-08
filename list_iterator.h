#pragma once

#include "doubly_linked_list.h"
#include <iostream>



template <typename T> class ListIterator
{
public:
	ListIterator(const DoublyLinkedList<T>* list);
	void First();
	void Last();
	void Prev();
	void Next();
	bool IsDone() const;
	T& Current() const;
	T& operator *() const;
	ListIterator& operator --();  // Prefix version
	ListIterator& operator ++();  // Prefix version
	
private:
	const DoublyLinkedList<T>* list_;
	DoublyLinkedList<T>::Node* current_;
};



template <typename T> 
ListIterator<T>::ListIterator(const DoublyLinkedList<T>* list)
	: list_ {list}, current_ {list->front_}
{}



template <typename T> 
void ListIterator<T>::First()
{
	if ( list_ )  current_ = list_->front_;
}



template <typename T> 
void ListIterator<T>::Last()
{
	if ( list_ )  current_ = list_->back_;
}



template <typename T> 
void ListIterator<T>::Prev()
{
	if ( current_ )  current_->prev;
}



template <typename T> 
void ListIterator<T>::Next()
{
	if ( current_ )  current_ = current_->next;
}



template <typename T> 
bool ListIterator<T>::IsDone() const
{
	return !current_;
}



template <typename T> 
T& ListIterator<T>::Current() const
{
	return current_->value;
}



template <typename T> 
T& ListIterator<T>::operator*() const
{
	return current_->value;
}



template <typename T> 
ListIterator<T>& ListIterator<T>::operator--()
{
	if ( current_ )  current_ = current_->prev;
	return *this;
}



template <typename T> 
ListIterator<T>& ListIterator<T>::operator++()
{
	if ( current_ )  current_ = current_->next;
	return *this;
}
