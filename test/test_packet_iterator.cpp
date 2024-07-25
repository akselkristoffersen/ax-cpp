#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <ax/packet_iterator.hpp>

// Test cases
TEST_CASE("test_packet_iterator", "[packet_iterator]")
{
    REQUIRE(ax::packet_iterator());
}