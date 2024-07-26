#include <catch2/catch_test_macros.hpp>
#include <ax/packet_iterator.hpp>
#include <ranges>
#include <numeric>

struct get_size
{
    std::size_t operator()(std::span<const std::byte> buf) const
    {    
        return std::to_integer<std::size_t>(buf.front());
    }
};

TEST_CASE("is forward range")
{
    REQUIRE(std::ranges::forward_range<ax::packet_iterator<const std::byte, get_size>>);
}

TEST_CASE("default iterator")
{
    REQUIRE(std::ranges::distance(ax::packet_iterator<const std::byte, get_size>{}) == 0);
}

TEST_CASE("empty buffer")
{
    std::vector<int> const buffer{};
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };
    REQUIRE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 0);
}

TEST_CASE("complete packets")
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2, 0, 4, 0, 0, 0 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };

    SECTION("correct distance") 
    {
        REQUIRE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 3);
    }

    SECTION("correct span sizes") 
    {
        auto it{ ax::packet_iterator{buffer_as_bytes, get_size{}} };
        REQUIRE((*it).size() == 3);
        REQUIRE((*++it).size() == 2);
        REQUIRE((*++it).size() == 4);
    }
}

TEST_CASE("with lambda")
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2, 0, 4, 0, 0, 0 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };

    REQUIRE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, 
    [](std::span<const std::byte> buf)
    {
        return std::to_integer<std::size_t>(buf.front());
    }}) == 3);
}

TEST_CASE("incomplete packets 1")
{
    std::vector<std::uint8_t> const buffer{ 3, 0 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };
    REQUIRE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 0);
}

TEST_CASE("incomplete packets 2")
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };
    REQUIRE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 1);
    REQUIRE((*ax::packet_iterator{buffer_as_bytes, get_size{}}).size() == 3);
}