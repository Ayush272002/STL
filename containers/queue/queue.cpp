#include "queue.hpp"
using namespace std;

namespace stl
{
    template <typename T>
    queue<T>::queue() {}

    template <typename T>
    queue<T>::~queue() {}

    template <typename T>
    void queue<T>::push(T val)
    {
        q.push_back(val);
    }

    template <typename T>
    void queue<T>::pop()
    {
        if (!q.empty())
            q.erase(q.begin());
        else
            throw runtime_error("Queue is empty\n");
    }

    template <typename T>
    T queue<T>::front()
    {
        if (q.empty())
            throw runtime_error("Queue is empty\n");

        return q.front();
    }

    template <typename T>
    size_t queue<T>::size()
    {
        return q.size();
    }

    template <typename T>
    bool queue<T>::isempty()
    {
        return q.empty();
    }

    template <typename T>
    void queue<T>::print()
    {
        if (q.empty())
            cout << "()\n";
        else
        {
            cout << "(";
            for (size_t i = 0; i < q.size(); i++)
            {
                cout << q[i];
                if (i + 1 < q.size())
                    cout << " -> ";
            }

            cout << ")\n";
        }
    }

    template class queue<int>;
    template class queue<float>;
    template class queue<double>;
    template class queue<bool>;
    template class queue<char>;
}