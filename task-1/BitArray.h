#ifndef BITARRAY_H
#define BITARRAY_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>

class BitArray {
private:
    std::vector<uint8_t> data;
    size_t bit_count;

public:
    class BitProxy {
    private:
        uint8_t& byte;
        uint8_t mask;

    public:
        BitProxy(uint8_t& data_byte, size_t bit_pos)
            : byte(data_byte), mask(1 << bit_pos) {}

        BitProxy& operator=(bool value) {
            if (value) {
                byte |= mask;
            } else {
                byte &= ~mask;
            }
            return *this;
        }

        BitProxy& operator=(const BitProxy& other) {
            if (this != &other) {
                *this = static_cast<bool>(other);
            }
            return *this;
        }

        operator bool() const {
            return (byte & mask) != 0;
        }
    };

    BitArray();
    BitArray(int num_bits);
    BitArray(int num_bits, bool value);
    BitArray(const BitArray& b);
    
    BitArray& operator=(const BitArray& other);
    
    BitProxy operator[](size_t index);
    bool operator[](size_t index) const;
    
    int size() const;
    bool empty() const;
    void resize(size_t new_size, bool value = false);
    void clear();
    void push_back(bool bit);
    
    void swap(BitArray& other);
    BitArray& set(int n, bool val = true);
    BitArray& set();
    BitArray& reset(int n);
    BitArray& reset();
    bool any() const;
    bool none() const;
    int count() const;
    
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);
    BitArray operator~() const;
    
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;
    
    std::string to_string() const;
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);
BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif