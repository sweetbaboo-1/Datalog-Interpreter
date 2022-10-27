//
// Created by Matthew on 7/19/2022.
//

#ifndef CS236_DATABASE_H
#define CS236_DATABASE_H

#include <map>
#include "Relation.h"
#include <string>

using namespace std;

class Database {
private:
    map<string, Relation> database;

public:
    Database() = default;
    map<string, Relation> getDatabase() {
        return database;
    }

    void addRelation(const Relation& relation) {
        database.insert(pair<string, Relation>(relation.getName(), relation));
    }

    void addTuple(const string& nameOfRelation, Tuple tuple) {
        database.at(nameOfRelation).addTuple(tuple);
    }

    Relation *getRelation(string basicString) {
        return &database.at(basicString);
    }
};

#endif //CS236_DATABASE_H
