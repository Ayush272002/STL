#pragma once
#include <algorithm>
#include <stdexcept>
#include <new>

namespace STL {
    template<typename T>
    vector<T>::vector() : _data(nullptr), _size(0), _capacity(0) {
    }

    template<typename T>
    vector<T>::vector(size_type count) : _data(static_cast<T*>(operator new(sizeof(T) * count))), _size(count), _capacity(count) {
        for (size_type i = 0; i < _size; ++i)
            new(&_data[i]) T();
    }

    template<typename T>
    constexpr vector<T>::vector(size_type count, const T &value) : _data(static_cast<T*>(operator new(sizeof(T) * count))), _size(count), _capacity(count) {
        for (size_type i = 0; i < count; i++) new(&_data[i]) T(value);
    }

    template<typename T>
    template<std::input_iterator InputIt>
    constexpr vector<T>::vector(InputIt first, InputIt last) : _data(nullptr), _size(0), _capacity(0) {
        _size = std::distance(first, last);
        if (_size > 0) {
            _capacity = _size;
            _data = static_cast<T*>(::operator new(sizeof(T) * _capacity));

            size_type i = 0;
            try {
                for (; first != last; ++first, ++i) {
                    new(&_data[i]) T(*first);
                }
            } catch (...) {
                while (i > 0) {
                    _data[--i].~T();
                }
                ::operator delete(_data);
                throw;
            }
        }
    }

    template<typename T>
    template<container_compatible_range<T> R>
    constexpr vector<T>::vector(std::from_range_t, R &&rg) : _data(nullptr), _size(0), _capacity(0) {
        if constexpr (std::ranges::sized_range<R>) {
            if (const auto count = static_cast<size_type>(std::ranges::distance(rg)); count > 0) {
                _data = static_cast<T*>(::operator new(sizeof(T) * count));
                _capacity = count;

                size_type i = 0;
                try {
                    for (auto&& elem : rg) {
                        new(&_data[i]) T(std::forward<decltype(elem)>(elem));
                        ++i;
                    }
                    _size = count;
                } catch (...) {
                    // Clean up on exception
                    for (size_type j = 0; j < i; ++j) {
                        _data[j].~T();
                    }
                    ::operator delete(_data);
                    throw;
                }
            }
        } else {
            for (auto&& elem : rg) {
                push_back(std::forward<decltype(elem)>(elem));
            }
        }
    }

    template<typename T>
    constexpr vector<T>::vector(const vector &other) : _data(static_cast<T*>(operator new(sizeof(T) * other._capacity))), _size(other.size()), _capacity(other._capacity) {
        for (size_type i = 0; i < _size; ++i)
            new(&_data[i]) T(other._data[i]);
    }

