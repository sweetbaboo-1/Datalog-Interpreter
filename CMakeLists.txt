cmake_minimum_required(VERSION 3.16.3)
project(CS236)

set(CMAKE_CXX_STANDARD 14)

add_executable(CS236 main.cpp Token.h Automaton.h Lexer.h ColonAutomaton.h ColonDashAutomaton.h UndefinedCharAutomaton.h IDAutomaton.h CommaAutomaton.h PeriodAutomaton.h QuestionMarkAutomaton.h LeftParenthesisAutomaton.h RightParenthesisAutomaton.h MultiplyAutomaton.h AddAutomaton.h SchemesAutomaton.h FactsAutomaton.h RulesAutomaton.h QueriesAutomaton.h StringAutomaton.h BlockCommentAutomaton.h EOFAutomaton.h LineCommentAutomaton.h Parser.h Predicate.h DatalogProgram.h Parameter.h Rule.h Tuple.h Relation.h Header.h Interpreter.h Database.h Graph.h)
