#include <gtest/gtest.h>
#include <iostream>

TEST(SimpleTest, BasicAssertion) {
    EXPECT_EQ(2 + 2, 4);
}
