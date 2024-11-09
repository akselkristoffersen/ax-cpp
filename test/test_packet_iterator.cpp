#include <gtest/gtest.h>
#include <ax/packet_iterator.hpp>
#include <ranges>
#include <numeric>

struct get_size
{
    std::size_t operator()(std::span<const std::byte> buf) const
    {   
        return buf.empty() ? 0 : std::to_integer<std::size_t>(buf.front());
    }
};

TEST(TestPacketIterator, IsForwardIterator) 
{
    ASSERT_TRUE((std::forward_iterator<ax::packet_iterator<const std::byte, get_size>>));
}

TEST(TestPacketIterator, IsForwardRange)
{
    ASSERT_TRUE((std::ranges::forward_range<ax::packet_iterator<const std::byte, get_size>>));
}

TEST(TestPacketIterator, DefaultIterator)
{
    ASSERT_TRUE(std::ranges::distance(ax::packet_iterator<const std::byte, get_size>{}) == 0);
}

TEST(TestPacketIterator, EmptyBuffer)
{
    std::vector<int> const buffer{};
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };
    ASSERT_TRUE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 0);
}

TEST(TestPacketIterator, CompletePackets)
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2, 0, 4, 0, 0, 0 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };

    ASSERT_TRUE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 3);

    auto it{ ax::packet_iterator{buffer_as_bytes, get_size{}} };
    ASSERT_TRUE((*it).size() == 3);
    ASSERT_TRUE((*++it).size() == 2);
    ASSERT_TRUE((*++it).size() == 4);
}



TEST(TestPacketIterator, WithLambda)
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2, 0, 4, 0, 0, 0 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };

    ASSERT_TRUE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, 
    [](std::span<const std::byte> buf)
    {
        return std::to_integer<std::size_t>(buf.front());
    }}) == 3);
}

TEST(TestPacketIterator, WithLambdaAndAnotherType)
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2, 0, 4, 0, 0, 0 };

    ASSERT_TRUE(std::ranges::distance(ax::packet_iterator{std::span(buffer), 
    [](std::span<const std::uint8_t> buf)
    {
        return buf.front();
    }}) == 3);
}

TEST(TestPacketIterator, IncompletePackets)
{
    std::vector<std::uint8_t> const buffer{ 3, 0 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };
    ASSERT_TRUE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 0);
}

TEST(TestPacketIterator, IncompletePackets2)
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2 };
    auto const buffer_as_bytes{ std::as_bytes(std::span(buffer)) };
    ASSERT_TRUE(std::ranges::distance(ax::packet_iterator{buffer_as_bytes, get_size{}}) == 1);
    ASSERT_TRUE((*ax::packet_iterator{buffer_as_bytes, get_size{}}).size() == 3);
}

TEST(TestPacketIterator, ReturnRangeFromFunction)
{
    std::vector<std::uint8_t> const buffer{ 3, 0, 0, 2, 0, 4, 0, 0, 0 };
    auto range{ []<typename T>(std::span<T> buffer)
        {
            return ax::packet_iterator{buffer, [](std::span<const std::uint8_t> buf)
                {
                    return buf.front();
                }};
        } };
    ASSERT_TRUE(std::ranges::distance(range(std::span{buffer})) == 3);
}