#include <gtest/gtest.h>
#include "main.cpp"  

TEST(MyProjectTest, MinMaxTest) {
    int array[] = { 1, 2, 3, 4, 5 };
    int size = 5;
    int max, min;
    double avg;
    MyData data{ array, size, &max, &min, &avg };

    min_max(&data);
    EXPECT_EQ(max, 5);
    EXPECT_EQ(min, 1);
}

TEST(MyProjectTest, AverageTest) {
    int array[] = { 1, 2, 3, 4, 5 };
    int size = 5;
    int max, min;
    double avg;
    MyData data{ array, size, &max, &min, &avg };

    average(&data);
    EXPECT_DOUBLE_EQ(avg, 3.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
