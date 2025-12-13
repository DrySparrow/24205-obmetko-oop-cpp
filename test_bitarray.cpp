#include <gtest/gtest.h>
#include "BitArray.h"

// Testing constructors
TEST(BitArrayTest, DefaultConstructor) {
    BitArray ba;
    EXPECT_TRUE(ba.empty());
    EXPECT_EQ(ba.size(), 0);
}

TEST(BitArrayTest, ConstructorWithSize) {
    BitArray ba(10);
    EXPECT_FALSE(ba.empty());
    EXPECT_EQ(ba.size(), 10);
    // All bits should be false by default
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(ba[i]);
    }
}

TEST(BitArrayTest, ConstructorWithSizeAndValue) {
    BitArray ba(5, true);
    EXPECT_EQ(ba.size(), 5);
    // All bits should be true
    for (int i = 0; i < 5; ++i) {
        EXPECT_TRUE(ba[i]);
    }
}

TEST(BitArrayTest, NegativeSizeThrowsException) {
    EXPECT_THROW(BitArray(-5), std::invalid_argument);
}

// Testing operator[]
TEST(BitArrayTest, IndexOperator) {
    BitArray ba(3);
    ba.set(1, true); // set the second bit
    
    EXPECT_FALSE(ba[0]);
    EXPECT_TRUE(ba[1]);
    EXPECT_FALSE(ba[2]);
}

TEST(BitArrayTest, IndexOperatorOutOfRange) {
    BitArray ba(3);
    EXPECT_THROW(ba[5], std::out_of_range);
    EXPECT_THROW(ba[-1], std::out_of_range);
}

// Testing set/reset
TEST(BitArrayTest, SetSingleBit) {
    BitArray ba(5);
    ba.set(2);
    EXPECT_TRUE(ba[2]);
    EXPECT_FALSE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_FALSE(ba[3]);
    EXPECT_FALSE(ba[4]);
}

TEST(BitArrayTest, ResetSingleBit) {
    BitArray ba(3, true); // all bits are true
    ba.reset(1);
    EXPECT_TRUE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_TRUE(ba[2]);
}

TEST(BitArrayTest, SetAllBits) {
    BitArray ba(4);
    ba.set();
    for (int i = 0; i < 4; ++i) {
        EXPECT_TRUE(ba[i]);
    }
}

TEST(BitArrayTest, ResetAllBits) {
    BitArray ba(4, true);
    ba.reset();
    for (int i = 0; i < 4; ++i) {
        EXPECT_FALSE(ba[i]);
    }
}

// Testing bitwise operations
TEST(BitArrayTest, BitwiseAND) {
    BitArray ba1(4);
    BitArray ba2(4);
    
    ba1.set(0); ba1.set(1); // 1100
    ba2.set(1); ba2.set(2); // 0110
    
    BitArray result = ba1 & ba2;
    
    EXPECT_FALSE(result[0]);
    EXPECT_TRUE(result[1]);
    EXPECT_FALSE(result[2]);
    EXPECT_FALSE(result[3]);
}

TEST(BitArrayTest, BitwiseOR) {
    BitArray ba1(4);
    BitArray ba2(4);
    
    ba1.set(0); ba1.set(1); // 1100
    ba2.set(1); ba2.set(2); // 0110
    
    BitArray result = ba1 | ba2;
    
    EXPECT_TRUE(result[0]);
    EXPECT_TRUE(result[1]);
    EXPECT_TRUE(result[2]);
    EXPECT_FALSE(result[3]);
}

// Testing shifts
TEST(BitArrayTest, LeftShift) {
    BitArray ba(4);
    ba.set(1); // 0100
    ba <<= 1;  // 1000
    
    EXPECT_TRUE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_FALSE(ba[2]);
    EXPECT_FALSE(ba[3]);
}

TEST(BitArrayTest, RightShift) {
    BitArray ba(4);
    ba.set(2); // 0010
    ba >>= 1;  // 0001
    
    EXPECT_FALSE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_FALSE(ba[2]);
    EXPECT_TRUE(ba[3]);
}

// Testing any/none/count
TEST(BitArrayTest, AnyNoneCount) {
    BitArray ba(4);
    
    EXPECT_TRUE(ba.none());
    EXPECT_FALSE(ba.any());
    EXPECT_EQ(ba.count(), 0);
    
    ba.set(2);
    
    EXPECT_FALSE(ba.none());
    EXPECT_TRUE(ba.any());
    EXPECT_EQ(ba.count(), 1);
}

// Testing to_string
TEST(BitArrayTest, ToString) {
    BitArray ba(4);
    ba.set(0);
    ba.set(2);
    
    EXPECT_EQ(ba.to_string(), "1010");
}

// Testing push_back
TEST(BitArrayTest, PushBack) {
    BitArray ba;
    ba.push_back(true);
    ba.push_back(false);
    ba.push_back(true);
    
    EXPECT_EQ(ba.size(), 3);
    EXPECT_TRUE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_TRUE(ba[2]);
}

// Testing resize
TEST(BitArrayTest, Resize) {
    BitArray ba(3, true);
    ba.resize(5, false);
    
    EXPECT_EQ(ba.size(), 5);
    EXPECT_TRUE(ba[0]);
    EXPECT_TRUE(ba[1]);
    EXPECT_TRUE(ba[2]);
    EXPECT_FALSE(ba[3]);
    EXPECT_FALSE(ba[4]);
    
    ba.resize(2);
    EXPECT_EQ(ba.size(), 2);
    EXPECT_TRUE(ba[0]);
    EXPECT_TRUE(ba[1]);
}

// Testing copying and assignment
TEST(BitArrayTest, CopyConstructor) {
    BitArray original(3);
    original.set(1);
    
    BitArray copy(original);
    
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_FALSE(copy[0]);
    EXPECT_TRUE(copy[1]);
    EXPECT_FALSE(copy[2]);
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray original(3);
    original.set(1);
    
    BitArray assigned;
    assigned = original;
    
    EXPECT_EQ(assigned.size(), original.size());
    EXPECT_FALSE(assigned[0]);
    EXPECT_TRUE(assigned[1]);
    EXPECT_FALSE(assigned[2]);
}

TEST(BitArrayTest, ChangeIndex) {
    BitArray array(3);
    array[0] = true;

    EXPECT_TRUE(array[0]);
    EXPECT_FALSE(array[2]);
    EXPECT_FALSE(array[2]);
}