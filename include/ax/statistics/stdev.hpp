#pragma once
#include <ranges>
#include <functional>
#include "variance.hpp"

namespace ax::ranges
{


template<
    std::floating_point T = double,
    std::ranges::input_range R,
    std::convertible_to<T> Mean,
    typename Proj = std::identity
    >
    requires std::convertible_to<std::iter_value_t<std::projected<std::ranges::iterator_t<R>, Proj>>, T>
[[nodiscard]] constexpr T standard_deviation(R&& r, Mean mean, Proj proj = {})
{
    const auto variance{ ax::ranges::variance<T>(r, mean, proj) };
    return std::sqrt(variance);
}


template<
	std::floating_point T = double,
	std::ranges::input_range R,
	typename Proj = std::identity
    >
	requires std::convertible_to<std::iter_value_t<std::projected<std::ranges::iterator_t<R>, Proj>>, T>
[[nodiscard]] constexpr T standard_deviation(R&& r, Proj proj = {})
{
	auto const mean{ ax::ranges::mean<T>(r, proj) };
	return ax::ranges::standard_deviation<T>(r, mean, proj);
}


}