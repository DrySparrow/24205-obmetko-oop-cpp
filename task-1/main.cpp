#include "BitArray.cpp"
#include <iostream>

BitArray createArray() {
    BitArray temp(5);
    return temp;       // может вызывать конструктор копирования (зависит от оптимизации)
}

int main(void) 
{
	BitArray a;
	BitArray b = a;
	BitArray c;
	c = a;

	

	return 0;
}