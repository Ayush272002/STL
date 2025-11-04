#pragma once
#include <cstddef>
#include <iterator>

namespace STL {

    template<class T, std::size_t _Size>
    struct array {
        using value_type = T;
        using size_type = std::size_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        T __elems_[_Size];

        // element access
        constexpr reference at(size_type pos);
        constexpr const_reference at(size_type pos) const;

        constexpr reference operator[](size_type pos);
        constexpr const_reference operator[](size_type pos) const;

        constexpr reference front();
        constexpr const_reference front() const;

        constexpr reference back();
        constexpr const_reference back() const;

        constexpr T* data();
        constexpr T* data() const noexcept;

        // iterators
        constexpr iterator begin() noexcept;
        constexpr const_iterator begin() const noexcept;
        constexpr  const_iterator cbegin() const noexcept;

        constexpr iterator end() noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cend() const noexcept;

        constexpr reverse_iterator rbegin() noexcept;
        constexpr const_reverse_iterator rbegin() const noexcept;
        constexpr const_reverse_iterator crbegin() const noexcept;

        constexpr reverse_iterator rend() noexcept;
        constexpr const_reverse_iterator rend() const noexcept;
        constexpr const_reverse_iterator crend() const noexcept;

        // capacity
        constexpr bool empty() const noexcept;
        constexpr size_type size() const noexcept;
        constexpr size_type max_size() const noexcept;

        // operations
        constexpr void fill(const T& value);
        constexpr void swap(array& other);
    };

    template<class T, std::size_t _Size>
    constexpr bool operator==(const array<T,_Size>& lhs, const array<T,_Size>& rhs);

    template<class T, std::size_t _Size>
    constexpr std::strong_ordering operator<=>(const array<T, _Size>& lhs, const array<T, _Size>& rhs);

    template<std::size_t I, class T, std::size_t _Size>
    constexpr T& get(array<T,_Size>& a) noexcept;

    template<std::size_t I, class T, std::size_t _Size>
    constexpr T&& get(array<T,_Size>&& a) noexcept;

    template<std::size_t I, class T, std::size_t _Size>
    constexpr const T& get( const array<T,_Size>& a ) noexcept;

    template<std::size_t I, class T, std::size_t _Size>
    constexpr T&& get( const array<T,_Size>&& a ) noexcept;

    template<class T, std::size_t _Size>
    constexpr void swap(array<T, _Size>& lhs, array<T, _Size>& rhs) noexcept;

    template<class T, std::size_t _Size>
    constexpr array<std::remove_cv_t<T>, _Size> to_array(T (&a)[_Size]);

    template<class T, std::size_t _Size>
    constexpr array<std::remove_cv_t<T>, _Size> to_array(T (&&a)[_Size]);
}

#include "array.tpp"