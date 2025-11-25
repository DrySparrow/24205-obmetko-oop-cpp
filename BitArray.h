#ifndef BITARRAY_H
#define BITARRAY_H

#include <cstdint>
#include <string>
#include <vector>

class BitArray
{
private:
    std::vector<uint8_t> data;
    size_t bit_count;
    
public:
    BitArray();
    ~BitArray() = default;
    explicit BitArray(int num_bits);
    explicit BitArray(int num_bits, bool value);
    BitArray(const BitArray& b);
    
    // exchange all values ​​of two arrays
    void swap(BitArray& other);
    BitArray& operator=(const BitArray& other);
    
    // changes the size by adding or removing low-order bits
    void resize(size_t new_size, bool value = false);
    // clear all bits
    void clear();
    // add least significant bit
    void push_back(bool bit);
    
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);
    
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;
    
    // set the value of the n-th bit at index
    BitArray& set(int n, bool val = true);
    // set all bits to true
    BitArray& set();
    // set the value of the n-th bit to false
    BitArray& reset(int n);
    // set all bits to false
    BitArray& reset();
    
    bool any() const;
    bool none() const;
    BitArray operator~() const;
    int count() const;
    
    bool operator[](int index) const;
    int size() const;
    bool empty() const;
    std::string to_string() const;
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);
BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif