#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

//В этой задаче для простоты не требуется делать контейнер шаблонным,
//но это вполне допускается по желанию студента.
class BitArray
{
private:
	std::vector<uint8_t> data;	// биты, хранящиеся в байтах
	size_t bit_count;			// количество бит
public:
	BitArray() : bit_count(0) {}
	
	//Конструирует массив, хранящий заданное количество бит.
	//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
	explicit BitArray(int num_bits) : bit_count(0) {
		if (num_bits < 0) {
			throw std::invalid_argument("Number of bits cannot be negative");
		}
		bit_count = static_cast<size_t>(num_bits);
		size_t byte_count = (bit_count + 7) / 8;
		data.resize(byte_count, 0);
	}
	
	
	explicit BitArray(int num_bits, bool value = false) : bit_count(0) {
		if (num_bits < 0) {
			throw std::invalid_argument("Number of bits cannot be negative");
		}
		bit_count = static_cast<size_t>(num_bits);
		size_t byte_count = (bit_count + 7) / 8;
		data.resize(byte_count, 0);  // сначала заполняем нулями
		
		// потом устанавливаем все биты в нужное значение
		if (value) {
			for (size_t i = 0; i < bit_count; ++i) {
				set(i, value);
			}
		}
	}
	// конструктор копирования
	BitArray(const BitArray& b) : data(b.data), bit_count(b.bit_count) {}

	//Обменивает значения двух битовых массивов.
	void swap(BitArray& other) {
		std::swap(data, other.data);
		std::swap(bit_count, other.bit_count);
	}

	BitArray& operator=(const BitArray& other) {
		if (this != &other) {
			data = other.data;
			bit_count = other.bit_count;
		}
		return *this;
	}


	//Изменяет размер массива. В случае расширения, новые элементы 
	//инициализируются значением value.
	void resize(size_t new_size, bool value = false) {
		if (new_size < bit_count) {
			bit_count = new_size;
			size_t byte_count = (new_size + 7) / 8;
			data.resize(byte_count);
		} else if (new_size > bit_count) {
			size_t old_size = bit_count;
			bit_count = new_size;
			size_t byte_count = (new_size + 7) / 8;
			data.resize(byte_count, 0);
			
			// заполняем новые биты
			for (size_t i = old_size; i < new_size; ++i) {
				set(i, value);
			}
		}
	}
	//Очищает массив.
	void clear() {
		data.clear();
		bit_count = 0;
	}

	//Добавляет новый бит в конец массива. В случае необходимости 
	//происходит перераспределение памяти.
	void push_back(bool bit) {
		// если все 8 бит заполнены, то выделяем ещё байт
		size_t new_bit_count = bit_count + 1;
		size_t byte_count = (new_bit_count + 7) / 8;

		if (byte_count > data.size()) {
			data.resize(byte_count, 0);
		}

		set(bit_count, bit);
		bit_count = new_bit_count;
	}


	//Битовые операции над массивами.
	//Работают только на массивах одинакового размера.
	//Обоснование реакции на параметр неверного размера входит в задачу.
	BitArray& operator&=(const BitArray& b) {
		size_t min_size = std::min(bit_count, b.bit_count);
		for (size_t i = 0; i < min_size; ++i) {
			set(i, (*this)[i] && b[i]);
		}
		// Обнуляем оставшиеся биты, если текущий массив длиннее
		for (size_t i = min_size; i < bit_count; ++i) {
			set(i, false);
		}
		return *this;
	}
	BitArray& operator|=(const BitArray& b) {
        size_t min_size = std::min(bit_count, b.bit_count);
        for (size_t i = 0; i < min_size; ++i) {
            set(i, (*this)[i] || b[i]);
        }
        return *this;
    }
	BitArray& operator^=(const BitArray& b) {
        size_t min_size = std::min(bit_count, b.bit_count);
        for (size_t i = 0; i < min_size; ++i) {
            set(i, (*this)[i] != b[i]);
        }
        return *this;
    }
 
