//#pragma once
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <string>
//#include <exception>
//#include "IMap.h"
//
//#define CAPACITY 10000
//
//template <class T>
//class HashTable {
//private:
//    struct Ht_item {
//        char* key;
//        char* value;
//    };
//
//    struct LinkedList {
//        Ht_item* item;
//        LinkedList* next;
//    };
//
//    struct Hash_Table {
//        Ht_item** items;
//        LinkedList** overflow_buckets;
//        int size;
//        int count;
//    };
//
//    Hash_Table* ht;
//
//    unsigned long hash_function(char* str) {
//        unsigned long i = 0;
//        for (int j = 0; str[j]; j++)
//            i += str[j];
//        return i % CAPACITY;
//    }
//
//    static LinkedList* allocate_list() {
//        LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
//        return list;
//    }
//
//    static LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item) {
//        if (!list) {
//            LinkedList* head = allocate_list();
//            head->item = item;
//            head->next = nullptr;
//            list = head;
//            return list;
//        }
//
//        else if (list->next == nullptr) {
//            LinkedList* node = allocate_list();
//            node->item = item;
//            node->next = nullptr;
//            list->next = node;
//            return list;
//        }
//
//        LinkedList* temp = list;
//
//        //while (temp->next)
//        //    temp = temp->next;
//
//        LinkedList* node = allocate_list();
//        node->item = item;
//        node->next = nullptr;
//        temp->next = node;
//
//        return list;
//    }
//
//    static Ht_item* linkedlist_remove(LinkedList* list) {
//        if (!list)
//            return nullptr;
//        if (!list->next)
//            return nullptr;
//        LinkedList* node = list->next;
//        LinkedList* temp = list;
//        temp->next = nullptr;
//        list = node;
//        Ht_item* it = nullptr;
//        memcpy(temp->item, it, sizeof(Ht_item));
//        free(temp->item->key);
//        free(temp->item->value);
//        free(temp->item);
//        free(temp);
//        return it;
//    }
//
//    static LinkedList** create_overflow_buckets(Hash_Table* table) {
//        LinkedList** buckets = (LinkedList**)calloc(table->size, sizeof(LinkedList*));
//        for (int i = 0; i < table->size; i++)
//            buckets[i] = nullptr;
//        return buckets;
//    }
//
//    static void free_overflow_buckets(Hash_Table* table) {
//        LinkedList** buckets = table->overflow_buckets;
//        free(buckets);
//    }
//
//    Ht_item* create_item(char* key, char* value) {
//        Ht_item* item = (Ht_item*)malloc(sizeof(Ht_item));
//        item->key = (char*)malloc(strlen(key) + 1);
//        item->value = (char*)malloc(strlen(value) + 1);
//
//        strcpy(item->key, key);
//        strcpy(item->value, value);
//
//        return item;
//    }
//
//    void free_item(Ht_item* item) {
//        //������������
//    }
//
//    void free_table(Hash_Table* table) {
//        for (int i = 0; i < table->size; i++) {
//            Ht_item* item = table->items[i];
//            if (item != nullptr)
//                free_item(item);
//        }
//
//        free_overflow_buckets(table);
//        free(table->items);
//        free(table);
//    }
//
//    void handle_collision(Hash_Table* table, unsigned long index, Ht_item* item) {
//        LinkedList* head = table->overflow_buckets[index];
//
//        if (head == NULL) {
//            // We need to create the list
//            head = allocate_list();
//            head->item = item;
//            table->overflow_buckets[index] = head;
//            return;
//        }
//        else {
//            // Insert to the list
//            table->overflow_buckets[index] = linkedlist_insert(head, item);
//            return;
//        }
//    }
//
//    void ht_insert(Hash_Table* table, char* key, char* value) {
//        Ht_item* item = create_item(key, value);
//
//        unsigned long index = hash_function(key);
//
//        Ht_item* current_item = table->items[index];
//
//        if (current_item == nullptr) {
//            if (table->count == table->size) {
//                printf("Insert Error: Hash Table is full\n");
//                free_item(item);
//                return;
//            }
//
//            table->items[index] = item;
//            table->count++;
//        }
//
//        else {
//            if (strcmp(current_item->key, key) == 0) {
//                strcpy(table->items[index]->value, value);
//                return;
//            }
//
//            else {
//                handle_collision(table, index, item);
//                return;
//            }
//        }
//    }
//
//    char* ht_search(Hash_Table* table, char* key) {
//        int index = hash_function(key);
//        Ht_item* item = table->items[index];
//        LinkedList* head = table->overflow_buckets[index];
//
//        while (item != NULL) {
//            if (strcmp(item->key, key) == 0)
//                return item->value;
//            if (head == NULL)
//                return NULL;
//            item = head->item;
//            head = head->next;
//        }
//        return NULL;
//    }
//
//    void ht_delete(Hash_Table* table, char* key) {
//        // Deletes an item from the table
//        int index = hash_function(key);
//        Ht_item* item = table->items[index];
//        LinkedList* head = table->overflow_buckets[index];
//
//        if (item == NULL) {
//            // Does not exist. Return
//            return;
//        }
//        else {
//            if (head == NULL && strcmp(item->key, key) == 0) {
//                // No collision chain. Remove the item
//                // and set table index to NULL
//                table->items[index] = NULL;
//                free_item(item);
//                table->count--;
//                return;
//            }
//            else if (head != NULL) {
//                // Collision Chain exists
//                if (strcmp(item->key, key) == 0) {
//                    // Remove this item and set the head of the list
//                    // as the new item
//
//                    free_item(item);
//                    LinkedList* node = head;
//                    head = head->next;
//                    node->next = NULL;
//                    table->items[index] = create_item(node->item->key, node->item->value);
//                    free_linkedlist(node);
//                    table->overflow_buckets[index] = head;
//                    return;
//                }
//
//                LinkedList* curr = head;
//                LinkedList* prev = NULL;
//
//                while (curr) {
//                    if (strcmp(curr->item->key, key) == 0) {
//                        if (prev == NULL) {
//                            // First element of the chain. Remove the chain
//                            free_linkedlist(head);
//                            table->overflow_buckets[index] = NULL;
//                            return;
//                        }
//                        else {
//                            // This is somewhere in the chain
//                            prev->next = curr->next;
//                            curr->next = NULL;
//                            free_linkedlist(curr);
//                            table->overflow_buckets[index] = head;
//                            return;
//                        }
//                    }
//                    curr = curr->next;
//                    prev = curr;
//                }
//
//            }
//        }
//    }
//
//    void print_search(Hash_Table* table, char* key) {
//        char* val;
//        if ((val = ht_search(table, key)) == nullptr) {
//            printf("%s does not exist\n", key);
//            return;
//        }
//        else {
//            printf("Key:%s, Value:%s\n", key, val);
//        }
//    }
//
//    void print_table(Hash_Table* table) {
//        printf("\n-------------------\n");
//        for (int i = 0; i < table->size; i++) {
//            if (table->items[i]) {
//                printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->value);
//                if (table->overflow_buckets[i]) {
//                    printf(" => Overflow Bucket => ");
//                    LinkedList* head = table->overflow_buckets[i];
//                    while (head) {
//                        printf("Key:%s, Value:%s ", head->item->key, head->item->value);
//                        head = head->next;
//                    }
//                }
//                printf("\n");
//            }
//        }
//        printf("-------------------\n");
//    }
//
//    char* intToStr(int data) {
//        string strData = to_string(data);
//
//        char* temp = new char[strData.length() + 1];
//        strcpy(temp, strData.c_str());
//
//        return temp;
//    }
//
//    char* stringToStr(string strData) {
//        char* temp = new char[strData.length() + 1];
//        strcpy(temp, strData.c_str());
//
//        return temp;
//    }
//public:
//    HashTable() {
//        Hash_Table* table = (Hash_Table*)malloc(sizeof(Hash_Table));
//        table->size = CAPACITY;
//        table->count = 0;
//        table->items = (Ht_item**)calloc(table->size, sizeof(Ht_item*));
//        for (int i = 0; i < table->size; i++)
//            table->items[i] = nullptr;
//        table->overflow_buckets = create_overflow_buckets(table);
//
//        ht = table;
//    }
//
//    HashTable(int* arr, int size) {
//        Hash_Table* table = (Hash_Table*)malloc(sizeof(Hash_Table));
//        table->size = CAPACITY;
//        table->count = 0;
//        table->items = (Ht_item**)calloc(table->size, sizeof(Ht_item*));
//        for (int i = 0; i < table->size; i++)
//            table->items[i] = nullptr;
//        table->overflow_buckets = create_overflow_buckets(table);
//
//        ht = table;
//
//        for (int i = 0; i < size; i++)
//            ht_insert(ht, intToStr(arr[i]), intToStr(i));
//    }
//
//    ~HashTable() {
//        free_table(ht);
//    }
//
//    void add(string key, string value) {
//        ht_insert(ht, stringToStr(key), stringToStr(value));
//    }
//
//    bool find(string key) {
//        char* val;
//        if ((val = ht_search(ht, stringToStr(key))) == NULL)
//            return false;
//        return true;
//    }
//
//    string getTable() {
//        string Myres = "";
//        for (int i = 0; i < ht->size; i++) {
//            if (ht->items[i]) {
//                int flag = 1;
//                string s3 = ht->items[i]->key;
//                string s4 = ht->items[i]->value;
//                Myres += to_string(flag) + ") Key: \n" + s4 + " Value: " + s3 + "\n";
//                flag++;
//                if (ht->overflow_buckets[i]) {
//                    LinkedList* head = ht->overflow_buckets[i];
//                    while (head) {
//                        string s1 = head->item->key;
//                        string s2 = head->item->value;
//                        Myres += "Key: " + s1 + " Value: " + s2;
//                        head = head->next;
//                    }
//                }
//                Myres += "\n";
//            }
//        }
//
//        return Myres;
//    }
//};