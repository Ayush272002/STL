#include "stack.hpp"
using namespace std;

namespace stl
{
    template <typename T>
    stack<T>::stack() {}

    template <typename T>
    stack<T>::~stack() {}

    template <typename T>
    void stack<T>::push(T val)
    {
        st.insert(st.begin(), val);
    }

    template <typename T>
    void stack<T>::pop()
    {
        if (st.empty())
            throw runtime_error("Stack is empty");

        st.erase(st.begin());
    }

    template <typename T>
    T stack<T>::top()
    {
        if (st.empty())
            throw runtime_error("Stack is empty");

        return st[0];
    }

    template <typename T>
    size_t stack<T>::size()
    {
        return st.size();
    }

    template <typename T>
    bool stack<T>::isempty()
    {
        return st.empty();
    }

    template <typename T>
    void stack<T>::print()
    {
        if (st.empty())
            cout << "()\n";
        else
        {
            cout << "(";
            for (size_t i = 0; i < st.size(); i++)
            {
                cout << st[i];
                if (i + 1 < st.size())
                    cout << " -> ";
            }

            cout << ")\n";
        }
    }

    template class stack<int>;
    template class stack<float>;
    template class stack<double>;
    template class stack<bool>;
    template class stack<char>;
}