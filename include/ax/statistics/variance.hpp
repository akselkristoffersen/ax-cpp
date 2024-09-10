#pragma once
#include <ranges>
#include <functional>
#include <cmath>
#include "mean.hpp"

namespace ax::ranges
{


template<
    std::floating_point T = double,
    std::ranges::input_range R,
    std::convertible_to<T> Mean,
    typename Proj = std::identity
    >
    requires std::convertible_to<std::iter_value_t<std::projected<std::ranges::iterator_t<R>, Proj>>, T>
[[nodiscard]] constexpr T variance(R&& r, Mean mean, Proj proj = {})
{
    T sum{};
    std::size_t size{};
    
    if constexpr (std::ranges::sized_range<R>)
    {
        size = std::ranges::size(r);
    }

    for (const auto& val : r)
    {
        sum += std::pow(std::invoke(proj, val) - mean, 2);
        if constexpr (!std::ranges::sized_range<R>)
        {
            ++size;
        }
    }

    if (size == 0)
    {
        throw std::invalid_argument("Error: Attempted to compute the variance of an empty range");
    }
    return sum / size;
}


template<
    std::floating_point T = double,
    std::ranges::input_range R,
    typename Proj = std::identity
    >
    requires std::convertible_to<std::iter_value_t<std::projected<std::ranges::iterator_t<R>, Proj>>, T>
[[nodiscard]] constexpr T variance(R&& r, Proj proj = {})
{
    auto const mean{ ax::ranges::mean<T>(r, proj) };
    return ax::ranges::variance<T>(r, mean, proj);
}


}