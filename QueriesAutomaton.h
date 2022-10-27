//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_QUERIESAUTOMATON_H
#define CS236_QUERIESAUTOMATON_H

#include "Automaton.h"
class QueriesAutomaton : public Automaton {
public:
    QueriesAutomaton() {
        type = TokenType::QUERIES; // set the type
    }
private:
    void s0() {
        if (match('Q')) {
            next();
            s1();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s1() {
        if (match('u')) {
            next();
            s2();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s2() {
        if (match('e')) {
            next();
            s3();
        } else {
            sError(); // this calls the error state
        }
    }
    void s3() {
        if (match('r')) {
            next();
            s4();
        } else {
            sError(); // this calls the error state
        }
    }
    void s4() {
        if (match('i')) {
            next();
            s5();
        } else {
            sError(); // this calls the error state
        }
    }
    void s5() {
        if (match('e')) {
            next();
            s6();
        } else {
            sError();
        }
    }
    void s6() {
        if (match('s')) {
            next();
            return;
        } else {
            sError();
        }
    }
};

#endif //CS236_QUERIESAUTOMATON_H
