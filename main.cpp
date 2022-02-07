#include <iostream>

void TestCtors();
void TestAssignments();
void TestPush();
void TestPop();
void TestInsertBefore();
void TestErase();
void TestSwap();
void TestBubbleSort();
void TestIteration();
void TestIterator();



int main()
{
	std::cerr << std::boolalpha;
	
	TestCtors();
	TestAssignments();
	
	TestPush();
	TestPop();
		
	TestInsertBefore();
	TestErase();

	TestSwap();
	TestBubbleSort();

	TestIteration();
	TestIterator();
}
