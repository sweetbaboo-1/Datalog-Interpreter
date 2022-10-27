//
// Created by Matthew on 7/19/2022.
//

#ifndef CS236_INTERPRETER_H
#define CS236_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include <iostream>
#include "Graph.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
public:

    explicit Interpreter(const DatalogProgram &datalogProgram) : datalogProgram(datalogProgram) {
        // make a relation for each scheme-predicate and put that relation in the database
        // make a tuple for each fact-predicate and put that tuple in the appropriate relation in the database
        // make a relation for each scheme and add it to the database
        for (Predicate scheme: datalogProgram.getSchemes()) {
            Relation relation;
            relation.setName(scheme.getName());
            Header header;
            for (const Parameter &parameter: scheme.getParameters()) {
                header.push_back(parameter.getValue());
            }
            relation.setHeader(header);
            database.addRelation(relation);
        }
        // make a tuple for each fact and add it to the database
        for (Predicate fact: datalogProgram.getFacts()) {
            Tuple tuple;
            for (const Parameter &parameter: fact.getParameters()) {
                tuple.push_back(parameter.getValue());
            }
            database.addTuple(fact.getName(), tuple);
        }
    }

    void run() {
        //evalRules();
        evalRulesOptimized();
        cout << "\nQuery Evaluation\n";
        evalQueries();
    }

    void evalRulesOptimized() {
        /*****************************************************************
         * Build the dependency graph and the reverse dependency graph
         * Run DFS-Forest (in regular numeric order) on the reverse dependency graph to get the post-order
         * Run DFS-Forest (in reverse post-order) on the forward dependency graph to find the strongly connected components
         * Evaluate the rules in each component
         ****************************************************************/
        Graph graph;
        // make a node for each rule
        for (unsigned int i = 0; i < datalogProgram.getRules().size(); i++)
            graph.addNode();

        /* for each rule in order:
         * for each predicate p in the body of the rule
         * find every rule r whose head matches p
         * add the index r to the set of edges */
        for (unsigned int rule = 0; rule < datalogProgram.getRules().size(); rule++) {
            for (const Predicate& predicate: datalogProgram.getRules().at(rule).getBody()) {
                for (unsigned int i = 0; i < datalogProgram.getRules().size(); i++) {
                    if (predicate.getName() == datalogProgram.getRules().at(i).getHead().getName())
                        graph.editNode(rule, i);
                }
            }
        }
        cout << "Dependency Graph\n";
        cout << graph.toString();
        Graph reverseGraph = graph;
        reverseGraph.flipItAndReverseIt();
        vector<int> postOrder = reverseGraph.dfsForest(reverseGraph);
        graph.dfsForestSCC(postOrder);
        vector<set<int>> SCCs = graph.getSCCs();

        // determine if any rule is self dependent
        for (unsigned int i = 0; i < graph.getEdges().size(); i++) {
            for (unsigned int it:graph.getEdges().at(i)) {
                // any of the things in j == i, the corresponding rule is self-dependent
                // cout << "it = " << it << endl;
                if (i == it) {
                    datalogProgram.getRules().at(it).setSelfDependent();
                }
            }
        }

        // make sets of SCCs
        vector<vector<Rule>> setOfRules;
        for (const auto& it:SCCs) {
            vector<Rule> temp;
            for (auto itt:it) {
                temp.push_back(datalogProgram.getRules().at(itt));
            }
            setOfRules.push_back(temp);
            temp.clear();
        }
        // evaluate rules
        cout << "\nRule Evaluation\n";
        int scc = 0;
        for (auto & setOfRule : setOfRules) {
            cout << "SCC: ";
            string sep;
            for (auto it: SCCs.at(scc)) {
                cout << sep << "R" << it;
                sep = ",";
            }
            cout << endl;
            bool changesMade = true;
            bool skip = false;
            int n = 0;
            while (changesMade && !skip) {
                skip = false;
                changesMade = false;
                for (auto rule : setOfRule) {
                    if (setOfRule.size() == 1 && !setOfRule.at(0).isSelfDependent())
                        skip = true;
                    cout << rule.toString() << endl;
                    vector<Relation *> results;
                    // Evaluate the predicates on the right-hand side of the rule:
                    for (const Predicate &predicate: rule.getBody())
                        results.push_back(evalPredicate(predicate));
                    // Join the relations that result:
                    Relation *result = results[0];
                    if (results.size() > 1) { // nothing to join if there is only one result
                        for (unsigned int i = 0; i < results.size() - 1; i++)
                            result = result->naturalJoin(results[i + 1]);
                    }
                    // remove the columns that don't appear in the head of the rule from the result and reorder to match the head
                    vector<unsigned int> colsToKeep;
                    vector<string> names;
                    for (unsigned int i = 0; i < rule.getHead().getParameters().size(); i++) {
                        for (unsigned int j = 0; j < result->getHeader().size(); j++) {
                            if (rule.getHead().getParameters().at(i).getValue() == result->getHeader().at(j)) {
                                colsToKeep.push_back(j);
                                names.push_back(rule.getHead().getParameters().at(i).getValue());
                            }
                        }
                    }
                    result = result->project(colsToKeep);
                    result = result->rename(
                            database.getRelation(rule.getHead().getName())->getHeader().getAttributes());
                    pair<bool, set<Tuple>> foo;
                    foo = database.getRelation(rule.getHead().getName())->unionize(result);
                    if (foo.first)
                        changesMade = true;
                    if (!foo.second.empty()) {
                        for (const Tuple& t: foo.second)
                            cout << "  " << t.toString(result->getHeader()) << endl;
                    }
                }
                n++;
            } // while
            cout << n << " passes: ";
            sep = "";
            for (auto it: SCCs.at(scc)) {
                cout << sep << "R" << it;
                sep = ",";
            }
            n = 0;
            cout << endl;
            scc++;
        } // for each SCC
    }

    void evalRules() {
        int n = 0;
        bool changesMade = true;
        while (changesMade) {
            changesMade = false;
            for (Rule rule: datalogProgram.getRules()) {
                cout << rule.toString() << endl;
                vector<Relation *> results;
                // Evaluate the predicates on the right-hand side of the rule:
                for (const Predicate& predicate: rule.getBody())
                    results.push_back(evalPredicate(predicate));
                // Join the relations that result:
                Relation *result = results[0];
                if (results.size() > 1) { // nothing to join if there is only one result
                    for (unsigned int i = 0; i < results.size() - 1; i++)
                        result = result->naturalJoin(results[i + 1]);
                }
                // remove the columns that don't appear in the head of the rule from the result and reorder to match the head
                vector<unsigned int> colsToKeep;
                vector<string> names;
                for (unsigned int i = 0; i < rule.getHead().getParameters().size(); i++) {
                    for (unsigned int j = 0; j < result->getHeader().size(); j++) {
                        if (rule.getHead().getParameters().at(i).getValue() == result->getHeader().at(j)) {
                            colsToKeep.push_back(j);
                            names.push_back(rule.getHead().getParameters().at(i).getValue());
                        }
                    }
                }
                result = result->project(colsToKeep);
                result = result->rename(database.getRelation(rule.getHead().getName())->getHeader().getAttributes());
                pair<bool, set<Tuple>> foo;
                foo = database.getRelation(rule.getHead().getName())->unionize(result);
                if (foo.first)
                    changesMade = true;
                if (!foo.second.empty()) {
                    for (Tuple t: foo.second)
                        cout << "  " << t.toString(result->getHeader()) << endl;
                }
            }
            n++;
        }
        cout << endl << "Schemes populated after " << n << " passes through the Rules.\n";
    }

    void evalQueries() {
        for (Predicate query: datalogProgram.getQueries()) {
            Relation *result = evalPredicate(query);
            int x = result->numTuples();
            cout << query.toString() << "? "
                 << (result->numTuples() > 0 ? "Yes(" + to_string(x) + ")\n" + result->toString() : "No\n");
        }
    }

    Relation *evalPredicate(Predicate predicate) {
        map<string, unsigned int> seenParameters;
        vector<unsigned int> indexes;
        vector<string> newHeader;

        Relation *output = database.getRelation(predicate.getName());
        unsigned int i = 0;
        for (const Parameter &parameter: predicate.getParameters()) {
            if (parameter.isConst()) {
                output = output->select(i, parameter.getValue());
            } else {
                if (seenParameters.find(parameter.getValue()) != seenParameters.end()) { // we've seen this parameter
                    output = output->select(seenParameters.at(parameter.getValue()), i);
                } else { // we've not seen the parameter
                    seenParameters.insert(pair<string, unsigned int>(parameter.getValue(), i));
                    indexes.push_back(i);
                    newHeader.push_back(parameter.getValue());
                }
            }
            i++;
        }
        output = output->project(indexes);
        output = output->rename(newHeader);
        return output;
    }
};

#endif //CS236_INTERPRETER_H
