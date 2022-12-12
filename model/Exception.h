//
// Created by - on 12.12.2022.
//

#ifndef LAB2_3SEM_FINAL_EXCEPTION_H
#define LAB2_3SEM_FINAL_EXCEPTION_H

#include "iostream"
#include "exception"
#include "string"
using namespace std;

enum Error {
    INDEX_OUT_OF_RANGE=1,
    NULL_POINTER=2,
    NEGATIVE_SIZE = 3,
};


class Exception:public exception {
public:
    string msg;
    Error number;
    explicit Exception(int code) {
        if (code == 1) {
            msg = "List index out of range";
            number = ::INDEX_OUT_OF_RANGE;
        }
        if (code == 2) {
            msg = "Pointer in NULL";
            number = ::NULL_POINTER;
        }
        if (code == 3) {
            msg = "Size under zero";
            number = ::NEGATIVE_SIZE;
        }
    };

    void show() const {
        cout << msg << endl;
    }
};

#endif //LAB2_3SEM_FINAL_EXCEPTION_H
