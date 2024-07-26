#include <iterator>
#include <span>

namespace ax
{
    template<typename T, typename F>
    requires std::is_invocable_r_v<std::size_t, F, std::span<T>>
    class packet_iterator
    {
    public:
        packet_iterator() = default;
        packet_iterator(std::span<T> buffer, F func)
            : buffer(buffer), get_size_func(std::move(func))
        {
        }

        using difference_type = std::ptrdiff_t;
        using value_type = std::span<T>;

        std::span<T> operator*() const
        {
            return buffer.subspan(0, get_size_func(buffer));
        }

        packet_iterator& operator++()
        {
            buffer = buffer.subspan(get_size_func(buffer));
            return *this;
        }

        packet_iterator operator++(int)
        {
            auto tmp{ *this };
            ++*this;
            return tmp;
        }

        bool operator==(const packet_iterator& rhs) const
        {
            return buffer.data() == rhs.buffer.data();
        }

        bool operator==(const std::default_sentinel_t&) const
        {
            if (buffer.empty())
            {
                return true;
            }
            auto const size{ get_size_func(buffer) };
            return size == 0 || size > buffer.size();
        }

        packet_iterator begin() const
        {
            return *this;
        }

        std::default_sentinel_t end() const
        {
            return {};
        }

    private:
        std::span<T> buffer;
        F get_size_func;
    };
}

template<typename T, typename F>
requires std::is_invocable_r_v<std::size_t, F, std::span<const std::byte>>
inline constexpr bool std::ranges::enable_borrowed_range<ax::packet_iterator<T, F>> = true;