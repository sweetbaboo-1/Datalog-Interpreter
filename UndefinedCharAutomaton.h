//
// Created by Matthew on 6/24/2022.
//

#ifndef CS236_UNDEFINEDCHARAUTOMATON_H
#define CS236_UNDEFINEDCHARAUTOMATON_H
#include "Automaton.h"
class UndefinedCharAutomaton : public Automaton {
public:
    UndefinedCharAutomaton() {
        type = TokenType::UNDEFINED; // set the type
    }
private:
    void s0() {
        next(); // read next character
        return; // accept the input
    }
};
#endif //CS236_UNDEFINEDCHARAUTOMATON_H
