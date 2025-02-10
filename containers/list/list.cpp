#include "list.hpp"
using namespace std;

namespace stl
{

    template <typename T>
    list<T>::list()
    {
        head = nullptr;
        size = 0;
    }

    template <typename T>
    list<T>::~list()
    {
        clear();
    }

    template <typename T>
    void list<T>::push_front(T val)
    {
        Node<T> *new_head = new Node<T>(val, head);
        head = new_head;
        size++;
    }

    template <typename T>
    void list<T>::push_back(T val)
    {
        Node<T> *new_node = new Node<T>(val);

        if (head == nullptr)
        {
            head = new_node; 
        }
        else
        {
            Node<T> *curr = head;
            while (curr->next)
                curr = curr->next;

            curr->next = new_node;
        }

        size++;
    }

    template <typename T>
    void list<T>::insert(size_t index, T val)
    {
        if (index >= size || size < 0)
        {
            throw runtime_error("Out of bounds");
            return;
        }

        if (index == 0)
        {
            push_front(val);
            return;
        }

        int i = 0;
        Node<T> *curr = head;
        while (i != (index - 1))
        {
            curr = curr->next;
            i++;
        }

        Node<T> *node_to_insert = new Node(val);
        Node<T> *next = curr->next;
        curr->next = node_to_insert;
        node_to_insert->next = next;
        size++;
    }

    template <typename T>
    T list<T>::pop_front()
    {
        if (size == 0)
        {
            throw runtime_error("Empty list cant pop anything out");
        }

        T val = head->val;
        Node<T> *next = head->next;
        delete head;
        head = next;
        size--;
        return val;
    }

    template <typename T>
    T list<T>::pop_back()
    {
        if (size == 0)
        {
            throw runtime_error("Empty list cant pop anything out");
        }
        else if (size == 1)
        {
            T head_val = head->val;
            delete head;
            head = nullptr;
            size--;
            return head_val;
        }

        Node<T> *curr = head;
        Node<T> *prev = nullptr;

        while (curr->next)
        {
            prev = curr;
            curr = curr->next;
        }

        T last_val = curr->val;
        delete curr;
        prev->next = nullptr;
        size--;
        return last_val;
    }

    template <typename T>
    void list<T>::erase(size_t index)
    {
        if (index >= size || size < 0)
        {
            throw runtime_error("Out of bounds");
            return;
        }

        if (index == 0)
        {
            pop_front();
            return;
        }

        Node<T> *curr = head;
        Node<T> *prev = nullptr;

        int i = 0;
        while (i != index)
        {
            prev = curr;
            curr = curr->next;
            i++;
        }

        Node<T> *next = curr->next;
        delete curr;
        prev->next = next;
        size--;
        return;
    }

    template <typename T>
    T list<T>::front()
    {
        return head->val;
    }

    template <typename T>
    T list<T>::back()
    {
        Node<T> *curr = head;
        while (curr->next)
        {
            curr = curr->next;
        }

        return curr->val;
    }

    template <typename T>
    T &list<T>::operator[](size_t index)
    {
        if (index >= size || size < 0 || index < 0)
        {
            throw runtime_error("Out of bounds");
        }

        int i = 0;
        Node<T> *curr = head;
        while (i != index)
        {
            curr = curr->next;
            i++;
        }

        return curr->val;
    }

    template <typename T>
    size_t list<T>::getSize()
    {
        return size;
    }

    template <typename T>
    bool list<T>::is_empty()
    {
        return size == 0;
    }

    template <typename T>
    void list<T>::clear()
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            Node<T> *next = curr->next;
            delete curr;
            curr = next;
        }

        head = nullptr;
        size = 0;
    }

    template <typename T>
    void list<T>::print()
    {
        if (head == nullptr)
        {
            cout << "()\n";
        }
        else
        {
            cout << "(";
            Node<T> *curr = head;
            while (curr != nullptr)
            {
                cout << curr->val;
                curr = curr->next;
                if (curr)
                    cout << " -> ";
            }

            cout << ")\n";
        }
    }

    template class list<int>;
    template class list<float>;
    template class list<double>;
    template class list<bool>;
    template class list<char>;
}