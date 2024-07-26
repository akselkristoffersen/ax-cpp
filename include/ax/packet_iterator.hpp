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
            : buffer(buffer), func(std::move(func))
        {
        }

        using difference_type = std::ptrdiff_t;
        using value_type = std::span<T>;

        std::span<T> operator*() const
        {
            return buffer.subspan(current_pos, func(buffer.subspan(current_pos)));
        }

        packet_iterator& operator++()
        {
            current_pos += func(buffer.subspan(current_pos));
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
            if (buffer.data() != rhs.buffer.data())
            {
                return false;
            }
            return current_pos == rhs.current_pos;
        }

        bool operator==(const std::default_sentinel_t&) const
        {
            return is_end();
        }

        packet_iterator begin() const
        {
            return { buffer, func };
        }

        std::default_sentinel_t end() const
        {
            return {};
        }

    private:
        std::span<T> buffer;
        std::size_t current_pos{};
        F func;

        [[nodiscard]] bool is_end() const
        {
            if (buffer.empty())
            {
                return true;
            }
            auto const next_size{ func(buffer.subspan(current_pos)) };
            return next_size == 0 || current_pos + next_size > buffer.size();
        }
    };
}

template<typename T, typename F>
requires std::is_invocable_r_v<std::size_t, F, std::span<const std::byte>>
inline constexpr bool std::ranges::enable_borrowed_range<ax::packet_iterator<T, F>> = true;