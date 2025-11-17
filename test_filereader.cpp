#include <gtest/gtest.h>
#include <iostream>

TEST(SimpleTest, BasicAssertion) {
    //std::cout << "TEST COMPLETED!" << std::endl;
    EXPECT_EQ(2 + 2, 4);
}
