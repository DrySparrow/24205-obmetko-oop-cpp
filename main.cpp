#include "BitArray.cpp"

int main(void) 
{
	BitArray b(10, 1);
	b >>= 2;
	b.set(3, 0);
	std::cout << b.to_string() << std::endl;
	b = ~b;
	std::cout << b.to_string() << std::endl;

	return 0;
}