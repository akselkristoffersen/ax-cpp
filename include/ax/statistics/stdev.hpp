#pragma once
#include <ranges>
#include <functional>
#include <cmath>
#include "variance.hpp"

namespace ax::ranges
{


template<
	std::floating_point T = double,
	std::ranges::input_range R,
	typename Proj = std::identity
    >
	requires std::convertible_to<std::iter_value_t<std::projected<std::ranges::iterator_t<R>, Proj>>, T>
[[nodiscard]] constexpr T stdev(R&& r, Proj proj = {})
{
    const auto variance{ ax::ranges::variance<T>(r, proj) };
    return std::sqrt(variance);
}


}