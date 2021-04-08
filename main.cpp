#include <iostream>

using std::cout, std::cerr, std::string;

void TestCtors();
void TestAssignments();
void TestPush();
void TestMove();
void TestPop();
void TestInsertBefore();
void TestSwap();
void TestErase();
void TestIteration();
void TestIterator();



int main()
{
	cerr << std::boolalpha;
	
	TestCtors();
	TestAssignments();
	
	TestPush();
	TestMove();
	TestPop();
		
	TestInsertBefore();
	TestSwap();
	
	TestErase();
	
	TestIteration();
	TestIterator();
}
