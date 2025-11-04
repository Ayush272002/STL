#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include "array.hpp"

namespace STL {
    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::reference array<T, _Size>::at(size_type pos) {
        if (pos >= _Size)
            throw std::out_of_range(
                "STL::array::at: index " + std::to_string(pos) + " is out of range " + std::to_string(_Size));

        return __elems_[pos];
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reference array<T, _Size>::at(size_type pos) const {
        if (pos >= _Size)
            throw std::out_of_range(
                "STL::array::at: index " + std::to_string(pos) + " is out of range " + std::to_string(_Size));

        return __elems_[pos];
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::reference array<T, _Size>::operator[](size_type pos) {
        return __elems_[pos];
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reference array<T, _Size>::operator[](size_type pos) const {
        return __elems_[pos];
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::reference array<T, _Size>::front() {
        return (*this)[0];
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reference array<T, _Size>::front() const {
        return (*this)[0];
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::reference array<T, _Size>::back() {
        return (*this)[_Size - 1];
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reference array<T, _Size>::back() const {
        return (*this)[_Size - 1];
    }

    template<class T, std::size_t _Size>
    constexpr T *array<T, _Size>::data() {
        return __elems_;
    }

    template<class T, std::size_t _Size>
    constexpr T *array<T, _Size>::data() const noexcept {
        return __elems_;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::iterator array<T, _Size>::begin() noexcept {
        return __elems_;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_iterator array<T, _Size>::begin() const noexcept {
        return __elems_;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_iterator array<T, _Size>::cbegin() const noexcept {
        return __elems_;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::iterator array<T, _Size>::end() noexcept {
        return __elems_ + _Size;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_iterator array<T, _Size>::end() const noexcept {
        return __elems_ + _Size;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_iterator array<T, _Size>::cend() const noexcept {
        return __elems_ + _Size;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::reverse_iterator array<T, _Size>::rbegin() noexcept {
        return reverse_iterator(end());
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reverse_iterator array<T, _Size>::rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reverse_iterator array<T, _Size>::crbegin() const noexcept {
        return rbegin();
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::reverse_iterator array<T, _Size>::rend() noexcept {
        return reverse_iterator(begin());
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reverse_iterator array<T, _Size>::rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::const_reverse_iterator array<T, _Size>::crend() const noexcept {
        return rend();
    }

    template<class T, std::size_t _Size>
    constexpr bool array<T, _Size>::empty() const noexcept {
        return _Size == 0;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::size_type array<T, _Size>::size() const noexcept {
        return _Size;
    }

    template<class T, std::size_t _Size>
    constexpr array<T, _Size>::size_type array<T, _Size>::max_size() const noexcept {
        return _Size;
    }

    template<class T, std::size_t _Size>
    constexpr void array<T, _Size>::fill(const T &value) {
        for (size_type i = 0; i < _Size; i++) {
            __elems_[i] = value;
        }
    }

    template<class T, std::size_t _Size>
    constexpr void array<T, _Size>::swap(array &other) {
        std::swap(__elems_, other.__elems_);
    }

    template<class T, std::size_t _Size>
    constexpr bool operator==(const array<T, _Size> &lhs, const array<T, _Size> &rhs) {
        if (lhs.size() != rhs.size()) return false;
        for (size_t i = 0; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i]) return false;
        }

        return true;
    }

    template<class T, std::size_t _Size>
    constexpr std::strong_ordering operator<=>(const array<T, _Size> &lhs, const array<T, _Size> &rhs) {
        const size_t min_size = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
        for (size_t i = 0; i < min_size; ++i) {
            if (auto cmp = lhs[i] <=> rhs[i]; cmp != 0)
                return cmp;
        }
        return lhs.size() <=> rhs.size();
    }

    template<std::size_t I, class T, std::size_t _Size>
    constexpr T &get(array<T, _Size> &a) noexcept {
        static_assert(I < _Size, "Index out of bounds in array::get");
        return a.__elems_[I];
    }

    template<std::size_t I, class T, std::size_t _Size>
    constexpr const T &get(const array<T, _Size> &a) noexcept {
        static_assert(I < _Size, "Index out of bounds in array::get");
        return a.__elems_[I];
    }

    template<std::size_t I, class T, std::size_t _Size>
    constexpr T &&get(array<T, _Size> &&a) noexcept {
        static_assert(I < _Size, "Index out of bounds in array::get");
        return std::move(a.__elems_[I]);
    }

    template<std::size_t I, class T, std::size_t _Size>
    constexpr T &&get(const array<T, _Size> &&a) noexcept {
        static_assert(I < _Size, "Index out of bounds in array::get");
        return std::move(a.__elems_[I]);
    }

    template<class T, std::size_t _Size>
    constexpr void swap(array<T, _Size> &lhs, array<T, _Size> &rhs) noexcept {
        lhs.swap(rhs);
    }

    template<class T, std::size_t _Size>
    constexpr array<std::remove_cv_t<T>, _Size> to_array(T (&a)[_Size]) {
        array<std::remove_cv_t<T>, _Size> result{};
        for (std::size_t i = 0; i < _Size; ++i) {
            result[i] = a[i];
        }
        return result;
    }

    template<class T, std::size_t _Size>
    constexpr array<std::remove_cv_t<T>, _Size> to_array(T (&&a)[_Size]) {
        array<std::remove_cv_t<T>, _Size> result{};
        for (std::size_t i = 0; i < _Size; ++i) {
            result[i] = std::move(a[i]);
        }
        return result;
    }
}
