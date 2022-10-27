//
// Created by Matthew on 7/7/2022.
//

#ifndef CS236_PARAMETER_H
#define CS236_PARAMETER_H

#include <string>

using namespace std;

class Parameter {
private:
    string value;

public:
    Parameter() = default;

    const string &getValue() const {
        return value;
    }

    void setValue(const string &value) {
        Parameter::value = value;
    }

    string toString() {
        return value;
    }

    bool isConst() const {
        if (value[0] == '\'')
            return true;
        return false;
    }

};

#endif //CS236_PARAMETER_H
