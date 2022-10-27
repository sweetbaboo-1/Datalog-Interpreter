//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_MULTIPLYAUTOMATON_H
#define CS236_MULTIPLYAUTOMATON_H

#include "Automaton.h"
class MultiplyAutomaton : public Automaton {
public:
    MultiplyAutomaton() {
        type = TokenType::MULTIPLY; // set the type
    }
private:
    void s0() {
        if (match('*')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_MULTIPLYAUTOMATON_H
