//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_RIGHTPARENTHESISAUTOMATON_H
#define CS236_RIGHTPARENTHESISAUTOMATON_H

#include "Automaton.h"
class RightParenthesisAutomaton : public Automaton {
public:
    RightParenthesisAutomaton() {
        type = TokenType::RIGHT_PAREN; // set the type
    }
private:
    void s0() {
        if (match(')')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_RIGHTPARENTHESISAUTOMATON_H
