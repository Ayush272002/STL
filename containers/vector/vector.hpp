#include <bits/stdc++.h>
using namespace std;

namespace stl
{
    template <typename T>
    class vector
    {
    private:
        int size;
        int capacity;
        unique_ptr<T[]> data;

    public:
        vector();

        int getSize();
        int getCapacity();
        void resize(int newSize);

        T &operator[](int index);

        void push_back(T value);
        T pop_back();

        void clear();

        T *begin();
        T *end();

        string toString();
    };
}