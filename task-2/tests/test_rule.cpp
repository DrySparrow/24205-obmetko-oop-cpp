#include <gtest/gtest.h>
#include "rule.h"
#include <iostream>

TEST(RuleTest, DefaultConstructor) {
    Rule rule = Rule::getDefaultRule();

    EXPECT_EQ(rule.toString(), "B3/S23");
}

TEST(RuleTest, toString) {
	Rule rule = Rule::parseRuleString("B234/S15");
	
	EXPECT_EQ(rule.toString(), "B234/S15");
}
