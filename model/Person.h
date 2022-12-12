//
// Created by - on 11.12.2022.
//

#ifndef LAB2_3SEM_FINAL_PERSON_H
#define LAB2_3SEM_FINAL_PERSON_H

#include <iostream>
#include <string>

using namespace std;

struct Person {
    int id;
    string firstName;
    string lastName;

    bool operator == (const Person& person) const {
        return person.id == this -> id && person.firstName == this -> firstName && person.lastName == this -> lastName;
    }
};

template <>
struct hash<Person> {
    size_t operator()(const Person& person) const {
        size_t result = 0;
        result = 31 * result + hash<int>{}(person.id);
        result = 31 * result + hash<string>{}(person.firstName);
        result = 31 * result + hash<string>{}(person.lastName);
        return result;
    }
};

//std::string to_string(const Person& person) {
//    return "Person: id = " + to_string(person.id) + ", firstname = " + person.firstName + ", lastname = " + person.lastName;
//}

std::ostream& operator << (std::ostream& o, const Person& person) {
    o << "Person: id = " << person.id << ", firstname = " << person.firstName << ", lastname = " << person.lastName << std::endl;
    return o;
}

#endif //LAB2_3SEM_FINAL_PERSON_H
