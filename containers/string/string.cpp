#include "string.hpp"
using namespace std;

namespace stl
{
    string::string()
    {
        data = make_unique<char[]>(0);
        size = 0;
        capacity = 0;
    }

    string::string(const char *str)
    {
        size_t input_len = strlen(str);

        data = make_unique<char[]>(input_len + 1);
        memcpy(data.get(), str, input_len + 1);

        size = input_len;
        capacity = input_len;
    }

    void string::resize(size_t newSize)
    {
        unique_ptr<char[]> newData = make_unique<char[]>(newSize);

        memcpy(newData.get(), data.get(), size + 1);
        data = move(newData);
        capacity = newSize;
    }

    size_t string::getSize() const
    {
        return size;
    }

    size_t string::getCapacity() const
    {
        return capacity;
    }

    void string::reserve(size_t new_capacity)
    {
        if (capacity >= new_capacity)
            return;

        resize(new_capacity);
        capacity = new_capacity;
    }

    char &string::operator[](size_t index)
    {
        if (index < 0 || index >= size)
            throw runtime_error("Out of bounds");

        return data[index];
    }

    string &string::operator+=(const char *str)
    {
        size_t strLen = strlen(str);

        if ((strLen + size) > capacity)
        {
            size_t new_capacity = (strLen + size) * 2;
            resize(new_capacity);
        }

        memcpy(data.get() + size, str, strLen);
        size += strLen;

        return *this;
    }

    const char *string::c_str() const
    {
        return data.get();
    }
}