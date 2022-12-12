//
// Created by - on 28.11.2022.
//

#ifndef MEPHI_LAB2_3SEM_IMAP_H
#define MEPHI_LAB2_3SEM_IMAP_H

#include <iostream>

using namespace std;

template <typename K, typename V>
class IMap {
public:
    IMap() = default;
    //virtual bool get(const K& key, V& value) = 0;
    //get по ключу
    //virtual void put(const V& value) = 0;
    virtual V get(const K& key) = 0;
    virtual void put(const K& key, const V& value) = 0;
    virtual void remove(const K& key) = 0;
    virtual bool find(const K& key) = 0;
    //Поиск по значению
    virtual void getTable() = 0;
private:
};
#endif //MEPHI_LAB2_3SEM_IMAP_H
