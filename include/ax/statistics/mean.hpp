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
[[nodiscard]] constexpr T mean(R&& r, Proj proj = {})
{
    T sum{};
    std::size_t size{};

    if constexpr (std::ranges::sized_range<R>)
    {
        size = std::ranges::size(r);
    }
  
    for (const auto& val : r)
    {
        sum += std::invoke(proj, val);
        if constexpr (!std::ranges::sized_range<R>)
        {
            ++size;
        }
    }
    
    if (size == 0)
    {
        throw std::invalid_argument("Error: Attempted to compute the mean of an empty range");
    }
    return sum / size;
}

}