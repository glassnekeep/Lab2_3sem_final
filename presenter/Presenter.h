#pragma once

#include "../model/array/ArraySequence.h"
#include "../model/Sort.h"
#include "../model/BinSearch.h"
#include "../model/HashTable1.h"
#include "../model/BinaryTree1.h"
#include "../model/Person.h"

class Presenter {
private:
	int size;
	int matrix_size;
	ArraySequence<int>* arr;
    Person* arrayFromFile;
	int** matrix;
public:
	void createArr(int size);
    void readArrayFromFile(int size);
	string getArr();
	pair<string, bool> find(string findType, string value);
	static string findMostPopularExp(string s);
	void createMat(int size);
	string getMat();
	string processMat();
	tuple<vector<double>, vector<double>, vector<double>> getPointsForChart();
};
