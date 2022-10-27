//
// Created by Matthew on 6/26/2022.
//

#ifndef CS236_LINECOMMENTAUTOMATON_H
#define CS236_LINECOMMENTAUTOMATON_H

//TODO: Check for \n and return UNDEFINED

#include "Automaton.h"
class LineCommentAutomaton : public Automaton {
public:
    LineCommentAutomaton() {
        type = TokenType::LINE_COMMENT; // set the type
    }
private:
    void s0() {
        if (match('#')) {
            next();
            s1();
        }
        else
            sError(); // this calls the error state
    }
    void s1() {
        if (match('|'))
            sError();
        else {
            next();
            s2();
        }
    }
    void s2() {
        if (getNewLines() > 0) {
            //this->numCharRead--; // cuts off the \r\n TODO: check that this works on the pass off machine
            return;
        }
        else {
            next();
            s2();
        }


    }
};
#endif //CS236_LINECOMMENTAUTOMATON_H
