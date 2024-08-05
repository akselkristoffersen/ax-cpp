#include <ranges>
#include <cmath>
#include <functional>
#include <stdexcept>

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
        for (const auto& val : r)
        {
            sum += std::invoke(proj, val);
        }
    }
    else
    {
        for (const auto& val : r)
        {
            sum += std::invoke(proj, val);
            ++size;
        }
    }
    if (size == 0)
    {
        throw std::invalid_argument("Error: Attempt to compute the mean of an empty range\n");
    }
    return sum / size;
}

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
        for (const auto& val : r)
        {
            sum += std::pow(std::invoke(proj, val) - mean, 2);
        }
    }
    else
    {
        for (const auto& val : r)
        {
            sum += std::pow(std::invoke(proj, val) - mean, 2);
            ++size;
        }
    }
    if (size == 0)
    {
        throw std::invalid_argument("Error: Attempt to compute the variance of an empty range\n");
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