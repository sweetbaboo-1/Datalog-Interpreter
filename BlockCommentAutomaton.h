//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_BLOCKCOMMENTAUTOMATON_H
#define CS236_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"
class BlockCommentAutomaton : public Automaton {
public:
    BlockCommentAutomaton() {
        type = TokenType::COMMENT; // set the type
    }
private:
    void s0() {
        if (match('#')) {
            next();
            s1();
        }
        else {
            sError(); // this calls the error state
        }
    }
    void s1() {
        if (match('|')) {
            next();
            s2();
        }
        else {
            sError();
        }
    }
    void s2() {
        if (!match('|')) {
            next();
            if(endOfFile()) {
                type = TokenType::UNDEFINED;
                return;
            }
            s2();
        }
        else {
            next();
            s3();
        }
    }
    void s3() {
        if (!match('#')) {
            next();
            s2();
        }
        else {
            next();
            return;
        }
    }
};
#endif //CS236_BLOCKCOMMENTAUTOMATON_H
