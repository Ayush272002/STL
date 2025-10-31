#pragma once
#include <ranges>
#include <compare>
#include <iterator>

namespace STL {

    template<typename R, typename T>
    concept container_compatible_range =
    std::ranges::range<R> &&
    std::constructible_from<T, std::ranges::range_reference_t<R>>;

    template<typename T>
    class vector {
    public:
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;

        // constructor
        vector();
        explicit vector(size_type count);
        constexpr vector(size_type count, const T& value);

        template<std::input_iterator InputIt>
        constexpr vector(InputIt first, InputIt last);

        template<container_compatible_range<T> R>
        constexpr vector(std::from_range_t, R&& rg);

        constexpr vector(const vector& other);
        constexpr vector(vector&& other) noexcept;

        vector(std::initializer_list<T> init);

        // destructor
        ~vector();

        // operator =
        constexpr vector& operator=(const vector& other);
        constexpr vector& operator=(vector&& other) noexcept;
        constexpr vector& operator=(std::initializer_list<value_type> ilist);

        // assign
        constexpr void assign(size_type count, const T& value);

        template<std::input_iterator InputIt>
        constexpr void assign(InputIt first, InputIt last);

        constexpr void assign(std::initializer_list<T> ilist);

        // assign range
        template<container_compatible_range<T> R>
        constexpr void assign_range(R&& rg);

        // at
        constexpr reference at(size_type pos);
        constexpr const_reference at(size_type pos) const;

        // operator []
        constexpr reference operator[](size_type pos);
        constexpr const_reference operator[](size_type pos) const;

        // front
        constexpr reference front();
        constexpr const_reference front() const;

        // back
        constexpr reference back();
        constexpr const_reference back() const;

        // data
        constexpr T* data();
        constexpr const T* data() const;

        // iterator

        // begin/cbegin
        constexpr T* begin();
        constexpr const T* begin() const;
        constexpr const T* cbegin() const noexcept;

        // end/cend
        constexpr T* end();
        constexpr const T* end() const;
        constexpr const T* cend() const noexcept;

        // rbegin/crbegin
        constexpr T* rbegin();
        constexpr const T* rbegin() const;
        constexpr const T* crbegin() const noexcept;

        // rend/crend
        constexpr T* rend();
        constexpr const T* rend() const;
        constexpr const T* crend() const noexcept;

        // capacity
        constexpr bool empty() const;
        constexpr size_type size() const;
        constexpr size_type max_size() const;
        constexpr void reserve(size_type new_cap);
        constexpr size_type capacity() const;
        constexpr void shrink_to_fit();

        // modifiers
        constexpr void clear();

        //insert
        constexpr T* insert(const T* pos, const T& value);
        constexpr T* insert(const T* pos, T&& value);
        constexpr T* insert(const T* pos, size_type count, const T& value);

        template<std::input_iterator InputIt>
        constexpr T* insert(const T* pos, InputIt first, InputIt last);

        constexpr T* insert(const T* pos, std::initializer_list<T> ilist);

        // insert range
        template<container_compatible_range<T> R>
        constexpr T* insert(const T* pos, R&& rg);

        // emplace
        template<class... Args>
        constexpr T* emplace(const T* pos, Args&&... args);

        // erase
        constexpr T* erase(const T* pos);
        constexpr T* erase(T* first, T* last);

        // push_back
        constexpr void push_back(const T& value);
        constexpr void push_back(T&& value);

        // emplace_back
        template<class... Args>
        constexpr reference emplace_back(Args&&... args);

        // append range
        template<container_compatible_range<T> R>
        constexpr void append_range(R&& rg);

        // pop back
        constexpr void pop_back();

        // resize
        constexpr void resize(size_type count);
        constexpr void resize(size_type count, const value_type& value);

        // swap
        constexpr void swap(vector& other) noexcept;

    private:
        T* _data;
        size_type _size;
        size_type _capacity;
    };

    template<class T>
    constexpr bool operator==(const vector<T>& lhs, const vector<T>& rhs);

    template<class T>
    constexpr std::strong_ordering operator<=>(const vector<T>& lhs, const vector<T>& rhs);

    template<class T>
    constexpr void swap(vector<T>& lhs, vector<T>& rhs) noexcept;

    template<class T, class U>
    constexpr vector<T>::size_type
        erase(vector<T>& c, const U& value);

    template<class T, class Pred>
    constexpr vector<T>::size_type
        erase_if(vector<T>& c, Pred pred);
}

#include "vector.tpp"