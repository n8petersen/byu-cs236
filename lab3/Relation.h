// Relation.h - CS 236 - Lab 3
#pragma once
#include <vector>
#include <string>
#include <set>
#include "Tuple.h"
using namespace std;

class Relation {

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation (const string& name, const Scheme& scheme) : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    string toString() const {
        stringstream out;
        for (auto& tuple : tuples) {
            out << tuple.toString(scheme) << endl;
        }
        return out.str();
    }

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples) {
            if (tuple[index] == value) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

};