#include <span>
#include <iterator>

namespace ax
{
    template<typename T, typename F>
    class packet_iterator
    {
    public:
        packet_iterator() = default;
        packet_iterator(std::span<T>, F);

        using difference_type = std::ptrdiff_t;
        using value_type = std::span<T>;

        std::span<T> operator*() const;
        packet_iterator& operator++();
        packet_iterator operator++(int);
        bool operator==(const packet_iterator&) const;
        bool operator==(const std::default_sentinel_t&) const;

        packet_iterator begin() const;
        std::default_sentinel_t end() const;

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

    template<typename T, typename F>
    packet_iterator<T, F>::packet_iterator(std::span<T> buffer, F func)
        : buffer(buffer), func(func)
    {
    }

    template<typename T, typename F>
    std::span<T> packet_iterator<T, F>::operator*() const
    {
        return buffer.subspan(current_pos, func(buffer.subspan(current_pos)));
    }

    template<typename T, typename F>
    packet_iterator<T, F>& packet_iterator<T, F>::operator++()
    {
        current_pos += func(buffer.subspan(current_pos));
        return *this;
    }

    template<typename T, typename F>
    packet_iterator<T, F> packet_iterator<T, F>::operator++(int)
    {
        auto tmp{ *this };
        ++*this;
        return tmp;
    }

    template<typename T, typename F>
    bool packet_iterator<T, F>::operator==(const packet_iterator& rhs) const
    {
        if (buffer.data() != rhs.buffer.data())
        {
            return false;
        }
        return current_pos == rhs.current_pos;
    }

    template<typename T, typename F>
    bool packet_iterator<T, F>::operator==(const std::default_sentinel_t&) const
    {
        return is_end();
    }

    template<typename T, typename F>
    packet_iterator<T, F> packet_iterator<T, F>::begin() const
    {
        return { buffer, func };
    }

    template<typename T, typename F>
    std::default_sentinel_t packet_iterator<T, F>::end() const
    {
        return {};
    }
}

template<typename T, typename F>
inline constexpr bool std::ranges::enable_borrowed_range<ax::packet_iterator<T, F>> = true;