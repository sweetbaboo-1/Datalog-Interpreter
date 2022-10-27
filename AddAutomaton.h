//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_ADDAUTOMATON_H
#define CS236_ADDAUTOMATON_H

#include "Automaton.h"
class AddAutomaton : public Automaton {
public:
    AddAutomaton() {
        type = TokenType::ADD; // set the type
    }
private:
    void s0() {
        if (match('+')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_ADDAUTOMATON_H
