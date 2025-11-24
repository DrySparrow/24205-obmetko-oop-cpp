#include "BitArray.h"
#include <algorithm>
#include <stdexcept>

// Constructors
BitArray::BitArray() : bit_count(0) {}

BitArray::BitArray(int num_bits) : bit_count(0) {
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }
    bit_count = static_cast<size_t>(num_bits);
    size_t byte_count = (bit_count + 7) / 8;
    data.resize(byte_count, 0);
}

BitArray::BitArray(int num_bits, bool value) : bit_count(0) {
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }
    bit_count = static_cast<size_t>(num_bits);
    size_t byte_count = (bit_count + 7) / 8;
    data.resize(byte_count, 0);
    
    if (value) {
        for (size_t i = 0; i < bit_count; ++i) {
            set(i, value);
        }
    }
}

BitArray::BitArray(const BitArray& b) : data(b.data), bit_count(b.bit_count) {}

// Methods
void BitArray::swap(BitArray& other) {
    std::swap(data, other.data);
    std::swap(bit_count, other.bit_count);
}

BitArray& BitArray::operator=(const BitArray& other) {
    if (this != &other) {
        data = other.data;
        bit_count = other.bit_count;
    }
    return *this;
}

void BitArray::resize(size_t new_size, bool value) {
    if (new_size < bit_count) {
        bit_count = new_size;
        size_t byte_count = (new_size + 7) / 8;
        data.resize(byte_count);
    } else if (new_size > bit_count) {
        size_t old_size = bit_count;
        bit_count = new_size;
        size_t byte_count = (new_size + 7) / 8;
        data.resize(byte_count, 0);
        
        for (size_t i = old_size; i < new_size; ++i) {
            set(i, value);
        }
    }
}

void BitArray::clear() {
    data.clear();
    bit_count = 0;
}

void BitArray::push_back(bool bit) {
	resize(bit_count + 1, bit);
}

// Bitwise operations
BitArray& BitArray::operator&=(const BitArray& b) {
    size_t min_size = std::min(bit_count, b.bit_count);
    for (size_t i = 0; i < min_size; ++i) {
        set(i, (*this)[i] && b[i]);
    }
    for (size_t i = min_size; i < bit_count; ++i) {
        set(i, false);
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    size_t min_size = std::min(bit_count, b.bit_count);
    for (size_t i = 0; i < min_size; ++i) {
        set(i, (*this)[i] || b[i]);
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    size_t min_size = std::min(bit_count, b.bit_count);
    for (size_t i = 0; i < min_size; ++i) {
        set(i, (*this)[i] != b[i]);
    }
    return *this;
}

// Shifts
BitArray& BitArray::operator<<=(int n) {
    if (n <= 0) {
        if (n < 0) return *this >>= -n;
        return *this;
    }
    
    if (n >= static_cast<int>(bit_count)) {
        reset();
        return *this;
    }
    
    for (size_t i = 0; i < bit_count - n; ++i) {
        set(i, (*this)[i+n]);
    }
    for (size_t i = bit_count - n; i < bit_count; ++i) {
        set(i, false);
    }
    
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n <= 0) {
        if (n < 0) return *this <<= -n;
        return *this;
    }
    
    if (n >= static_cast<int>(bit_count)) {
        reset();
        return *this;
    }
    
    for (size_t i = bit_count - 1; i >= n; --i) {
        set(i, (*this)[i-n]);
    }
    for (size_t i = 0; i < n; ++i) {
        set(i, false);
    }
    
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray result = *this;
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result = *this;
    result >>= n;
    return result;
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || static_cast<size_t>(n) >= bit_count) {
        throw std::out_of_range("Bit index out of range");
    }
    
    size_t byte_index = static_cast<size_t>(n) / 8;
    size_t bit_offset = static_cast<size_t>(n) % 8;
    uint8_t mask = 1 << bit_offset;
    
    if (val) {
        data[byte_index] |= mask;
    } else {
        data[byte_index] &= ~mask;
    }
    
    return *this;
}

BitArray& BitArray::set() {
    for (size_t i = 0; i < bit_count; ++i) {
        set(i, true);
    }
    return *this;
}

BitArray& BitArray::reset(int n) {
    return set(n, false);
}

BitArray& BitArray::reset() {
    for (auto& byte : data) {
        byte = 0;
    }
    return *this;
}

bool BitArray::any() const {
    for (size_t i = 0; i < bit_count; ++i) {
        if ((*this)[i]) return true;
    }
    return false;
}

bool BitArray::none() const {
    for (size_t i = 0; i < bit_count; ++i) {
        if ((*this)[i]) return false;
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (size_t i = 0; i < result.data.size(); ++i) {
        result.data[i] = ~result.data[i];
    }
    if (bit_count % 8 != 0) {
        size_t last_byte = result.data.size() - 1;
        uint8_t mask = (1 << (bit_count % 8)) - 1;
        result.data[last_byte] &= mask;
    }
    return result;
}

int BitArray::count() const {
    int result = 0;
    for (size_t i = 0; i < bit_count; ++i) {
        result += (*this)[i];
    }
    return result;
}

bool BitArray::operator[](int index) const {
    if (index >= static_cast<int>(bit_count) || index < 0) {
        throw std::out_of_range("Bit index out of range");
    }

    size_t byte_index = index / 8;
    size_t bit_offset = index % 8;
    uint8_t mask = 1 << bit_offset;
    
    return (data[byte_index] & mask) != 0;
}

int BitArray::size() const {
    return bit_count;
}

bool BitArray::empty() const {
    return bit_count == 0;
}

std::string BitArray::to_string() const {
    std::string result;
    result.reserve(bit_count);
    
    for (size_t i = 0; i < bit_count; ++i) {
        result += (*this)[i] ? '1' : '0';
    }
    
    return result;
}

// Global Operator Implementations
bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()) return false;
    
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool operator!=(const BitArray & a, const BitArray & b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray array = b1;
    array &= b2;
    return array;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray array = b1;
    array |= b2;
    return array;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray array = b1;
    array ^= b2;
    return array;
}