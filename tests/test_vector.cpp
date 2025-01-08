#include <cassert>
#include<iostream>
#include "../containers/vector/vector.hpp"

using namespace std;

int main()
{
    stl::vector<int> v;

    assert(v.getSize() == 0);
    assert(v.getCapacity() == 0);

    v.push_back(1);
    assert(v.getSize() == 1);
    assert(v.getCapacity() == 1);
    assert(v[0] == 1);

    v.push_back(2);
    assert(v.getSize() == 2);
    assert(v.getCapacity() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);

    v.push_back(3);
    assert(v.getSize() == 3);
    assert(v.getCapacity() == 4);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);

    v.pop_back();
    assert(v.getSize() == 2);
    assert(v.getCapacity() == 4);
    assert(v[0] == 1);
    assert(v[1] == 2);

    v.resize(100);
    assert(v.getSize() == 2);
    assert(v.getCapacity() == 100);

    assert(v.toString() == "[1, 2]\nSize: 2 Capacity: 100\n");

    v.clear();
    assert(v.getSize() == 0);
    assert(v.getCapacity() == 100);

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    int *beginPtr = v.begin();
    int *endPtr = v.end();

    assert(*(beginPtr) == 10);
    assert(*(endPtr - 1) == 30);

    int index = 0;
    for (int *ptr = v.begin(); ptr != v.end(); ++ptr, ++index)
    {
        if (index == 0)
            assert(*ptr == 10);
        else if (index == 1)
            assert(*ptr == 20);
        else if (index == 2)
            assert(*ptr == 30);
    }

    cout << "\033[32mAll tests passed!\033[0m" << endl;
    return 0;
}