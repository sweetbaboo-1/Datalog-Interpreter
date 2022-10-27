//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_QUESTIONMARKAUTOMATON_H
#define CS236_QUESTIONMARKAUTOMATON_H

#include "Automaton.h"
class QuestionMarkAutomaton : public Automaton {
public:
    QuestionMarkAutomaton() {
        type = TokenType::Q_MARK; // set the type
    }
private:
    void s0() {
        if (match('?')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError(); // this calls the error state
        }
    }
};

#endif //CS236_QUESTIONMARKAUTOMATON_H
