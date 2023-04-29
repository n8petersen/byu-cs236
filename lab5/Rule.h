// Rule.h - CS 236 - Nathan Petersen
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Predicate.h"
using namespace std;

class Rule
{
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;

public:
    Rule() {}
    Rule(Predicate head) : headPredicate(head) {}

    void setHead(Predicate head)
    {
        headPredicate = head;
    }

    Predicate getHead()
    {
        return headPredicate;
    }

    void addBodyPredicate(Predicate predicate)
    {
        bodyPredicates.push_back(predicate);
    }

    Predicate getBodyPredicate(int pred_idx)
    {
        return bodyPredicates.at(pred_idx);
    }

    unsigned int getBodySize() {
        return bodyPredicates.size();
    }

    vector<Predicate> getPredicateList()
    {
        return bodyPredicates;
    }

    string toString()
    {
        stringstream out;
        out << headPredicate.toString() << " :- ";
        for (size_t i = 0; i < bodyPredicates.size(); i++)
        {
            out << bodyPredicates.at(i).toString();
            if (i < bodyPredicates.size() - 1)
            {
                out << ',';
            } // Only print comma if not last one
        }

        return out.str();
    }
};
