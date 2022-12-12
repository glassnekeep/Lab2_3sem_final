#include <random>
#include <ctime>
#include <tuple>
#include <fstream>

#include "Presenter.h"

void Presenter::createArr(int size) {
    this->size = size;
    int* tmp_arr = new int[size];
    for (int i = 0; i < size; i++)
        tmp_arr[i] = rand() % 100 + 1;
    arr = new ArraySequence<int>(tmp_arr, size);
}

void Presenter::readArrayFromFile() {
    ifstream file("C:\\Users\\-\\CLionProjects\\Lab2_3sem_final\\Entry1.txt");
    int count;
    if (file.is_open()) {
        string s;
        getline(file, s);
        count = atoi(const_cast<char*>(s.c_str()));
    }
    personArrayLength = count;
    string str;
    arrayFromFile = new Person[count];
    if (file.is_open()) {
        for (int i = 0; i < count; ++i) {
            //getline(file, str);
            int id;
            string firstname;
            string lastname;
            string ptr;
//            ptr = strtok(const_cast<char*>(str.c_str()), "\0");
//            id = atoi(ptr);
//            ptr = strtok(const_cast<char*>(str.c_str()), " ");
//            firstname = ptr;
//            ptr = strtok(const_cast<char*>(str.c_str()), "\n");
//            lastname = ptr;
            getline(file, ptr);
            id = atoi(const_cast<char*>(ptr.c_str()));
            getline(file, ptr);
            firstname = ptr;
            getline(file, ptr);
            lastname = ptr;
            Person person = {
                    id,
                    firstname,
                    lastname
            };
            arrayFromFile[i] = person;
        }
    }
}

string Presenter::getArr() {
    string res = "";
    for (int i = 0; i < this->size; i++)
        res += to_string(arr->get(i)) + " ";

    return res;
}

pair<string, bool> Presenter::find(string findType, string value, string type) {
    clock_t start, end;
    string time;
    bool resBool;
    //if (findType.empty() || value.empty() || (arr->getLength() == 0 && type != "Person"))
    if (findType.empty() || value.empty())
        return make_pair("0", false);
    if (findType == "Bin Search") {
        Sort<int, ArraySequence<int>>::quickSort(arr);
        start = clock();
        resBool = BinSearch<int, ArraySequence<int>>::bin_Search(arr, stoi(value));
        end = clock();
        time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
        return make_pair(time, resBool);
    }
    if (findType == "Hash Table") {
        if (type == "Person") {
            readArrayFromFile();
            auto* hashMap = new HashMap<int, Person>();
            for (int i = 0; i < personArrayLength; ++i) {
                hashMap -> put(arrayFromFile[i].id, arrayFromFile[i]);
            }
            char *ptr = strtok(const_cast<char*>(value.c_str()), " ");
            int id = atoi(ptr);
            ptr = strtok(const_cast<char*>(value.c_str()), " ");
            string firstname = ptr;
            ptr = strtok(const_cast<char*>(value.c_str()), " ");
            string lastname = ptr;
            Person person = {
                    id,
                    firstname,
                    lastname
            };
            start = clock();
            resBool = hashMap -> find(id);
            end = clock();
            time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
            return make_pair(time, resBool);
        } else {
            pair<int*, int> arrPair = arr->arrToIntArr();
            HashMap<int, int> hashTable(arr, arr -> getLength());
            //HashMap<int, int> hashTable(arrPair.first, arrPair.second);
            start = clock();
            resBool = hashTable.find(stoi(value));
            end = clock();
            time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
            return make_pair(time, resBool);
        }
    }
    if (findType == "Bin Tree") {
        pair<int*, int> arrPair = arr->arrToIntArr();
        int* list = arrPair.first;
        Tree<int> tree(arr, arrPair.second);
        start = clock();
        resBool = tree.Search(stoi(value));
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
            if (rand() % 10+1 < 8)
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

void Presenter::processMat() {
    HashMap<int, string> hashTable;
    for (int i = 0; i < matrix_size; i++)
        for (int j = 0; j < matrix_size; j++)
            if(matrix[i][j] != 0)
                hashTable.put(matrix[i][j], "Row: " + to_string(i) + " ,Col: " + to_string(j));
    //string res = hashTable.getTable();
    //hashTable.getTable();
    //return res;
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

//        //3
//        Tree<int> tree(arr, i);
//        start = clock();
//        tree.find(valueToFind);
//        end = clock();
//        time = (double)(end - start) / (CLOCKS_PER_SEC / 1000);
//        binTreeVec.push_back(time);
    }
    return make_tuple(binSearchVec, hashTableVec, binTreeVec);
}
