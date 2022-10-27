//
// Created by Matthew on 7/15/2022.
//

#ifndef CS236_RELATION_H
#define CS236_RELATION_H

#include "Header.h"
#include "Tuple.h"
#include <set>
class Relation {
private:
    string name;
    Header header;
    set<Tuple> tuples;
public:
    const set<Tuple> &getTuples() const {
        return tuples;
    }

private:
    bool isJoinable (Tuple t1, Tuple t2, vector<pair<int, int>> overlap) {

        for (pair<int,int> p: overlap) {
            if (t1.at(p.first) != t2.at(p.second)) {
                return false;
            }
        }
        return true;
    }

    Tuple combineTuples(Tuple first, Tuple second, set<int> unique) {
        Tuple combinedTuple;
        for (unsigned int i = 0; i < first.size(); i++)
            combinedTuple.push_back(first.at(i));
        for (int i : unique)
            combinedTuple.push_back(second.at(i));
        return combinedTuple;
    }

    void combineSetsOfTuples (set<Tuple> first, set<Tuple> second, vector<pair<int, int>> overlap, set<int> unique, Relation* relation) {
        // combine tuples -- will be the tuples for 'output'
        for (Tuple t : first) {
            for (Tuple tt : second) {
                if (isJoinable(t, tt, overlap)) {
                    Tuple newTuple = combineTuples(t, tt ,unique);
                    relation->addTuple(newTuple);
                }
            }
        }
    }

    Header combineHeaders(Header h1, Header h2, set<int> unique) {
        Header output;
        // everything from h1
        for (unsigned int i = 0; i < h1.size(); i++) {
            output.push_back(h1.at(i));
        }
        // just the unique stuff from h2
        for (int i : unique) {
            output.push_back(h2.at(i));
        }
        return output;
    }

public:
    Relation() { }

    Relation* select(unsigned int col, string expectedVal) {
        Relation* output = new Relation(); // make a new empty relation

        output->setName(this->name); // copy over name
        output->setHeader(this->header); // copy over header

        for (Tuple currTuple : this->tuples) { // loop through each tuple
            if (currTuple.at(col) == expectedVal) {
                output->addTuple(currTuple);
            }
        }
        return output;
    }

    Relation* select(unsigned int col1, unsigned int col2) {

        Relation* output = new Relation(); // make a new empty relation

        output->setName(this->name); // copy over name
        output->setHeader(this->header); // copy over header

        for (Tuple currTuple : this->tuples) { // loop through each tuple
            // check to make sure both columns are in bounds
            if (currTuple.size() <= col1)
                throw "ERROR 1: Tried to select col that is out of range";
            if (currTuple.size() <= col2)
                throw "ERROR 2: Tried to select col that is out of range";

            if (currTuple.at(col1) == currTuple.at(col2)) {
                output->addTuple(currTuple);
            }
        }
        return output;
    }

    Relation* naturalJoin(Relation* other) {
        // give clearer names to the this and other relations
        Relation* r1 = this;
        Relation* r2 = other;
        Relation* output = new Relation();

        // set name of output relation
        output->setName(r1->getName() + " |x| " + r2->getName());

        // calculate header overlap of 'this' and 'other' relations
        Header h1 = r1->getHeader();
        Header h2 = r2->getHeader();
        vector<pair<int, int>> overlap;
        set<int> unique;
        for (unsigned int i = 0; i < h2.size(); i++) {
            bool found = false;
            for (unsigned int ii = 0; ii < h1.size(); ii++) {
                if (h1.at(ii) == h2.at(i)) {
                    found = true;
                    overlap.emplace_back(ii,i);
                }
            }
            if (!found)
                unique.insert(i);
        }
        output->setHeader(combineHeaders(h1, h2, unique));
        // combine tuples -- will be the tuples for 'output'
        combineSetsOfTuples(r1->tuples, r2->tuples, overlap, unique, output);
        return output;
    }

    Relation* project(vector<unsigned int> colsToKeep) {
        Relation* output = new Relation();
        output->setName(name);
        Header newHeader;
        for (unsigned int i: colsToKeep) {
            newHeader.push_back(header.at(i));
        }
        output->setHeader(newHeader);

        set<Tuple> newTuples;
        for (Tuple t: tuples) {
            Tuple tuple;
            for (int i: colsToKeep) {
                tuple.push_back(t.at(i));
            }
            newTuples.insert(tuple);
        }
        output->setTuples(newTuples);
        return output;
    }

    void setTuples(set<Tuple> set1) {
        tuples = set1;
    }

    Relation* rename(vector<string> newAttributes) {
        Relation* output = new Relation();
        output->setName(name);
        Header newHeader = (Header(newAttributes));
        output->setHeader(newHeader);
        output->setTuples(tuples);
        return output;
    }

     pair<bool, set<Tuple>> unionize (Relation* other) {
        bool addedSomething = false;
        set<Tuple> unique;
         for (Tuple t : other->getTuples()) {
             if(tuples.insert(t).second) {
                 addedSomething = true;
                 unique.insert(t);
             }
         }
         return {addedSomething, unique};
     }

    void addTuple(Tuple t) {
        tuples.insert(t);
    }

    unsigned int numTuples() const {
        return tuples.size();
    }

    string toString() const {
        stringstream out;
        //out << name;
        for (Tuple t : tuples) {
            if (t.size() > 0) {
                out << "  " << t.toString(header) << endl;
            }
        }
        return out.str();
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Relation::name = name;
    }

    const Header &getHeader() const {
        return header;
    }

    void setHeader(const Header &header) {
        Relation::header = header;
    }
};

#endif //CS236_RELATION_H
