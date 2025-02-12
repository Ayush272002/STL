#include <bits/stdc++.h>
using namespace std;

namespace stl
{
    template <typename T>
    class queue
    {
    private:
        vector<T> q;

    public:
        queue();
        ~queue();

        void push(T val);
        void pop();

        T front();
        size_t size();

        bool isempty();

        void print();
    };
}