#include "BitArray.cpp"
#include <iostream>

int main(void) 
{
	BitArray b(5);
	b.set(1);
	b[2] = true;

	std::cout << b.to_string();

	return 0;
}