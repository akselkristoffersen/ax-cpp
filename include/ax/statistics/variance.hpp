#pragma once
#include <ranges>
#include <functional>

namespace ax::ranges
{


template<
    std::floating_point T = double,
    std::ranges::input_range R,
    typename Proj = std::identity
    >
    requires std::convertible_to<std::iter_value_t<std::projected<std::ranges::iterator_t<R>, Proj>>, T>
[[nodiscard]] constexpr T variance(R&& r, Proj proj = {})
{
    // Using Welford's method
    T mean{};
    T M2{};
    std::size_t n{};

    for (const auto& value : r) 
    {
        ++n;
        const T val{ std::invoke(proj, value) };
        const T delta{ val - mean };
        mean += delta / n;
        M2 += delta * (val - mean);
    }

    if (n == 0)
    {
        throw std::invalid_argument("Error: Attempted to compute the variance of an empty range");
    }
    return M2 / n;
}


}