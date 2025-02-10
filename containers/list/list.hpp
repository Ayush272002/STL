#include <bits/stdc++.h>
using namespace std;

namespace stl
{
    template <typename T>
    struct Node
    {
        T val;
        Node *next;

        Node(T v, Node *nxtNode = nullptr)
        {
            val = v;
            next = nxtNode;
        }
    };

    template <typename T>
    class list
    {
    private:
        Node<T> *head;
        size_t size;

    public:
        list();
        ~list();

        void push_front(T value);
        void push_back(T value);
        void insert(size_t index, T val);

        T pop_front();
        T pop_back();
        void erase(size_t index);

        T front();
        T back();
        T &operator[](size_t index);

        size_t getSize();
        bool is_empty();
        void clear();

        void print();
    };
}