//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_STRINGAUTOMATON_H
#define CS236_STRINGAUTOMATON_H
#include "Automaton.h"

class StringAutomaton : public Automaton {
public:
    StringAutomaton() {
        type = TokenType::STRING; // set the type
    }
private:
    void s0() {
        if (match('\'')) {
            next();
            s1();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s1() {
        if (endOfFile()) {
            type = TokenType::UNDEFINED;
            return;
        }
        if (!match('\'')) {
            next();
            if (endOfFile()) {
                type = TokenType::UNDEFINED;
                return;
            }
            s1();
        }
        else {
            next();
            s2();
        }
    }
    void s2() {
        if (match('\'')) {
            next();
            s3();
        }
        else {
            //next();//this was commented out?
            return;
        }
    }
    void s3() {
        if (match('\'')) {
            next();
            s2();
        }
        else {
            next();
            s1();
        }
    }
};
#endif //CS236_STRINGAUTOMATON_H
