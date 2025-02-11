#include <bits/stdc++.h>
using namespace std;

namespace stl
{
    class string
    {
    private:
        unique_ptr<char[]> data;
        size_t size;
        size_t capacity;

        void resize(size_t newSize);

    public:
        string();
        string(const char *str); // constructor from c-string

        size_t getSize() const;
        size_t getCapacity() const;
        void reserve(size_t new_capacity); // reserve storage

        char &operator[](size_t index); // access element

        string &operator+=(const char *str);
        const char *c_str() const;
    };
}