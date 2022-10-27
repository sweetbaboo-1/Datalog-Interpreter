//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_COMMAAUTOMATON_H
#define CS236_COMMAAUTOMATON_H

#include "Automaton.h"
class CommaAutomaton : public Automaton {
public:
    CommaAutomaton() {
        type = TokenType::COMMA; // set the type
    }
private:
    void s0() {
        if (match(',')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_COMMAAUTOMATON_H
