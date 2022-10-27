//
// Created by Matthew on 7/7/2022.
//

#ifndef CS236_PREDICATE_H
#define CS236_PREDICATE_H

#include <string>
#include <vector>
#include <sstream>
#include "Parameter.h"

using namespace std;
class Predicate {
private:
    vector<Parameter> parameters;
    string name;
public:
    Predicate() {}
    // setters
    void setName(string newName) {
        name = newName;
    }
    void setParameters(vector<Parameter> newParameters) {
        parameters = newParameters;
    }

    // getters
    string getName() const {
        return name;
    }
    vector<Parameter> getParameters() const {
        return parameters;
    }

    // adder
    void addParameter(Parameter parameter) {
        parameters.push_back(parameter);
    }

    //helper function
    void addParameter(string parameterValue) {
        Parameter parameter;
        parameter.setValue(parameterValue);
        parameters.push_back(parameter);
    }

    // toString
    string toString() {
        string sep = "";
        stringstream out;
        out << name << "(";
        for (Parameter currParam : parameters) {
            out << sep << currParam.toString();
            sep = ",";
        }
        out << ")";
        return out.str();
    }
};

#endif //CS236_PREDICATE_H
