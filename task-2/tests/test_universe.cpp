#include <gtest/gtest.h>
#include "../include/Universe.h"

// TEST(UniverseTest, DefaultConstructor) {
//     Universe u;
//     EXPECT_EQ(u.getGeneration(), 0);
//     EXPECT_EQ(u.getName(), "Universe");
// }

// TEST(UniverseTest, SetAndGetCell) {
//     Universe u(10, 10);
//     u.setCell(5, 5, true);
//     EXPECT_TRUE(u.getCell(5, 5));
//     EXPECT_FALSE(u.getCell(0, 0));
// }

// TEST(UniverseTest, ToroidalWrapping) {
//     Universe u(3, 3);
//     u.setCell(0, 0, true);
//     u.setCell(2, 2, true);
    
//     // Проверяем, что крайние клетки считаются соседями
//     // В торическом поле клетка (0,0) соседствует с (2,2)
//     u.nextGeneration();
//     // Добавьте проверки в зависимости от правил
// }

// TEST(UniverseTest, Clear) {
//     Universe u(5, 5);
//     u.setCell(2, 2, true);
//     u.clear();
//     EXPECT_FALSE(u.getCell(2, 2));
//     EXPECT_EQ(u.getGeneration(), 0);
// }