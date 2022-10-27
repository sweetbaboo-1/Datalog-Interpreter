//
// Created by Matthew on 7/15/2022.
//

#ifndef CS236_TUPLE_H
#define CS236_TUPLE_H
#include <string>
#include <vector>
#include "Header.h"
#include <sstream>
using namespace std;
class Tuple {

private:
    vector<string> values;

public:
    Tuple() { }
    Tuple(vector<string> values) : values(values) { }

    bool operator<(const Tuple t) const {
        return values < t.values;
    }

    // TODO: add more delegation functions as needed

    // This goes in your tuple class, note that tuple must include Header.h
    string toString(Header header) const {
        if (size() != header.size()) {
            throw "Failed in toString Tuple.h";
        }
        stringstream out;
        string sep = "";
        for (unsigned i = 0; i < size(); i++) {
            string name = header.at(i);
            string value = at(i);
            out << sep << name << "=" << value;
            sep = ", ";
        }
        return out.str();
    }
    unsigned int size() const {
        return values.size();
    }

    string at(unsigned int index) const {
        if (index >= size()) {
            throw "Failed at 'at' Tuple.h";
        }
        return values.at(index);
    }

    void push_back(string value) {
        values.push_back(value);
    }
};

#endif //CS236_TUPLE_H
