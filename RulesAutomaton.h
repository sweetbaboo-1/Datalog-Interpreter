//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_RULESAUTOMATON_H
#define CS236_RULESAUTOMATON_H

#include "Automaton.h"
class RulesAutomaton : public Automaton {
public:
    RulesAutomaton() {
        type = TokenType::RULES; // set the type
    }
private:
    void s0() {
        if (match('R')) {
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
        if (match('l')) {
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
        if (match('s')) {
            next();
            return;
        } else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_RULESAUTOMATON_H
