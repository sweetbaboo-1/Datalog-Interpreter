//
// Created by Matthew on 7/7/2022.
//

#ifndef CS236_DATALOGPROGRAM_H
#define CS236_DATALOGPROGRAM_H

#include <set>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;

    // helper function to get all toStrings of some vector of predicates
    static string predicateString(const vector<Predicate>& predicates, const string& name, const string& trailingSymbol) {
        stringstream s;
        string sep;
        s << name << "(" << predicates.size() << ")" << ":\n  ";
        for (Predicate predicate: predicates) {
            s << sep << predicate.toString();
            sep = trailingSymbol + "\n  ";
        }
        if (!predicates.empty())
            s << trailingSymbol;
        s << endl;
        return s.str();
    }

public:
    DatalogProgram() = default;

    const vector<Predicate> &getSchemes() const {
        return schemes;
    }

    const vector<Predicate> &getFacts() const {
        return facts;
    }

    vector<Rule> &getRules() {
        return rules;
    }

    const vector<Predicate> &getQueries() const {
        return queries;
    }

    const set<string> &getDomain() const {
        return domain;
    }

    void addFact(const Predicate& predicate) {
        facts.push_back(predicate);
    }

    void addScheme(const Predicate& predicate) {
        schemes.push_back(predicate);
    }

    void addRule(const Rule& rule) {
        rules.push_back(rule);
    }

    void addQuery(const Predicate& predicate) {
        queries.push_back(predicate);
    }

    void addDomainItem(const string& s) {
        domain.insert(s);
    }

    string toString() {
        stringstream s;
        s << predicateString(schemes, "Schemes", "");
        s << predicateString(facts, "Facts", ".");

        s << "Rules(" << rules.size() << "):\n  ";
        string sep;
        for (Rule r: rules) {
            s << sep << r.toString();
            sep = ".\n  ";
        }
        if (!rules.empty())
            s << "." << endl;

        s << predicateString(queries, "Queries", "?");

        s << "Domain(" << domain.size() << "):" << "\n  ";
        sep = "";
        for (const string& str: domain) {
            s << sep << str;
            sep = "\n  ";
        }
        return s.str();
    }

};

#endif //CS236_DATALOGPROGRAM_H
