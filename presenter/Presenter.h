#pragma once

#include "../model/array/ArraySequence.h"
#include "../model/Sort.h"
#include "../model/BinSearch.h"
#include "../model/HashTable1.h"
#include "../model/BinaryTree.h"
#include "../model/tests/Tests.h"

class Presenter {
private:
	int size;
	int matrix_size;
	ArraySequence<int>* arr;
	int** matrix;
public:
	void createArr(int size);
	string getArr();
	pair<string, bool> find(string findType, string value);
	string findMostPopularExp(string s);
	void createMat(int size);
	string getMat();
	string processMat();
	string getTestRes();
	tuple<vector<double>, vector<double>, vector<double>> getPointsForChart();
};
