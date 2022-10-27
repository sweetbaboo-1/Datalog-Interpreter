//
// Created by Matthew on 6/24/2022.
//

#ifndef CS236_TOKEN_H
#define CS236_TOKEN_H
#include <string>
#include <sstream>

using namespace std;

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
    MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT,
    UNDEFINED, END_OF_FILE, LINE_COMMENT
};

// the token class
class Token {

private:
    TokenType type;
    string contents;
    unsigned int line;

    static string typeName(TokenType type) {
        switch (type) {
            case COMMA:
                return "COMMA";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case UNDEFINED:
                return "UNDEFINED";
            case ID:
                return "ID";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case STRING:
                return "STRING";
            case COMMENT:
                return "COMMENT";
            case END_OF_FILE:
                return "EOF";
            case LINE_COMMENT:
                return "COMMENT";
            default:
                return "UNDEFINED";
        }
    }

public:
    Token(TokenType type, string contents, unsigned int line) {
        this->type = type;
        this->contents = contents;
        this->line = line;
    }

    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << contents << "\"" << "," << line << ")";
        return out.str();
    }

    void setType(TokenType type) {
        Token::type = type;
    }

    TokenType getType() const {
        return type;
    }

    void setContents(const string &contents) {
        Token::contents = contents;
    }

    string getContents() {
        return contents;
    }

    void setLine(unsigned int line) {
        Token::line = line;
    }

    int getLine() {
        return line;
    }
};
#endif //CS236_TOKEN_H
