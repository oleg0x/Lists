#include "doubly_linked_list.h"
#include "list_iterator.h"
#include <iostream>
#include <string>
#include <cassert>

using std::cerr, std::string;



void TestCtors()
{
	{
		DoublyLinkedList<int16_t> l;
		l.Print();
		cerr << "Is empty: " << l.Empty() << ",  size = " << l.Size() << "\n";
		assert( l.Size() == 0 && l.Empty() );
	}

	{
		cerr << '\n';
		DoublyLinkedList<int> l1 {7, 2, 5, 8, 3};
		l1.Print();
		cerr << "Is empty: " << l1.Empty() << ",  size = " << l1.Size() << "\n";
		assert( l1.Size() == 5 && !l1.Empty() );
		
		DoublyLinkedList<int> l2(l1);
		cerr << "l1 is  ";
		l1.Print();
		cerr << "l2 is  ";
		l2.Print();
	}

	{
		cerr << '\n';
		DoublyLinkedList<int> l1(4, 10);
		l1.Print();
		cerr << "Is empty: " << l1.Empty() << ",  size = " << l1.Size() << "\n";
		assert( l1.Size() == 4 && !l1.Empty() );
		assert( l1 == (DoublyLinkedList<int> {10, 10, 10, 10}) );
		
		DoublyLinkedList<int> l2(std::move(l1));
		cerr << "l1 is  ";
		l1.Print();
		cerr << "l2 is  ";
		l2.Print();
		assert( l1.Size() == 0 && l1.Empty() );
		assert( l2.Size() == 4 && !l2.Empty() );
		assert( l2 == (DoublyLinkedList<int> {10, 10, 10, 10}) );
	}

	cerr << "---------- TestCtors is OK ----------\n\n";
}



void TestAssignments()
{
	{
		DoublyLinkedList<int> l1(3, 2);
		l1.Print();
		DoublyLinkedList<int> l2(6, 3);
		l2.Print();
		
		l1 = l2;
		l1.Print();
		l2.Print();
		assert( l1.Size() == 6 && !l1.Empty() );
		assert( l2.Size() == 6 && !l2.Empty() );
		assert( l1 == (DoublyLinkedList<int> {3, 3, 3, 3, 3, 3}) );
		
		l2 = l2;
		assert( l2.Size() == 6 && !l2.Empty() );
		assert( l2 == (DoublyLinkedList<int> {3, 3, 3, 3, 3, 3}) );
		
		DoublyLinkedList<int> l3 {4, 5, 6, 7};
		l1 = l3;
		l1.Print();
		l3.Print();
		assert( l1.Size() == 4 && !l1.Empty() );
		assert( l3.Size() == 4 && !l3.Empty() );
		assert( l1 == (DoublyLinkedList<int> {4, 5, 6, 7}) );
		
		l3 = l3;
		assert( l3.Size() == 4 && !l3.Empty() );
		assert( l3 == (DoublyLinkedList<int> {4, 5, 6, 7}) );
	}
	
	{
		cerr << '\n';
		DoublyLinkedList<int> l1(3, 2);
		l1.Print();
		DoublyLinkedList<int> l2(6, 3);
		l2.Print();
		
		l1 = std::move(l2);
		l1.Print();
		l2.Print();
		assert( l1.Size() == 6 && !l1.Empty() );
		assert( l2.Size() == 0 && l2.Empty() );
		assert( l1 == (DoublyLinkedList<int> {3, 3, 3, 3, 3, 3}) );
		
		l1 = DoublyLinkedList<int> {4, 5, 6, 7};
		l1.Print();
		assert( l1.Size() == 4 && !l1.Empty() );
		assert( l1 == (DoublyLinkedList<int> {4, 5, 6, 7}) );
		
		l1 = std::move(l1);
		l1.Print();
		assert( l1.Size() == 4 && !l1.Empty() );
		assert( l1 == (DoublyLinkedList<int> {4, 5, 6, 7}) );
	}

	cerr << "---------- TestAssignments is OK ----------\n\n";
}



void TestPush()
{
	{
		DoublyLinkedList<int> l;
		l.PushBack(1);
		l.PushBack(2);
		assert( l.Size() == 2 && l == (DoublyLinkedList<int> {1, 2}) );
		l.PushFront(-1);
		l.PushFront(-2);
		assert( l.Size() == 4 && l == (DoublyLinkedList<int> {-2, -1, 1, 2}) );
		l.PushBack(3);
		l.PushFront(-3);
		l.Print();
		DoublyLinkedList<int> sample {-3, -2, -1, 1, 2, 3};
		assert( l.Size() == 6 && l == sample );
	}
	
	{
		DoublyLinkedList<string> l;
		string str("ABC");
		cerr << "str = '" << str << "\'\n";
		l.PushFront(move(str));
		cerr << "str = '" << str << "\'\n";
		assert( str.empty() );
		assert( l.Size() == 1 && l == (DoublyLinkedList<string> {"ABC"}) );
		l.PushBack(string("XYZ"));
		l.Print();
		assert( l.Size() == 2 && l == (DoublyLinkedList<string> {"ABC", "XYZ"}) );
	}
	
	cerr << "---------- TestPush is OK ----------\n\n";
}



