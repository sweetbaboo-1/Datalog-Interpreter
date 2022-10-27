//
// Created by Matthew on 6/25/2022.
//

#ifndef CS236_EOFAUTOMATON_H
#define CS236_EOFAUTOMATON_H

#include "Automaton.h"
class EOFAutomaton : public Automaton {
public:
    EOFAutomaton() {
        type = TokenType::END_OF_FILE; // set the type
    }
private:
    void s0() {
        return;
//        if (endOfFile()) {
//            cout << "end of file";
//            return; // this represents accepting the input
//        }
//        else {
//            sError(); // this calls the error state
//        }
    }
};

#endif //CS236_EOFAUTOMATON_H
