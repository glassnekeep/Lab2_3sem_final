#include <random>
#include <string>
#include <ctime>
#include <tuple>

#include "Presenter.h"

void Presenter::createArr(int size) {
    this->size = size;
    int* tmp_arr = new int[size];
    for (int i = 0; i < size; i++)
        tmp_arr[i] = rand() % 100 + 1;

    arr = new ArraySequence<int>(tmp_arr, size);
}

string Presenter::getArr() {
    string res = "";
    for (int i = 0; i < this->size; i++)
        res += to_string(arr->get(i)) + " ";

    return res;
}

pair<string, bool> Presenter::find(string findType, string value) {
    clock_t start, end;
    string time;
    bool resBool;
    if (findType.empty() || value.empty() || arr->getLength() == 0)
        return make_pair("0", false);
    if (findType == "Bin Search") {
        Sort<int, ArraySequence<int>>::quickSort(arr);
        start = clock();
        resBool = BinSearh<int, ArraySequence<int>>::bin_Search(arr, stoi(value));
        end = clock();
        time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
        return make_pair(time, resBool);
    }
    if (findType == "Hash Table") {
        pair<int*, int> arrPair = arr->arrToIntArr();
        HashMap<int, int> hashTable(arr, arr -> getLength());
        //HashMap<int, int> hashTable(arrPair.first, arrPair.second);
        start = clock();
        resBool = hashTable.find(stoi(value));
        end = clock();
        time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
        return make_pair(time, resBool);
    }
    if (findType == "Bin Tree") {
        pair<int*, int> arrPair = arr->arrToIntArr();
        BinaryTree<int> tree(arrPair.first, arrPair.second);
        start = clock();
        resBool = tree.find(stoi(value));
        end = clock();
        time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
        return make_pair(time, resBool);
    }
}

string Presenter::findMostPopularExp(string spell) {
    unsigned cnt_spell = 0;
    string sub_spell;

    unsigned size = spell.size();
    for (unsigned i = 0; i < size; ++i) {
        for (unsigned j = 1; j <= size - i; ++j) {
            string sub = spell.substr(i, j);

            unsigned cnt = 0;
            for (unsigned k = i + 1; k <= size - sub.size(); ++k) {
                std::string::size_type n = spell.find(sub, k);
                if (n != string::npos) ++cnt;
            }

            if (cnt > cnt_spell) {
                sub_spell = sub;
                cnt_spell = cnt;
            }
            else if (cnt == cnt_spell && sub.size() > sub_spell.size()) {
                sub_spell = sub;
                cnt_spell = cnt;
            }
        }
    }
    return sub_spell;
}

void Presenter::createMat(int size) {
    matrix_size = size;
    matrix = new int* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
        matrix[i] = new int[matrix_size];

    for (int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            if (rand() % 10+1 < 8) // �������� 80% �������� ����� ����� ����
                matrix[i][j] = 0;
            else
                matrix[i][j] = rand() % 100 + 1;
}

string Presenter::getMat() {
    string res = "";
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++)
            res += to_string(matrix[i][j]) + " ";
        res += "\n";
    }

    return res;
}

string Presenter::processMat() {
    HashMap<int, string> hashTable;
    for (int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            if(matrix[i][j] != 0)
                hashTable.put(matrix[i][j], "Row: " + to_string(i) + " ,Col: " + to_string(j));

    string res = hashTable.getTable();
    return res;
}

string Presenter::getTestRes() {
    return startTests();
}

tuple<vector<double>, vector<double>, vector<double>> Presenter::getPointsForChart() {
    vector<double> binSearchVec, hashTableVec, binTreeVec;
    for(int i = 2; i < 10000; i++) {
        int* arr = new int[i];
        for (int j = 0; j < i; j++)
            arr[j] = rand() % 100 + 1;
        clock_t start, end;
        double time;
        int valueToFind = rand() % 100 + 1;

        //1
        ArraySequence<int> arrSeq(arr, i);
        Sort<int, ArraySequence<int>>::quickSort(&arrSeq);
        start = clock();
        //BinSearh<int, ArraySequence<int>>::bin_Search(&arrSeq, 10);
        end = clock();
        time = (double)(end - start) / (CLOCKS_PER_SEC / 1000);
        binSearchVec.push_back(time);

        //2
        HashMap<int, int> hashTable(arr, i);
        start = clock();
        hashTable.find(valueToFind);
        end = clock();
        time = (double)(end - start) / (CLOCKS_PER_SEC / 1000);
        hashTableVec.push_back(time);

        //3
        BinaryTree<int> tree(arr, i);
        start = clock();
        tree.find(valueToFind);
        end = clock();
        time = (double)(end - start) / (CLOCKS_PER_SEC / 1000);
        binTreeVec.push_back(time);
    }
    return make_tuple(binSearchVec, hashTableVec, binTreeVec);
}