void TestPop()
{
	{
		DoublyLinkedList<int16_t> l {5, 8, 1, 3, 7};
		l.PopFront();  l.PopBack();
		l.Print();
		assert( l.Size() == 3 && l == (DoublyLinkedList<int16_t> {8, 1, 3}) );

		l.PopFront();  l.PopBack();
		assert( l.Size() == 1 && l == (DoublyLinkedList<int16_t> {1}) );
		l.PopFront();  
		assert( l.Size() == 0 && l == DoublyLinkedList<int16_t>() );
		l.PopFront();
		l.PopFront();
		assert( l.Size() == 0 && l == DoublyLinkedList<int16_t>() );
	
		l.PushBack(10);
		assert( l.Size() == 1 && l == (DoublyLinkedList<int16_t> {10}) );
		l.PopBack();
		l.PopBack();
		assert( l.Size() == 0 && l == DoublyLinkedList<int16_t>() );
	}
	
	cerr << "---------- TestPop is OK ----------\n\n";
}



void TestInsertBefore()
{
	{
		DoublyLinkedList<float> l;
		l.InsertBefore(nullptr, 5);
		l.InsertBefore(nullptr, 8);
		l.InsertBefore(l.Begin(), 6);
		l.InsertBefore(l.End(), 9);
		l.Print();
		assert( l.Size() == 4 && l == (DoublyLinkedList<float> {6, 5, 9, 8}) );
		
		l.InsertBefore(l.Next(l.Begin()), 200);
		l.InsertBefore(l.Begin(), 100);
		l.InsertBefore(l.Prev(l.End()), 300);
		l.InsertBefore(l.End(), 400);
		l.InsertBefore(nullptr, 500);
		l.Print();
		assert( l.Size() == 9 && 
			l == (DoublyLinkedList<float> {100, 6, 200, 5, 300, 9, 400, 8, 500}) );
	}
	
	cerr << "---------- TestInsertBefore is OK ----------\n\n";
}



void TestSwap()
{
	{
		DoublyLinkedList<int16_t> l {1};
		l.Print();
		l.Swap(l.Begin(), l.End());
		l.Print();
		assert( l.Size() == 1 && l == DoublyLinkedList<int16_t> {1} );
	
		l.PushBack(2);
		l.Print();
		l.Swap(l.Begin(), l.End());
		l.Print();
		assert( l.Size() == 2 && l == (DoublyLinkedList<int16_t> {2, 1}) );
		l.Swap(l.End(), l.Begin());
		l.Print();
		assert( l.Size() == 2 && l == (DoublyLinkedList<int16_t> {1, 2}) );
	
		l.PushBack(3);
		l.Print();
		l.Swap(l.Begin(), l.End());
		l.Print();
		assert( l.Size() == 3 && l == (DoublyLinkedList<int16_t> {3, 2, 1}) );
		l.Swap(l.End(), l.Begin());
		l.Print();
		assert( l.Size() == 3 && l == (DoublyLinkedList<int16_t> {1, 2, 3}) );
	
		l.PushBack(4);
		l.PushBack(5);
		l.PushBack(6);
		l.Print();
		l.Swap( l.Next(l.Begin()), l.Prev(l.End()) );
		l.Print();
		assert( l.Size() == 6 && l == (DoublyLinkedList<int16_t> {1, 5, 3, 4, 2, 6}) );
		l.Swap( l.Prev(l.End()), l.Next(l.Begin()) );
		l.Print();
		assert( l.Size() == 6 && l == (DoublyLinkedList<int16_t> {1, 2, 3, 4, 5, 6}) );
		l.Swap( l.Begin(), l.Prev(l.Prev(l.End())) );
		l.Print();
		assert( l.Size() == 6 && l == (DoublyLinkedList<int16_t> {4, 2, 3, 1, 5, 6}) );
		l.Swap( l.Prev(l.Prev(l.End())), l.Begin() );
		l.Print();
		assert( l.Size() == 6 && l == (DoublyLinkedList<int16_t> {1, 2, 3, 4, 5, 6}) );
		l.Swap( l.End(), l.Prev(l.End()) );
		l.Print();
		assert( l.Size() == 6 && l == (DoublyLinkedList<int16_t> {1, 2, 3, 4, 6, 5}) );
		l.Swap( l.Prev(l.End()), l.End() );
		l.Print();
		assert( l.Size() == 6 && l == (DoublyLinkedList<int16_t> {1, 2, 3, 4, 5, 6}) );
		l.Swap( l.Next(l.Next(l.Begin())), l.Prev(l.Prev(l.End())) );
		l.Print();
		assert( l.Size() == 6 && l == (DoublyLinkedList<int16_t> {1, 2, 4, 3, 5, 6}) );
	}
	
	cerr << "---------- TestSwap is OK ----------\n\n";
}



