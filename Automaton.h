//
// Created by Matthew on 6/24/2022.
//

#ifndef CS236_AUTOMATON_H
#define CS236_AUTOMATON_H

#include <string>
#include "Token.h"

class Automaton {
protected:
    // This tracks where in the input we are
    unsigned int currCharIndex = 0;

    // This tracks the number of newLines ('\n') we have read
    unsigned int newLinesRead = 0;

    TokenType type = TokenType::UNDEFINED;
    // This tracks the total number of characters consumed
    // This is different from currCharIndex to let you "peek" at the next input without consuming it
    unsigned int numCharRead = 0;
    std::string input = "";

    // All children of this class must define this function
    virtual void s0() = 0;

    // Helper functions
    void next() {
        if (curr() == '\n') {
            newLinesRead++;
        }
        numCharRead++;
        currCharIndex++;
    }

    char curr() {
        if (endOfFile()) {
            throw "Tried to read past the file, does your automaton state check for it as a transition?";
        }
        return input.at(currCharIndex);
    }

    bool match(char c) {
        if (endOfFile()) {
            cout << "Tried to read past the file, does your automaton state check for it as a transition?";
            throw "Tried to read past the file, does your automaton state check for it as a transition?";
        }
        return (curr() == c);
    }

    // Call this function to check if you have reached the end of file
    bool endOfFile() {
        return (currCharIndex >= input.size());
    }

    // This is the error state call it when the token is invalid
    void sError() {
        numCharRead = 0;
    }

public:
    Automaton() {}

    unsigned int run(std::string input) {
        this->input = input;
        currCharIndex = 0;
        newLinesRead = 0;
        numCharRead = 0;
        s0();
        return numCharRead;
    }

    unsigned int getNewLines() const {
        return newLinesRead;
    }

    TokenType getType() const {
        return type;
    }
};

#endif //CS236_AUTOMATON_H
