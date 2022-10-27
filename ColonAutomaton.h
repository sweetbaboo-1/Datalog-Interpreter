//
// Created by Matthew on 6/24/2022.
//

#ifndef CS236_COLONAUTOMATON_H
#define CS236_COLONAUTOMATON_H
#include "Automaton.h"
class ColonAutomaton : public Automaton {
public:
    ColonAutomaton() {
        type = TokenType::COLON; // set the type
    }
private:
    void s0() {
        if (match(':')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};
#endif //CS236_COLONAUTOMATON_H
