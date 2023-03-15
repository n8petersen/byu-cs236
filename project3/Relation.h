// Relation.h - CS 236 - Lab 3
#pragma once
#include <vector>
#include <string>
#include <set>
#include "Tuple.h"
using namespace std;

class Relation
{

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string &name, const Scheme &scheme) : name(name), scheme(scheme) {}

    void addTuple(const Tuple &tuple)
    {
        tuples.insert(tuple);
    }

    int getTuplesCount()
    {
        return tuples.size();
    }

    bool schemeEmpty()
    {
        return scheme.empty();
    }

    string toString() const
    {
        stringstream out;
        for (auto &tuple : tuples)
        {
            out << tuple.toString(scheme) << endl;
        }
        return out.str();
    }

    string printTuples()
    {
        stringstream out;
        for (auto &tuple : tuples)
        {
            vector<string> vars = tuple;
            out << "  ";
            for (unsigned int i = 0; i < vars.size(); ++i)
            {
                out << scheme.at(i) << '=' << vars.at(i);
                if (i < vars.size() - 1) {
                    out << ", ";
                }
                    
            }
            out << endl;
        }
        return out.str();
    }

    // select TYPE 1
    // select keeps the same name and scheme
    // but only keeps tuples where the value in the passed column matches  the passed value
    Relation select(int index, const string &value) const
    {
        Relation result(name, scheme);
        for (auto &tuple : tuples)
        {
            if (tuple[index] == value)
            {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    // select TYPE 2
    Relation select(int index1, int index2)
    {
        Relation result(name, scheme);
        for (auto &tuple : tuples)
        {
            if (tuple.at(index1) == tuple.at(index2))
            {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(map<string, int> vars, vector<string> variables)
    {
        Relation result(name, variables);
        for (auto &tuple : tuples)
        {
            vector<string> tuple_values;
            vector<string> preTuple;

            for (unsigned int i = 0; i < variables.size(); ++i)
            {
                int index = vars.at(variables.at(i));
                preTuple.push_back(tuple.at(index));
            }
            result.addTuple(preTuple);
        }
        return result;
    }

    // Just pass in the whole new schema and totally replace the old one with the new one
    Relation rename(vector<string> variables)
    {
        Relation result(name, variables);
        result.tuples = tuples;
        return result;
    }
};