#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <ax/statistics.hpp>

TEST_CASE("mean - empty range")
{
    REQUIRE_THROWS_AS(ax::ranges::mean(std::vector<double>{}), std::invalid_argument);
}

TEST_CASE("mean - one element")
{
    std::vector<double> numbers{ 2.0 }; 
    REQUIRE_THAT(ax::ranges::mean(numbers), Catch::Matchers::WithinRel(2.0));
}

TEST_CASE("mean - one element float")
{
    std::vector<double> numbers{ 2.0 }; 
    REQUIRE_THAT(ax::ranges::mean<float>(numbers), Catch::Matchers::WithinRel(2.0f));
}

TEST_CASE("mean - three elements")
{
    std::vector<double> numbers{ 2.0, 2.5, 3.0 }; 
    REQUIRE_THAT(ax::ranges::mean(numbers), Catch::Matchers::WithinRel(2.5));
}

TEST_CASE("variance - empty range")
{
    REQUIRE_THROWS_AS(ax::ranges::variance(std::vector<double>{}), std::invalid_argument);
}

TEST_CASE("variance - one element")
{
    std::vector<double> numbers{ 2.0 }; 
    REQUIRE_THAT(ax::ranges::variance(numbers), Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("variance - one element float")
{
    std::vector<double> numbers{ 2.0 }; 
    REQUIRE_THAT(ax::ranges::variance<float>(numbers), Catch::Matchers::WithinRel(0.0f));
}

TEST_CASE("variance - more elements")
{
    std::vector<double> numbers{ 2, 3, 4, 6 };
    REQUIRE_THAT(ax::ranges::variance(numbers), Catch::Matchers::WithinRel(2.1875));
}

TEST_CASE("stdev - empty range")
{
    REQUIRE_THROWS_AS(ax::ranges::stdev(std::vector<double>{}), std::invalid_argument);
}

TEST_CASE("stdev - one element")
{
    std::vector<double> numbers{ 2.0 }; 
    REQUIRE_THAT(ax::ranges::stdev(numbers), Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("stdev - one element float")
{
    std::vector<double> numbers{ 2.0 }; 
    REQUIRE_THAT(ax::ranges::stdev<float>(numbers), Catch::Matchers::WithinRel(0.0f));
}

TEST_CASE("stdev - more elements")
{
    std::vector<double> numbers{ 2, 7 };
    REQUIRE_THAT(ax::ranges::stdev(numbers), Catch::Matchers::WithinRel(2.5));
}




