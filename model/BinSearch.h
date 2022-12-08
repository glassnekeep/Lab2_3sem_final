#pragma once

#include "array/ArraySequence.h"

template <class T, class U>
class BinSearh {
public:
    static bool bin_Search(U* arr, T key);
};

template<class T, class U>
bool BinSearh<T, U>::bin_Search(U* arr, T key) {
    int l = 0;
    int r = arr->getLength();
    int mid;

    while (l < r) {
        mid = (l + r) / 2;
        if (arr->get(mid) > key)
            r = mid;
        else
            l = mid + 1;
    }
    r--;

    if (arr->get(r) == key)
        return true;
    return false;
}


