#pragma once

#include <cstdint>
#include <initializer_list>

using CountType = uint32_t;

template <typename T> class ListIterator;



template <typename T> class DoublyLinkedList
{
public:
	struct Node
	{
		T value;
		Node* prev = nullptr;
		Node* next = nullptr;
	};
	
	DoublyLinkedList() = default;       // Default constructor
	explicit DoublyLinkedList(CountType count, const T& value = T());
	DoublyLinkedList(std::initializer_list<T> init);
	DoublyLinkedList(const DoublyLinkedList& other);  // Copy constructor
	DoublyLinkedList(DoublyLinkedList&&  other);      // Move constructor

	~DoublyLinkedList();

	DoublyLinkedList<T>& operator =(const DoublyLinkedList& other);  // Copy assignment
	DoublyLinkedList<T>& operator =(DoublyLinkedList&& other);       // Move assignment
	
	bool Empty() const;
	CountType Size() const;
	
	T& Front();  // Access the first element 
	T& Back();   // Access the last element 
	const T& Front() const;
	const T& Back() const;
	
	Node* Begin() const;
	Node* End() const;
	
	Node* Next(const Node* node) const;
	Node* Prev(const Node* node) const;

	void PushBack(const T& value);
	void PushBack(T&& value);
	void PushFront(const T& value);
	void PushFront(T&& value);

	void PopBack();   // Removes the last element 
	void PopFront();  // Removes the first element 
	
	void InsertBefore(Node* node, const T& value);
	void Swap(Node* n1, Node* n2);
	
	void Erase(Node* node);
	void Clear();
		
	void Print() const;

private:
	Node* front_ = nullptr;
	Node* back_ = nullptr;
	CountType size_ = 0;
	
	void PushBackCommon(Node* node);
	void PushFrontCommon(Node* node);
	
	template <typename U>
	friend bool operator ==(const DoublyLinkedList<U>& lhs, const DoublyLinkedList<U>& rhs);
	
	friend class ListIterator<T>;
};



template <typename U>
bool operator ==(const DoublyLinkedList<U>& lhs, const DoublyLinkedList<U>& rhs);
