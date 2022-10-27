//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_FACTSAUTOMATON_H
#define CS236_FACTSAUTOMATON_H
#include "Automaton.h"

class FactsAutomaton : public Automaton {
public:
    FactsAutomaton() {
        type = TokenType::FACTS; // set the type
    }
private:
    void s0() {
        if (match('F')) {
            next();
            s1();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s1() {
        if (match('a')) {
            next();
            s2();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s2() {
        if (match('c')) {
            next();
            s3();
        } else {
            sError(); // this calls the error state
        }
    }
    void s3() {
        if (match('t')) {
            next();
            s4();
        } else {
            sError(); // this calls the error state
        }
    }
    void s4() {
        if (match('s')) {
            next();
            return; // success
        } else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_FACTSAUTOMATON_H
