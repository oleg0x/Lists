#include <iostream>

void TestCtors();
void TestAssignments();
void TestPush();
void TestPop();
void TestInsertBefore();
void TestSwap();
void TestErase();
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
	TestSwap();
	
	TestErase();
	
	TestIteration();
	TestIterator();
}
