// Database.h - CS 236 - Nathan Petersen
#pragma once
#include <map>
#include <string>
#include "Relation.h"
using namespace std;

class Database : public map<string, Relation>
{

private:
public:
    Database() {}
    ~Database() {}

    int getSize() 
    {
        int size = 0;
        Database dbMap = *this;
        
        for (auto iter = dbMap.begin(); iter != dbMap.end(); iter++)
        {
            for(Tuple tuple : iter->second.getTuples())
            {
                size++;
            }
        }

        return size;
    }
};