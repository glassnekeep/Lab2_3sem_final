#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template <class T >
class DynamicArray {
private:
    T* a;
    int size;

public:
    DynamicArray(int size) {
        this->size = size;
        a = new T[size];
    }
    DynamicArray(T* items, int count) : DynamicArray(count) {
        for (int i = 0; i < count; i++)
            a[i] = items[i];
    }
    DynamicArray(const DynamicArray<T>& arr) {
        this->size = size;
        if (size != 0)
            a = new T[size];
        else
            a = 0;
        for (int i = 0; i < size; ++i)
            a[i] = arr.a[i];
    }
    ~DynamicArray() {
        delete[] a;
    }

    //void setSize(int n) {
    //    size = n;
    //    delete[] a;
    //    a = new T[size];
    //}

    void setData(T data, int index) {
        if (index < size && index >= 0)
            a[index] = data;
        else
            throw exception();
    }

    void output() {
        for (int i = 0; i < size; i++)
            cout << a[i] << " ";
        cout << "\n";
    }

    int getSize() { return size; }

    int getData(int index) {
        if (index <= size && index >= 0)
            return a[index];
        throw exception();
    }

    void resize(int newSize) {
        int tempSize = newSize > size ? size : newSize;
        T* newData = new T[newSize];
        for (int i = 0; i < newSize; i++)
            newData[i] = a[i];
        delete[] a;
        a = newData;
        size = newSize;
    }

    T operator[](int index) {
        return getData(index);
    }
};