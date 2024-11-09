#include <gtest/gtest.h>
#include <ax/statistics.hpp>

TEST(Mean, EmptyRange)
{
    ASSERT_THROW(auto result{ ax::ranges::mean(std::vector<double>{}) }, std::invalid_argument);
}

TEST(Mean, OneElement)
{
    std::vector<double> numbers{ 2.0 }; 
    ASSERT_DOUBLE_EQ(ax::ranges::mean(numbers), 2.0);
}

TEST(Mean, OneElementFloat)
{
    std::vector<float> numbers{ 2.0 }; 
    ASSERT_FLOAT_EQ(ax::ranges::mean<float>(numbers), 2.0f);
}

TEST(Mean, ThreeElements)
{
    std::vector<double> numbers{ 2.0, 2.5, 3.0 }; 
    ASSERT_DOUBLE_EQ(ax::ranges::mean(numbers), 2.5);
}

TEST(Variance, EmptyRange)
{
    ASSERT_THROW(auto result{ ax::ranges::variance(std::vector<double>{}) }, std::invalid_argument);
}

TEST(Variance, OneElement)
{
    std::vector<double> numbers{ 2.0 }; 
    ASSERT_DOUBLE_EQ(ax::ranges::variance(numbers), 0.0);
}

TEST(Variance, OneElementFloat)
{
    std::vector<float> numbers{ 2.0 }; 
    ASSERT_FLOAT_EQ(ax::ranges::variance<float>(numbers), 0.0f);
}

TEST(Variance, MoreElements)
{
    std::vector<double> numbers{ 2, 3, 4, 6 };
    ASSERT_DOUBLE_EQ(ax::ranges::variance(numbers), 2.1875);
}

TEST(Stdev, EmptyRange)
{
    ASSERT_THROW(auto result{ ax::ranges::stdev(std::vector<double>{}) }, std::invalid_argument);
}

TEST(Stdev, OneElement)
{
    std::vector<double> numbers{ 2.0 }; 
    ASSERT_DOUBLE_EQ(ax::ranges::stdev(numbers), 0.0);
}

TEST(Stdev, OneElementFloat)
{
    std::vector<float> numbers{ 2.0 }; 
    ASSERT_FLOAT_EQ(ax::ranges::stdev<float>(numbers), 0.0f);
}

TEST(Stdev, MoreElements)
{
    std::vector<double> numbers{ 2, 7 };
    ASSERT_DOUBLE_EQ(ax::ranges::stdev(numbers), 2.5);
}