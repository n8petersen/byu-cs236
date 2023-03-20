// Relation.h - CS 236 - Lab 3 // Modified for Lab/Project 4
#pragma once
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include "Tuple.h"
using namespace std;

class Relation {

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation (const string& name, const Scheme& scheme) : name(name), scheme(scheme) { }
    Relation () {}

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    void setName(string newName) {
        name = newName;
    }

    void setScheme(Scheme newScheme) {
        scheme = newScheme;
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

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
        // add code to test whether the tuplesa re joinable

        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);
            cout << "left  name: " << leftName << " value: " << leftValue << endl;

            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);
                cout << "righ t name: " << rightName << " value: " << rightValue << endl;
                
                if ((leftName == rightName) && (leftValue != rightValue)) {
                    return false;
                }
            }
        }
        return true;
    }

    Relation join(const Relation& right) {
        const Relation& left = *this;
        Relation result;

        for (const Tuple& leftTuple : left.tuples) {
            cout << "left tuple: " << leftTuple.toString(left.scheme) << endl;

            for (const Tuple& rightTuple : right.tuples) {
                cout << "right tuple: " << rightTuple.toString(right.scheme) << endl;
            }
        }

         

        return result;
    }

};