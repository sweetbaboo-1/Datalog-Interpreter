//
// Created by Matthew on 6/29/2022.
//

#ifndef CS236_PARSER_H
#define CS236_PARSER_H

#include <vector>
#include <iostream>
#include "Token.h"
#include "DatalogProgram.h"

class Parser {
private:
    vector<Token> tokens;
    unsigned int currTokenIndex = 0;
    DatalogProgram program;

    string getPrevTokenContents() {
        if (currTokenIndex < 0) throw "couldn't get previous token contents";
        return tokens.at(currTokenIndex - 1).getContents();
    }

    string getCurrTokenContents() {
        if (currTokenIndex >= tokens.size()) throw "couldn't get current token contents";
        return tokens.at(currTokenIndex).getContents();
    }

public:
    DatalogProgram run() {
        datalogProgram();
        return program;
    }

    Parser(const vector<Token>& tokens) : tokens(tokens) { }
    TokenType tokenType() const {
        if (currTokenIndex >= tokens.size()) return UNDEFINED;
        return tokens.at(currTokenIndex).getType();
    }

    void advanceToken() {
        ++currTokenIndex;
    }

    void throwError() {
        if (currTokenIndex >= tokens.size()) throw tokens.at(tokens.size() - 1);
        throw tokens.at(currTokenIndex);
    }

    void match(TokenType expectedType) {
        if (tokenType() == expectedType) {
            advanceToken();
        } else {
            throwError();
        }
    }

    // datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    void datalogProgram() {
        if(tokenType()==SCHEMES){
            match(SCHEMES);
            match(COLON);
            scheme();
            schemeList();
            match(FACTS);
            match(COLON);
            factList();
            match(RULES);
            match(COLON);
            ruleList();
            match(QUERIES);
            match(COLON);
            query();
            queryList();
            match(END_OF_FILE);
        } else {
            // lambda
        }
    }

    // schemeList -> scheme schemeList | lambda
    void schemeList() {
        if (tokenType() == ID) {
            scheme();
            schemeList();
        } else {
            // lambda
        }
    }

    // factList	-> fact factList | lambda
    void factList() {
        if(tokenType() == ID) {
            fact();
            factList();
        } else {
            // lambda
        }
    }

    // ruleList -> rule ruleList | lambda
    void ruleList() {
        if(tokenType() == ID) {
          rule();
          ruleList();
        } else {
            // lambda
        }
    }

    //queryList	-> query queryList | lambda
    void queryList() {
        if(tokenType() == ID) {
            query();
            queryList();
        } else {
            // lambda
        }
    }

    // scheme ->ID LEFT_PAREN ID idList RIGHT_PAREN
    void scheme() {
        Predicate newScheme;
        match(ID); // name
        newScheme.setName(getPrevTokenContents());
        match(LEFT_PAREN);
        match(ID); // first id
        Parameter firstParameter;
        firstParameter.setValue(getPrevTokenContents());
        newScheme.addParameter(firstParameter);
        idList(newScheme); // all subsequent id
        match(RIGHT_PAREN);
        program.addScheme(newScheme);
    }

    // idList -> COMMA ID idList | lambda
    void idList(Predicate& predicate) {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            Parameter parameter;
            parameter.setValue(getPrevTokenContents());
            predicate.addParameter(parameter);
            idList(predicate);
        } else {
            // lambda
        }
    }

    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    void fact() {
        Predicate newFact;
        match(ID);
        newFact.setName(getPrevTokenContents());
        match(LEFT_PAREN);
        match(STRING);
        newFact.addParameter(getPrevTokenContents());
        program.addDomainItem(getPrevTokenContents());
        stringList(newFact);
        match(RIGHT_PAREN);
        match(PERIOD);
        program.addFact(newFact);
    }

    // stringList -> COMMA STRING stringList | lambda
    void stringList(Predicate& predicate) {
        if(tokenType() == COMMA) {
            match(COMMA);
            match(STRING);
            predicate.addParameter(getPrevTokenContents());
            program.addDomainItem(getPrevTokenContents());
            stringList(predicate);
        } else {
            // lambda
        }
    }

    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    void rule() {
        Rule newRule;
        if (tokenType() == ID) {
            headPredicate(newRule);
            match(COLON_DASH);
            Predicate p;
            predicate(p);
            predicateList(newRule);
            newRule.addPredicate(p);
            match(PERIOD);
            program.addRule(newRule);
        }
    }

    // query -> predicate Q_MARK
    void query() {
        if (tokenType() == ID) {
            Predicate p;
            predicate(p);
            match(Q_MARK);
            program.addQuery(p);
        }
    }

    // headPredicate ->	ID LEFT_PAREN ID idList RIGHT_PAREN
    void headPredicate(Rule& rule) {
        Predicate head;
        match(ID);
        head.setName(getPrevTokenContents());
        match(LEFT_PAREN);
        match(ID);
        head.addParameter(getPrevTokenContents());
        idList(head);
        rule.setHead(head);
        match(RIGHT_PAREN);
    }

    // predicate ->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    void predicate(Predicate& predicate) {
        match(ID);
        predicate.setName(getPrevTokenContents());
        match(LEFT_PAREN);
        parameter(predicate);
        parameterList(predicate);
        match(RIGHT_PAREN);
    }

    // predicateList ->	COMMA predicate predicateList | lambda
    void predicateList(Rule& r) { // pass a rule and add predicates to it
        if(tokenType() == COMMA) {
            Predicate p;
            match(COMMA);
            predicate(p);
            predicateList(r);
            r.addPredicate(p);
        } else {
            // lambda
        }
    }

    // parameterList ->	COMMA parameter parameterList | lambda
    void parameterList(Predicate& predicate) {
        if(tokenType() == COMMA) {
            match(COMMA);
            parameter(predicate);
            parameterList(predicate);
        } else {
            // lambda
        }
    }

    // parameter -> STRING | ID
    void parameter(Predicate& predicate) { // TODO do i need to addParameter or add predicate?
        if(tokenType() == STRING) {
            match(STRING);
        } else {
            match(ID);
        }
        predicate.addParameter(getPrevTokenContents());
    }
};

#endif //CS236_PARSER_H
