#pragma once

#include <iostream>

#include "Sequence.h"
#include "DynamicArray.h"

using namespace std;

template <class T>
class ArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* items;

public:
	ArraySequence(int size) {
		items = new DynamicArray<T>(size);
	}

	ArraySequence(T* arr, int count) {
		items = new DynamicArray<T>(arr, count);
	}

	ArraySequence(ArraySequence<T>& list) {
		this->items = new DynamicArray<T>(list.getLength());
		for (int i = 0; i < list.getLength(); i++)
			this->items->setData(list.get(i), i);
	}

	~ArraySequence() {
		items->~DynamicArray();
	}

	void output() override {
		items->output();
	}

	int getLength() override {
		return items->getSize();
	}

	T getFirst() override {
		return items->getData(0);
	}

	T getLast() override {
		return items->getData(items->getSize() - 1);
	}

	T get(int index) override {
		return items->getData(index);
	}

	void multiplyWythConst(int con) override {
		for (int i = 0; i < getLength(); i++)
			insertAt(get(i) * con, i);
	}

	void append(T item) override {
		items->resize(items->getSize() + 1);
		items->setData(item, items->getSize() - 1);
	}

	void prepend(T item) override {
		items->resize(items->getSize() + 1);
		for (int i = items->getSize() - 1; i > 0; i--) {
			T tmp = items->getData(i);
			items->setData(items->getData(i - 1), i);
			items->setData(tmp, i - 1);
		}
		items->setData(item, 0);
	}

	void insertAt(T item, int index) override {
		items->setData(item, index);
	}

	T operator[](int index) {
		return get(index);
	}

	void swap(int a, int b) override {
		int a_it = a, b_it = b;
		T a_val = get(a_it), b_val = get(b_it);
		insertAt(a_val, b_it);
		insertAt(b_val, a_it);
	}

	pair<int*, int> arrToIntArr() {
		int* res = new int[getLength()];
		for (int i = 0; i < getLength(); i++)
			res[i] = get(i);
		return make_pair(res, getLength());
	}
};
