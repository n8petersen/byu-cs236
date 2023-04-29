// Relation.h - CS 236 - Lab 3
#pragma once
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
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
    Relation() {}

    void addTuple(const Tuple &tuple)
    {
        tuples.insert(tuple);
    }

    int getTuplesCount()
    {
        return tuples.size();
    }

    set<Tuple> getTuples()
    {
        return tuples;
    }

    Scheme getScheme()
    {
        return scheme;
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
                if (i < vars.size() - 1)
                {
                    out << ", ";
                }
            }
            out << endl;
        }
        return out.str();
    }

    // select keeps the same name and scheme
    // but only keeps tuples where the value in the passed column matches  the passed value
    // select TYPE 1
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

    static bool joinable(const Scheme &leftScheme, const Scheme &rightScheme, const Tuple &leftTuple, const Tuple &rightTuple)
    {
        // add code to test whether the tuplesa re joinable

        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++)
        {
            const string &leftName = leftScheme.at(leftIndex);
            const string &leftValue = leftTuple.at(leftIndex);
            // cout << "left name: " << leftName << " value: " << leftValue << endl;

            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++)
            {
                const string &rightName = rightScheme.at(rightIndex);
                const string &rightValue = rightTuple.at(rightIndex);
                // cout << "right name: " << rightName << " value: " << rightValue << endl;

                if ((leftName == rightName) && (leftValue != rightValue))
                {
                    return false;
                }
            }
        }
        return true;
    }

    Scheme joinSchemes(const Relation &right)
    {
        const Relation &left = *this;
        const Scheme leftScheme = left.scheme;
        const Scheme rightScheme = right.scheme;

        Scheme resultScheme = leftScheme;

        for (unsigned int i = 0; i < rightScheme.size(); i++)
        {
            if (find(leftScheme.begin(), leftScheme.end(), rightScheme.at(i)) == leftScheme.end())
            {
                resultScheme.push_back(rightScheme.at(i));
            }
        }

        return resultScheme;
    }

    Tuple joinTuples(const Scheme &endScheme, const Scheme &leftScheme,
                     const Scheme &rightScheme, const Tuple &leftTuple, const Tuple &rightTuple)
    {
        Tuple result;
        // for each element in the result scheme
        for (auto &schemeEl : endScheme)
        {
            // found flag
            bool found = false;

            // iterate through the left scheme
            for (unsigned int i = 0; i < leftScheme.size(); i++)
            {
                // if this element of the result scheme is in the left scheme
                if (schemeEl == leftScheme.at(i))
                {
                    // set the found flag
                    found = true;
                    // add the element from left tuple at the current index to the result tuple
                    result.push_back(leftTuple.at(i));
                    break;
                }
            }

            // if the found flag is false, then it wasn't in the left tuple
            // so we check the right tuple
            // but we don't care to check the right tuple if it was found in the left tuple anyway
            if (!found)
            {
                // so we iterate through the right tuple
                for (unsigned int i = 0; i < rightScheme.size(); i++)
                {
                    // if this element of the result scheme is in the right scheme
                    if (schemeEl == rightScheme.at(i))
                    {
                        // no need to set the found flag, since it will get reset after this iteration anyway

                        // add the element from right tuple at the current index to the result tuple
                        result.push_back(rightTuple.at(i));
                        break;
                    }
                }
            }
        }

        // return the resulting tuple with all the added elements from the join
        return result;
    }

    Relation join(const Relation &right)
    {
        const Relation &left = *this;

        // combine schemes
        Scheme newScheme = joinSchemes(right);

        // make new empty relation using new scheme
        Relation result(name, newScheme);

        for (const Tuple &leftTuple : left.tuples)
        {
            for (const Tuple &rightTuple : right.tuples)
            {
                bool canJoin = joinable(left.scheme, right.scheme, leftTuple, rightTuple);
                if (canJoin)
                // if (joinable(left.scheme, right.scheme, leftTuple, rightTuple))
                {
                    Tuple newTuple;
                    newTuple = joinTuples(newScheme, left.scheme, right.scheme, leftTuple, rightTuple);
                    result.addTuple(newTuple);
                }
            }
        }

        return result;
    }

    void unionize(const Relation &right)
    {
        Relation thisRel = *this;
        Scheme thisScheme = thisRel.scheme;
        set<Tuple> leftTuples = thisRel.tuples;

        for (const Tuple &tuple : right.tuples)
        {
            if (leftTuples.find(tuple) == leftTuples.end())
            {
                addTuple(tuple);
                cout << "  " << tuple.toString(thisScheme) << endl;
            }
        }
    }
};