	//Битовый сдвиг с заполнением нулями.
	BitArray& operator<<=(int n) {
        if (n <= 0) {
            if (n < 0) return *this >>= -n;
            return *this;
        }
        
        if (n >= static_cast<int>(bit_count)) {
            // Все биты сдвигаются за пределы
            reset();
            return *this;
        }
        
        // Сдвигаем биты
        for (size_t i = 0; i < bit_count - n; ++i) {
            set(i, (*this)[i+n]);
        }
        // Заполняем нулями освободившиеся биты
        for (size_t i = bit_count - n; i < bit_count; ++i) {
            set(i, false);
        }
        
        return *this;
    }
	BitArray& operator>>=(int n) {
        if (n <= 0) {
            if (n < 0) return *this <<= -n;
            return *this;
        }
        
        if (n >= static_cast<int>(bit_count)) {
            // Все биты сдвигаются за пределы
            reset();
            return *this;
        }
        
        // Сдвигаем биты
        for (size_t i = bit_count - 1; i >= n; --i) {
            set(i, (*this)[i-n]);
        }
        // Заполняем нулями освободившиеся биты
        for (size_t i = 0; i < n; ++i) {
            set(i, false);
        }
        
        return *this;
    }
	BitArray operator<<(int n) const {
        BitArray result = *this;
        result <<= n;
        return result;
    }
	BitArray operator>>(int n) const {
        BitArray result = *this;
        result >>= n;
        return result;
    }


	//Устанавливает бит с индексом n в значение val.
	BitArray& set(int n, bool val = true) {
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
	//Заполняет массив истиной.
	BitArray& set() {
        // Устанавливаем все биты в 1
        for (size_t i = 0; i < bit_count; ++i) {
            set(i, true);
        }
        return *this;
    }

  //Устанавливает бит с индексом n в значение false.
	BitArray& reset(int n) {
        return set(n, false);
    }
	//Заполняет массив ложью.
	BitArray& reset() {
        // Устанавливаем все биты в 0
        for (auto& byte : data) {
            byte = 0;
        }
        return *this;
    }

	//true, если массив содержит истинный бит.
	bool any() const {
		for (size_t i = 0; i < bit_count; ++i) {
			if ((*this)[i]) return true;
		}
		return false;
	}
  	//true, если все биты массива ложны.
	bool none() const {
		for (size_t i = 0; i < bit_count; ++i) {
			if (data[i] != 0) return false;		// проверяем байты
		}
		return true;
	}
	//Битовая инверсия
	BitArray operator~() const {
        BitArray result(*this);
        for (size_t i = 0; i < result.data.size(); ++i) {
            result.data[i] = ~result.data[i];
        }
        // Корректируем последний байт, если битов не кратно 8
        if (bit_count % 8 != 0) {
            size_t last_byte = result.data.size() - 1;
            uint8_t mask = (1 << (bit_count % 8)) - 1;
            result.data[last_byte] &= mask;
        }
        return result;
    }
	//Подсчитывает количество единичных бит.
	int count() const {
		int result = 0;
		for (size_t i = 0; i < bit_count; ++i) {
			result += (*this)[i];
		}
		return result;
	}


	//Возвращает значение бита по индексу i.
	bool operator[](int index) const {
		if (index >= bit_count || index < 0) {
			throw std::out_of_range("Bit index out of range");
		}

		// т.к. храним число, то чтобы получить индекс, нужна маска
		size_t byte_index = index / 8;
		size_t bit_offset = index % 8;
		uint8_t mask = 1 << bit_offset;
		
		return (data[byte_index] & mask) != 0;
	}

	int size() const {
		return bit_count;
	}

	bool empty() const {
		return bit_count == 0;
	}
  
  //Возвращает строковое представление массива.
  std::string to_string() const {
        std::string result;
        result.reserve(bit_count); // Резервируем память для эффективности
        
        for (size_t i = 0; i < bit_count; ++i) {
            result += (*this)[i] ? '1' : '0';
        }
        
        return result;
    }
};

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