    template<typename T>
    constexpr vector<T>::vector(vector &&other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    template<typename T>
    vector<T>::vector(std::initializer_list<T> init) : _data(static_cast<T*>(operator new(sizeof(T) * init.size()))), _size(init.size()), _capacity(init.size()) {
        size_type i = 0;
        for (const auto& elem : init)
            new(&_data[i++]) T(elem);
    }

    template<typename T>
    vector<T>::~vector() {
        for (size_type i = 0; i < _size; ++i)
            _data[i].~T();
        operator delete(_data);
    }

    // operator =
    template<typename T>
    constexpr vector<T>& vector<T>::operator=(const vector &other) {
        if (this != &other) {
            for (size_type i = 0; i < _size; ++i)
                _data[i].~T();

            if (_capacity < other._size) {
                operator delete(_data);
                _capacity = other._size;
                _data = static_cast<T*>(operator new(sizeof(T) * _capacity));
            }

            for (size_type i = 0; i < other._size; ++i)
                new(&_data[i]) T(other._data[i]);

            _size = other._size;
        }

        return *this;
    }

    template<typename T>
    constexpr vector<T>& vector<T>::operator=(vector &&other) noexcept {
        if (this != &other) {
            for (size_type i = 0; i < _size; ++i)
                _data[i].~T();

            operator delete(_data);

            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;

            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }

        return *this;
    }

    template<typename T>
    constexpr vector<T>& vector<T>::operator=(std::initializer_list<value_type> ilist) {
        for (size_type i = 0; i < _size; ++i)
            _data[i].~T();

        if (_capacity < ilist.size()) {
            operator delete(_data);
            _capacity = ilist.size();
            _data = static_cast<T*>(operator new(sizeof(T) * _capacity));
        }

        size_type i = 0;
        for (const auto& elem : ilist)
            new(&_data[i++]) T(elem);

        _size = ilist.size();
        return *this;
    }

    // assign
    template<typename T>
    constexpr void vector<T>::assign(size_type count, const T &value) {
        for (size_type i = 0; i < _size; ++i)
            _data[i].~T();

        if (_capacity < count) {
            operator delete(_data);
            _data = static_cast<T*>(operator new(sizeof(T) * count));
            _capacity = count;
        }

        for (size_type i = 0; i < count; ++i)
            new(&_data[i]) T(value);

        _size = count;
    }

    template<typename T>
    template<std::input_iterator InputIt>
    constexpr void vector<T>::assign(InputIt first, InputIt last) {
        clear();
        const size_type new_size = std::distance(first, last);
        if (_capacity < new_size) reserve(new_size);

        for (size_type i = 0; first != last; ++first, ++i) new(&_data[i]) T(*first);

        _size = new_size;
    }

    template<typename T>
    constexpr void vector<T>::assign(std::initializer_list<T> ilist) {
        assign(ilist.begin(),ilist.end());
    }

    // assign range
    template<typename T>
    template<container_compatible_range<T> R>
    constexpr void vector<T>::assign_range(R &&rg) {
        const size_type new_size = std::ranges::distance(rg);

        for (size_type i = 0; i < _size; ++i)
            _data[i].~T();

        if (_capacity < new_size) {
            operator delete(_data);
            _data = static_cast<T*>(operator new(sizeof(T) * new_size));
            _capacity = new_size;
        }

        size_type i = 0;
        for (auto&& elem : rg)
            new(&_data[i++]) T(std::forward<decltype(elem)>(elem));

        _size = new_size;
    }

    // at
    template<typename T>
    constexpr vector<T>::reference vector<T>::at(size_type pos) {
        if (pos >= _size) throw std::out_of_range("vector::at: index out of range");

        return _data[pos];
    }

    template<typename T>
    constexpr vector<T>::const_reference vector<T>::at(size_type pos) const {
        if (pos >= _size) throw std::out_of_range("vector::at: index out of range");

        return _data[pos];
    }

    // operator []
    template<typename T>
    constexpr vector<T>::reference vector<T>::operator[](size_type pos) {
        return _data[pos];
    }

    template<typename T>
    constexpr vector<T>::const_reference vector<T>::operator[](size_type pos) const {
        return _data[pos];
    }

    // front
    template<typename T>
    constexpr vector<T>::reference vector<T>::front() {
        return _data[0];
    }

    template<typename T>
    constexpr vector<T>::const_reference vector<T>::front() const {
        return _data[0];
    }

    template<typename T>
    constexpr vector<T>::reference vector<T>::back() {
        return _data[_size - 1];
    }

    template<typename T>
    constexpr vector<T>::const_reference vector<T>::back() const {
        return _data[_size - 1];
    }

    // data
    template<typename T>
    constexpr T* vector<T>::data() {
        return _data;
    }

    template<typename T>
    constexpr const T* vector<T>::data() const {
        return _data;
    }

    // iterators
    template<typename T>
    constexpr T *vector<T>::begin() {
        return _data;
    }

    template<typename T>
    constexpr const T *vector<T>::begin() const {
        return _data;
    }

    template<typename T>
    constexpr const T *vector<T>::cbegin() const noexcept {
        return _data;
    }

    template<typename T>
    constexpr T* vector<T>::end() {
        return _data + _size;
    }

    template<typename T>
    constexpr const T* vector<T>::end() const {
        return _data + _size;
    }

    template<typename T>
    constexpr const T* vector<T>::cend() const noexcept {
        return _data + _size;
    }

    template<typename T>
    constexpr T* vector<T>::rbegin() {
        return _data + _size;
    }

    template<typename T>
    constexpr const T* vector<T>::rbegin() const {
        return _data + _size;
    }

    template<typename T>
    constexpr const T* vector<T>::crbegin() const noexcept {
        return _data + _size;
    }

    template<typename T>
    constexpr T* vector<T>::rend() {
        return _data;
    }

    template<typename T>
    constexpr const T* vector<T>::rend() const {
        return _data;
    }

    template<typename T>
    constexpr const T* vector<T>::crend() const noexcept {
        return _data;
    }

    // capacity
    template<typename T>
    constexpr bool vector<T>::empty() const {
        return _size == 0;
    }

    template<typename T>
    constexpr vector<T>::size_type vector<T>::size() const {
        return _size;
    }

    template<typename T>
    constexpr vector<T>::size_type vector<T>::max_size() const {
        return static_cast<size_type>(-1)/sizeof(T);
    }

    template<typename T>
    constexpr void vector<T>::reserve(size_type new_cap) {
        if (new_cap <= _capacity) return;

        T* new_data = static_cast<T*>(operator new(sizeof(T) * new_cap));
        for (size_type i = 0; i < _size; ++i) new(&new_data[i]) T(std::move(_data[i]));

        for (size_type i = 0; i < _size; ++i)
            _data[i].~T();

        operator delete(_data);
        _data = new_data;
        _capacity = new_cap;
    }

    template<typename T>
    constexpr vector<T>::size_type vector<T>::capacity() const {
        return _capacity;
    }

    template<typename T>
    constexpr void vector<T>::shrink_to_fit() {
        if (_size == _capacity) return;

        if (_size == 0) {
            for (size_type i = 0; i < _size; ++i)
                _data[i].~T();

            operator delete(_data);
            _data = nullptr;
            _capacity = 0;
            return;
        }

        T* new_data = static_cast<T*>(operator new(sizeof(T) * _size));
        for (size_type i = 0; i < _size; ++i)
            new(&new_data[i]) T(std::move(_data[i]));

        for (size_type i = 0; i < _size; ++i)
            _data[i].~T();

        operator delete(_data);
        _data = new_data;
        _capacity = _size;
    }

    // modifiers
    template<typename T>
    constexpr void vector<T>::clear() {
        for (size_type i = 0; i < _size; ++i)
            _data[i].~T();
        _size = 0;
    }

    // insert
    template<typename T>
    constexpr T* vector<T>::insert(const T *pos, const T &value) {
        size_type idx = pos - _data;
        if (_size + 1 > _capacity) reserve(_capacity ? _capacity * 2 : 1);

        for (size_type i = _size; i > idx; --i) _data[i] = std::move(_data[i-1]);

        _data[idx] = value;
        ++_size;

        return _data + idx;
    }

    template<typename T>
    constexpr T* vector<T>::insert(const T *pos, T &&value) {
        size_type idx = pos - _data;
        if (_size + 1 > _capacity) reserve(_capacity ? _capacity * 2 : 1);

        for (size_type i = _size; i > idx; --i) _data[i] = std::move(_data[i-1]);

        _data[idx] = std::move(value);
        ++_size;

        return _data + idx;
    }

    template<typename T>
    constexpr T* vector<T>::insert(const T *pos, size_type count, const T &value) {
        size_type idx = pos - _data;
        if (_size + count > _capacity) reserve(std::max(_capacity * 2, _size + count));

        if (idx < _size) {
            for (size_type i = _size; i-- > idx; ) {
                _data[i + count] = std::move(_data[i]);
            }
        }

        for (size_type i = 0; i < count; ++i)
            _data[idx + i] = value;

        _size += count;
        return _data + idx;
    }

    template<typename T>
    template<std::input_iterator InputIt>
    constexpr T *vector<T>::insert(const T *pos, InputIt first, InputIt last) {
        size_type idx = pos - _data;
        const size_type count = std::distance(first, last);
        if (_size + count > _capacity) reserve(std::max(_capacity * 2, _size + count));

        for (size_type i = _size; i-- > idx; ) _data[i + count] = std::move(_data[i]);
        for (size_type i = 0; first != last; ++first, ++i) _data[idx + i] = *first;

        _size += count;
        return _data + idx;
    }


    template<typename T>
    constexpr T* vector<T>::insert(const T *pos, std::initializer_list<T> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    // insert range
    template<typename T>
    template<container_compatible_range<T> R>
    constexpr T* vector<T>::insert(const T *pos, R &&rg) {
        size_type idx = pos - _data;
        const size_type count = std::ranges::distance(rg);

        if (_size + count > _capacity) reserve(std::max(_capacity * 2, _size + count));

        for (size_type i = _size; i-- > idx;) _data[i + count] = std::move(_data[i]);

        size_type i = 0;
        for (auto&& elem : rg) _data[idx + i++] = std::forward<decltype(elem)>(elem);

        _size += count;
        return _data + idx;
    }

    // emplace
    template<typename T>
    template<class... Args>
    constexpr T* vector<T>::emplace(const T *pos, Args &&... args) {
        size_type idx = pos - _data;

        if (_size + 1 > _capacity) reserve(_capacity ? _capacity * 2 : 1);

        if (idx < _size) {
            new(&_data[_size]) T(std::move(_data[_size - 1]));

            for (size_type i = _size - 1; i-- > idx; ) {
                _data[i + 1] = std::move(_data[i]);
            }

            _data[idx].~T();
        }

        new(&_data[idx]) T(std::forward<Args>(args)...);

        ++_size;
        return _data + idx;
    }

    // erase
    template<typename T>
    constexpr T* vector<T>::erase(const T *pos) {
        size_type idx = pos - _data;

        if (idx >= _size) return end();

        _data[idx].~T();

        for (size_type i = idx; i < _size - 1; ++i) _data[i] = std::move(_data[i+1]);

        --_size;
        return _data + idx;
    }

    template<typename T>
    constexpr T* vector<T>::erase(T *first, T *last) {
        size_type start = first - _data;
        const size_type endPos = last - _data;

        if (start >= _size || endPos > _size || start >= endPos) return _data + start;

        size_type count = endPos - start;

        for (size_type i = start; i < endPos; ++i) {
            _data[i].~T();
        }

        for (size_type i = endPos; i < _size; ++i) {
            _data[i - count] = std::move(_data[i]);
        }

        _size -= count;
        return _data + start;
    }

    template<typename T>
    constexpr void vector<T>::push_back(const T &value) {
        if (_size == _capacity) reserve(_capacity ? _capacity * 2 : 1);

        new (&_data[_size++]) T(value);
    }

    template<typename T>
    constexpr void vector<T>::push_back(T &&value) {
        if (_size == _capacity) reserve(_capacity ? _capacity * 2 : 1);

        new (&_data[_size++]) T(std::move(value));
    }

    template<typename T>
    template<class... Args>
    constexpr vector<T>::reference vector<T>::emplace_back(Args &&... args) {
        if (_size == _capacity) reserve(_capacity ? _capacity * 2 : 1);

        new (&_data[_size]) T(std::forward<Args>(args)...);
        return _data[_size++];
    }

    template<typename T>
    template<container_compatible_range<T> R>
    constexpr void vector<T>::append_range(R &&rg) {
        const size_type count = std::ranges::distance(rg);

        if (_size + count > _capacity) {
            size_type new_cap = _capacity == 0 ? count : _capacity;
            while (new_cap < _size + count) new_cap *= 2;
            reserve(new_cap);
        }

        size_type idx = _size;
        for (auto&& elem : rg) {
            new(&_data[idx++]) T(std::forward<decltype(elem)>(elem));
        }

        _size += count;
    }

    template<typename T>
    constexpr void vector<T>::pop_back() {
        if (_size == 0) return;
        _data[_size - 1].~T();
        --_size;
    }

    template<typename T>
    constexpr void vector<T>::resize(size_type count) {
        if (count < _size) {
            for (size_type i = count; i < _size; ++i)
                _data[i].~T();
        }
        else if (count > _size) {
            if (count > _capacity)
                reserve(std::max(_capacity * 2, count));

            for (size_type i = _size; i < count; ++i)
                new(&_data[i]) T();
        }

        _size = count;
    }

    template<typename T>
    constexpr void vector<T>::resize(size_type count, const value_type& value) {
        if (count < _size) {
            for (size_type i = count; i < _size; ++i)
                _data[i].~T();
        }
        else if (count > _size) {
            if (count > _capacity)
                reserve(std::max(_capacity * 2, count));

            for (size_type i = _size; i < count; ++i)
                new(&_data[i]) T(value);
        }

        _size = count;
    }

    template<typename T>
    constexpr void vector<T>::swap(vector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    template<class T>
    constexpr bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
        if (lhs.size() != rhs.size()) return false;
        for (size_t i = 0; i < lhs.size(); ++i) {
            if (!(lhs[i] == rhs[i])) return false;
        }
        return true;
    }

    template<class T>
    constexpr std::strong_ordering operator<=>(const vector<T>& lhs, const vector<T>& rhs) {
        const size_t min_size = lhs.size() < rhs.size() ? lhs.size() : rhs.size();

        for (size_t i = 0; i < min_size; ++i) {
            if (auto cmp = lhs[i] <=> rhs[i]; cmp != 0)
                return cmp;
        }
        return lhs.size() <=> rhs.size();
    }

    template<class T>
    constexpr void swap(vector<T>& lhs, vector<T>& rhs) noexcept {
        lhs.swap(rhs);
    }

    template<class T, class U>
    constexpr vector<T>::size_type
    erase(vector<T>& c, const U& value) {
        auto old_size = c.size();

        auto* it = std::remove(c.begin(), c.end(), value);
        c.erase(it, c.end());

        return old_size - c.size();
    }

    template<class T, class Pred>
    constexpr vector<T>::size_type
    erase_if(vector<T>& c, Pred pred) {
        auto old_size = c.size();

        auto* it = std::remove_if(c.begin(), c.end(), pred);
        c.erase(it, c.end());

        return old_size - c.size();
    }
}
