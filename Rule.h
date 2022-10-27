//
// Created by Matthew on 7/7/2022.
//

#ifndef CS236_RULE_H
#define CS236_RULE_H

#include "Predicate.h"

class Rule {
private:
    Predicate head;
    vector<Predicate> body;
    bool selfDependent;
public:
    Rule() {}

    Predicate getHead() const {
        return head;
    }

    void setHead(const Predicate &head) {
        Rule::head = head;
    }

    const vector<Predicate> & getBody() const {
        return body;
    }

    void setBody(const vector<Predicate> &body) {
        Rule::body = body;
    }

    bool isSelfDependent() {
        return selfDependent;
    }

    void setSelfDependent() {
        Rule::selfDependent = true;
    }

    void addPredicate(Predicate predicate) {
        body.push_back(predicate);
    }

    string toString() {
        stringstream str;
        string sep = "";
        str << head.toString() << " :- ";
        for (int i = body.size() - 1; i >= 0; i--) {
            str << sep << body[i].toString();
            sep = ",";
        }
        str << ".";
        return str.str();
    }
};

#endif //CS236_RULE_H
