// Parameter.h - CS 236 - Nathan Petersen
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Parameter
{
private:
	string name;

public:
	Parameter(string name) : name(name) {}

	void setName(string newName)
	{
		name = newName;
	}

	string getName()
	{
		return name;
	}

	bool isConstant()
	{
		if (name.at(0) == '\'')
			return true;
		else
			return false;
	}
};
