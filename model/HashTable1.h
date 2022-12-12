//
// Created by - on 08.12.2022.
//

#ifndef LAB2_3SEM_FINAL_HASHTABLE1_H
#define LAB2_3SEM_FINAL_HASHTABLE1_H
#include <iostream>
#include "IMap.h"
#include "array/Sequence.h"
#include <string>
#include "Exception.h"
#include "Person.h"

#define LOAD_FACTOR  0.75
// поменять на 0.75
//брать капасити как простые числа

using namespace std;

template <typename K, typename V>
class HashNode {
public:
    HashNode(const K &key, const V &value) :
            key(key), value(value), next(NULL) {
    }
    K getKey() const {
        return key;
    }
    V getValue() const {
        return value;
    }
    void setValue(V value) {
        HashNode::value = value;
    }
    HashNode *getNext() const {
        return next;
    }
    void setNext(HashNode *next) {
        HashNode::next = next;
    }
private:
    K key;
    V value;
    HashNode *next;
};

template <typename K, typename V/*, typename F = KeyHash<K>*/>
class HashMap : public IMap<K, V> {
public:
    HashMap() {
        table = new HashNode<K, V> *[capacity]();
    }
    HashMap(V* arr, int count) {
        //size = count;
        size = 0;
        capacity = (count / 10) * 16;
        table = new HashNode<K, V> * [capacity]();
        for (int i = 0; i < count; i++) {
            put((arr[i]), arr[i]);
        }
    }
    HashMap(Sequence<V>* sequence, int count) {
        capacity = count;
        table = new HashNode<V, V> * [capacity]();
        for (int i = 0; i < count; i++) {
            put(sequence -> get(i), sequence -> get(i));

        }
    }

    ~HashMap() {
        for (int i = 0; i < size; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != NULL) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
        delete [] table;
    }



//    bool get(const K &key, V &value) override {
//        unsigned long hashValue = hashFunc(key);
//        HashNode<K, V> *entry = table[hashValue];
//        while (entry != NULL) {
//            if (entry->getKey() == key) {
//                value = entry->getValue();
//                return true;
//            }
//            entry = entry->getNext();
//        }
//        return false;
//    }

    V get(const K& key) override {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];
        while (entry != nullptr) {
            if (entry -> getKey() == key) {
                return entry -> getValue();
            }
            entry = entry -> getNext();
        }
        throw Exception(2);
    }

    void put(const K &key, const V &value) override {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];
        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == NULL) {
            entry = new HashNode<K, V>(key, value);
            if (prev == NULL) {
                table[hashValue] = entry;
                size++;
                if (size * LOAD_FACTOR > capacity) {
                    capacity *= 2;
                    HashNode<K, V>** oldTable = table;
                    table = new HashNode<K, V>* [capacity]();
                    for (int i = 0; i < capacity; i++) {
                        //int newFunc = hashFunc(oldTable[i] -> getKey());
                        put(oldTable[i] -> getKey(), oldTable[i] -> getValue());
                    }
                    delete oldTable;
                }
            } else {
                prev->setNext(entry);
            }
        } else {
            entry->setValue(value);
            size++;
            if (size * LOAD_FACTOR > capacity) {
                capacity *= 2;
                HashNode<K, V>** oldTable = table;
                table = new HashNode<K, V>* [capacity]();
                for (int i = 0; i < size; i++) {
                    int newFunc = oldTable[i] -> getKey();
                    put(newFunc, oldTable[i] -> getValue());
                }
                delete oldTable;
            }
        }
    }

    void remove(const K &key) override {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];
        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == NULL) {
            return;
        }
        else {
            if (prev == NULL) {
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
            size--;
        }
    }

    bool find(const K& key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];
        while (entry != NULL) {
            if (entry->getKey() == key) {
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    string print() {
        string result;
        for (int i = 0; i < capacity; i++) {
            if (table[i]) {
                result += " key: " + to_string(table[i] -> getKey()) + ", value: " + table[i] -> getValue() + "\n";
            }
        }
        return result;
    }

//    void getTable() {
//        string Myres;
//        for (int i = 0; i < size; i++) {
//            if (table[i]) {
////                int flag = 1;
////                string s3 = to_string(table[i] -> getKey());
////                string s4 = to_string(table[i] -> getValue());
////                Myres += to_string(flag) + ") Key: \n" + s4 + " Value: " + s3 + "\n";
////                flag++;
////                Myres += "\n";
//                cout << "key = " << (table[i] -> getKey()) << ", value = " << (table[i] -> getValue()) << endl;
//            }
//        }
////        return Myres;
//    }


private:
    HashNode<K, V> **table;
    int hashFunc(K key) {
        return hash<K>()(key) % capacity;
    };
    int capacity = 16;
    int size = 0;
};
#endif //LAB2_3SEM_FINAL_HASHTABLE1_H
