#include "vector.hpp"
using namespace std;

namespace stl
{
    template <typename T>
    vector<T>::vector()
    {
        size = 0;
        capacity = 0;

        data = make_unique<T[]>(0);
    }

    template <typename T>
    int vector<T>::getCapacity()
    {
        return capacity;
    }

    template <typename T>
    int vector<T>::getSize()
    {
        return size;
    }

    template <typename T>
    void vector<T>::resize(int newSize)
    {
        // new arr creation
        unique_ptr<T[]> newArrPtr = make_unique<T[]>(newSize);

        // copy old data
        for (int i = 0; i < this->getSize(); i++)
        {
            newArrPtr[i] = data[i];
        }

        data = move(newArrPtr);
        capacity = newSize;
    }

    template <typename T>
    T &vector<T>::operator[](int index)
    {
        if (index < 0 || index >= getSize())
            throw runtime_error("Out of bounds");

        return data[index];
    }

    template <typename T>
    void vector<T>::push_back(T value)
    {
        if (getSize() + 1 > getCapacity())
        {
            cout << "Increasing size\n";
            if (getCapacity() > 0)
                resize(getCapacity() * 2);
            else
                resize(1);
        }

        data[size++] = value;
    }

    template <typename T>
    T vector<T>::pop_back()
    {
        T value = data[size - 1];
        size--;
        return value;
    }

    template <typename T>
    void vector<T>::clear()
    {
        size = 0;
    }

    template <typename T>
    T *vector<T>::begin()
    {
        return data.get();
    }

    template <typename T>
    T *vector<T>::end()
    {
        return data.get() + size;
    }

    template <typename T>
    string vector<T>::toString()
    {
        ostringstream oss;
        oss << "[";

        for (int i = 0; i < getSize(); i++)
        {
            if (i + 1 != getSize())
                oss << data[i] << ", ";
            else
                oss << data[i];
        }

        oss << "]\n";
        oss << "Size: " << getSize() << " Capacity: " << getCapacity() << "\n";

        return oss.str();
    }

    template class vector<int>;
    template class vector<float>;
    template class vector<double>;
    template class vector<bool>;
    template class vector<char>;

    template class vector<std::string>;
}