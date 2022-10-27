//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_SCHEMESAUTOMATON_H
#define CS236_SCHEMESAUTOMATON_H

#include "Automaton.h"
class SchemesAutomaton : public Automaton {
public:
    SchemesAutomaton() {
        type = TokenType::SCHEMES; // set the type
    }
private:
    void s0() {
        if (match('S')) {
            next();
            s1();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s1() {
        if (match('c')) {
            next();
            s2();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s2() {
        if (match('h')) {
            next();
            s3();
        } else {
            sError(); // this calls the error state
        }
    }
    void s3() {
        if (match('e')) {
            next();
            s4();
        } else {
            sError(); // this calls the error state
        }
    }
    void s4() {
        if (match('m')) {
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

#endif //CS236_SCHEMESAUTOMATON_H
