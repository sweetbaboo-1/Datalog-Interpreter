//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_LEFTPARENTHESISAUTOMATON_H
#define CS236_LEFTPARENTHESISAUTOMATON_H

#include "Automaton.h"
class LeftParenthesisAutomaton : public Automaton {
public:
    LeftParenthesisAutomaton() {
        type = TokenType::LEFT_PAREN; // set the type
    }
private:
    void s0() {
        if (match('(')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_LEFTPARENTHESISAUTOMATON_H
