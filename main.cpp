#include "Token.h"
#include<iostream>
#include<fstream>
#include<string>
#include "Lexer.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {

    ifstream f(argv[1]);
    string input;
    input.assign((istreambuf_iterator<char>(f)), (istreambuf_iterator<char>()));

    vector<Token> tokens;
    Lexer lexer;
    DatalogProgram datalogProgram;

    tokens = lexer.run(input);

    try {
        Parser parser = Parser(tokens);
        datalogProgram = parser.run();
//        cout << "Success!\n";
//        cout << datalogProgram.toString();
//        cout << "\n\n------------------------------------------------\n\n";
        Interpreter interpreter(datalogProgram);
        interpreter.run();
    }
    catch(Token errorToken) {
        cout << "Failure!" << endl << "  " << errorToken.toString();
    }
    catch(const char* errorMsg) {
        cout << errorMsg;
    }
}
