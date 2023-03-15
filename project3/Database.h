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
};