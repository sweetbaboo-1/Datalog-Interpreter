//
// Created by Matthew on 7/15/2022.
//

#ifndef CS236_HEADER_H
#define CS236_HEADER_H
#include <string>
#include <vector>
using namespace std;
class Header {

private:
    vector<string> attributes;

public:
    Header() { }
    Header(vector<string> attributes) : attributes(attributes) { }

    unsigned int size() const {
        return attributes.size();
    }

    string at(unsigned int index) const {
        if (index >= size()) {
            throw "Failed at 'at' Header.h";
        }
        return attributes.at(index);
    }

    void push_back(string value) {
        attributes.push_back(value);
    }

    const vector<string> &getAttributes() const {
        return attributes;
    }
};

#endif //CS236_HEADER_H
