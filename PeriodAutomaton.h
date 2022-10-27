//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_PERIODAUTOMATON_H
#define CS236_PERIODAUTOMATON_H
#include "Automaton.h"
class PeriodAutomaton : public Automaton {
public:
    PeriodAutomaton() {
        type = TokenType::PERIOD; // set the type
    }
private:
    void s0() {
        if (match('.')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};
#endif //CS236_PERIODAUTOMATON_H