void TestBubbleSort()
{
	{
		DoublyLinkedList<int16_t> l;
		l.Print();
		l.BubbleSort();
		l.Print();
		assert( l.Size() == 0 && l == DoublyLinkedList<int16_t>() );
	}

	{
		DoublyLinkedList<int16_t> l {5};
		l.Print();
		l.BubbleSort();
		l.Print();
		assert( l.Size() == 1 && l == (DoublyLinkedList<int16_t> {5}) );
	}

	{
		DoublyLinkedList<int16_t> l {7, 5};
		l.Print();
		l.BubbleSort();
		l.Print();
		assert( l.Size() == 2 && l == (DoublyLinkedList<int16_t> {5, 7}) );
	}

	{
		DoublyLinkedList<int16_t> l {2, 5, 8};
		l.Print();
		l.BubbleSort();
		l.Print();
		assert( l.Size() == 3 && l == (DoublyLinkedList<int16_t> {2, 5, 8}) );
	}

	{
		DoublyLinkedList<int16_t> l {4, 6, 1, 3, 7, 5, 2};
		l.Print();
		l.BubbleSort();
		l.Print();
		assert( l.Size() == 7 && l == (DoublyLinkedList<int16_t> {1, 2, 3, 4, 5, 6, 7}) );
	}

	cerr << "---------- TestBubbleSort is OK ----------\n\n";
}



void TestErase()
{
	{
		DoublyLinkedList<int16_t> l {1, 2, 3, 4, 5, 6};
		l.Print();
	
		auto p = l.Begin();
		p = l.Next(p);  p = l.Next(p);
		l.Erase(p);  // Erase '3'
		l.Print();
		assert( l.Size() == 5 && l == (DoublyLinkedList<int16_t> {1, 2, 4, 5, 6}) );
	
		l.Erase(l.Begin());
		l.Erase(l.End());
		l.Print();
		assert( l.Size() == 3 && l == (DoublyLinkedList<int16_t> {2, 4, 5}) );
	
		p = l.Begin();  p = l.Next(p);
		l.Erase(p);  // Erase '4'
		l.Print();
		assert( l.Size() == 2 && l == (DoublyLinkedList<int16_t> {2, 5}) );
	
		l.Erase(l.Begin());
		l.Erase(l.End());
		l.Print();
		assert( l.Size() == 0 && l == (DoublyLinkedList<int16_t>()) );
	}
	
	{
		DoublyLinkedList<int16_t> l {5, 4, 3, 2, 1};
		l.Print();
		l.Clear();
		l.Print();
		assert( l.Size() == 0 && l == (DoublyLinkedList<int16_t>()) );
	}
	
	cerr << "---------- TestErase is OK ----------\n\n";
}



void TestIteration()
{
	{
		DoublyLinkedList<int16_t> l(8, 1);
		l.Print();
		cerr << --l.Front()  << ' ' << (l.Back() *= 10) << '\n';
		assert( l.Front() == 0 && l.Back() == 10 );
		for ( auto p = l.Begin(); p; p = l.Next(p) )
			cerr << ++(p->value) << ", ";
		cerr << '\n';
		for ( auto p = l.End(); p; p = l.Prev(p) )
			cerr << (p->value *= 10) << ", ";
		cerr << '\n';
	}
	
	cerr << "---------- TestIteration is OK ----------\n\n";
}



void TestIterator()
{
	{
		DoublyLinkedList<int> l(7, 3);
		l.Print();
		ListIterator<int> it(&l);
	
		for ( it.First(); !it.IsDone(); it.Next() )
		{
			it.Current() += 4;
			cerr << it.Current() << ", ";
		}
		cerr << '\n';
		assert( l.Size() == 7 && l == (DoublyLinkedList<int> {7, 7, 7, 7, 7, 7, 7}) );
	
		int k = 0;
		for ( it.First(); !it.IsDone(); ++it )
		{
			*it += ++k;
			cerr << *it << ", ";
		}
		cerr << '\n';
	
		for ( it.Last(); !it.IsDone(); --it )
		{
			*it *= 10;
			cerr << *it << ", ";
		}
		cerr << '\n';
	
		assert( l.Size() == 7 && 
			l == (DoublyLinkedList<int> {80, 90, 100, 110, 120, 130, 140}) );
		l.Print();
	}
	
	cerr << "---------- TestIterator is OK ----------\n\n";
}
