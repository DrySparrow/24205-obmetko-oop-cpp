#include "BitArray.cpp"
#include <iostream>

int main(void) 
{
	BitArray b;
	b.push_back(1);
	std::cout << b.to_string() << std::endl;
	b.push_back(0);
	std::cout << b.to_string() << std::endl;
	b.push_back(1);
	b.push_back(0);
	b.set(1);
	std::cout << b.to_string() << std::endl;

	return 0;
}