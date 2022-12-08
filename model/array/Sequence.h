#pragma once

using namespace std;

template <class T>
class Sequence {
public:
	virtual int getLength() = 0;

	virtual T getFirst() = 0;

	virtual T getLast() = 0;

	virtual T get(int index) = 0;

	virtual void append(T item) = 0;

	virtual void prepend(T item) = 0;

	virtual void insertAt(T item, int index) = 0;

	virtual void output() = 0;

	virtual void multiplyWythConst(int con) = 0;

	virtual void swap(int a, int b) = 0;
};

