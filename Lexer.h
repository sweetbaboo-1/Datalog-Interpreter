//
// Created by Matthew on 6/24/2022.
//

#ifndef CS236_LEXER_H
#define CS236_LEXER_H

#include <vector>
#include "Token.h"
#include "Automaton.h"
#include <iostream>
#include "IDAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "UndefinedCharAutomaton.h"
#include "CommaAutomaton.h"
#include "AddAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "LineCommentAutomaton.h"
//#include "EOFAutomaton.h"
#include "FactsAutomaton.h"
#include "LeftParenthesisAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "QueriesAutomaton.h"
#include "StringAutomaton.h"
#include "RulesAutomaton.h"
#include "RightParenthesisAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "SchemesAutomaton.h"


class Lexer {
private:
    vector<Automaton*> automata;
    vector<Token> tokens;

    void initializeAutomata() { // if ID and undefined are at the end it resolves keyword issues
        automata.push_back(new LineCommentAutomaton());
        automata.push_back(new ColonAutomaton());
        automata.push_back(new ColonDashAutomaton());
        automata.push_back(new CommaAutomaton());
        automata.push_back(new AddAutomaton());
        automata.push_back(new BlockCommentAutomaton());
        automata.push_back(new FactsAutomaton());
        automata.push_back(new LeftParenthesisAutomaton());
        automata.push_back(new MultiplyAutomaton());
        automata.push_back(new PeriodAutomaton());
        automata.push_back(new QueriesAutomaton());
        automata.push_back(new QuestionMarkAutomaton());
        automata.push_back(new RightParenthesisAutomaton());
        automata.push_back(new RulesAutomaton());
        automata.push_back(new SchemesAutomaton());
        automata.push_back(new StringAutomaton());

        automata.push_back(new IDAutomaton()); // leave me 2nd to last
        automata.push_back(new UndefinedCharAutomaton()); // leave me last
    }

public:
    vector<Token> run(string input) { // this should be in public
        initializeAutomata();
        Automaton *maxAutomaton = automata.at(0);
        unsigned int maxRead = 0;
        unsigned int line = 1;

        while (!input.empty()) {
            while (isspace(input[0]) || input[0] == '\n') {
                if (input[0] == '\n') {
                    line += 1;
                }
                input = input.substr(1);
            }
            if (input.empty())
                break;

            for (auto currentAutomaton : automata) {
                unsigned int n = currentAutomaton->run(input);
                if (n > maxRead) {
                    maxRead = n;
                    maxAutomaton = currentAutomaton;
                }
            }
            Token currToken = Token(maxAutomaton->getType(), input.substr(0, maxRead), line);

            // edge case for line comment
            if (currToken.getType() == LINE_COMMENT)
                currToken = Token(maxAutomaton->getType(), input.substr(0, maxRead - 1), line);
            input = input.substr(maxRead);
            line += maxAutomaton->getNewLines();
            if (currToken.getType() != LINE_COMMENT && currToken.getType() != COMMENT) {
                tokens.push_back(currToken);
            }
            maxRead = 0;
            maxAutomaton = automata.at(0);
        }
        // once we're at the end add an end of file token
        Token t = Token(END_OF_FILE, "", line);
        tokens.push_back(t);
        return tokens;
    }
};

#endif //CS236_LEXER_H