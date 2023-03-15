// Tuple.h - CS 236 - Lab 3
#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "Scheme.h"
using namespace std;

class Tuple : public vector<string>
{

public:
    Tuple(vector<string> values) : vector<string>(values) {}
    Tuple() : vector<string>(){};

    string toString(const Scheme &scheme) const
    {
        const Tuple &tuple = *this;
        stringstream out;

        for (size_t i = 0; i < scheme.size(); i++)
        {
            out << scheme.at(i) << "=" << tuple.at(i) << ", ";
        }

        return out.str();
    }
};