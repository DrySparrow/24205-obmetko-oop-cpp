#include <gtest/gtest.h>
#include "../src/GameOfLifeEngine.cpp"

TEST(RuleTest, DefaultConstructor) {
    GameOfLifeEngine engine = GameOfLifeEngine();
	engine.getDefaultRule();

    EXPECT_EQ(engine.getStringRule(), "B3/S23");
}

TEST(RuleTest, toString) {
	GameOfLifeEngine engine = GameOfLifeEngine();
	engine.setRule("B234/S15");
	
	EXPECT_EQ(engine.getStringRule(), "B234/S15");
}
