#pragma once
#include <iostream>
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include <sstream>
using namespace std;

class Interpreter
{
private:
	DatalogProgram datalog;
	Database database;

	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;

public:
	Interpreter() {}
	Interpreter(DatalogProgram data)
	{
		datalog = data;
		schemes = data.getSchemes();
		facts = data.getFacts();
		queries = data.getQueries();
		// rules = data.getRules(); // Don't do in project 3

		// get the schemes and facts out of the datalog
		interpretSchemes();
		interpretFacts();
	}

	void interpretSchemes()
	{
		// make a relation for each scheme, and put that relation in the database datamember
		// // for each scheme
		for (size_t i = 0; i < schemes.size(); i++)
		{
			string schemeName = schemes.at(i).getName();
			Scheme scheme;

			// get each parameter in the scheme
			vector<Parameter> schemeParameters = schemes.at(i).getParameters();
			for (size_t j = 0; j < schemeParameters.size(); j++)
			{
				string value = schemeParameters.at(j).getName();
				scheme.push_back(value);
			}

			// make a relation using the scheme
			Relation resultRelation(schemeName, scheme);

			// put the relation in the database
			database.insert(pair<string, Relation>(schemeName, resultRelation));
		}
	}

	void interpretFacts()
	{
		// make a tuple for each fact, and put that tuple in the appropriate relation within the database.
		// for each fact
		for (size_t i = 0; i < facts.size(); i++)
		{
			string factName = facts.at(i).getName();
			Tuple tuple;

			// get each parameter in the fact
			vector<Parameter> factParameters = facts.at(i).getParameters();
			for (size_t j = 0; j < factParameters.size(); j++)
			{
				string value = factParameters.at(j).getName();
				tuple.push_back(value);
			}
			database.at(factName).addTuple(tuple);
		}
	}

	Relation evaluateQuery(vector<string> queryVector, string name)
	{
		// grab relation from database 
		Relation resultRelation = database.at(name);

		map<string, int> variables;
		vector<string> variableNames;

		for (unsigned int i = 0; i < queryVector.size(); ++i)
		{
			// check if the current token(?) is a constant
			if (queryVector.at(i).at(0) == '\'')
			{
				resultRelation = resultRelation.select(i, queryVector.at(i)); // select type 1
			}

			// otherwise its a variable that we need to keep track of
			else
			{
				if (variables.find(queryVector.at(i)) != variables.end())
				{
					resultRelation = resultRelation.select(i, variables.at(queryVector.at(i))); // select type 2
				}
				else
				{
					variables.insert(pair<string, int>(queryVector.at(i), i)); // save for the project
					variableNames.push_back(queryVector.at(i)); // save for the project and rename
				}
			}
		}

		// output number of tuples, if any were found
		if (resultRelation.getTuplesCount() > 0) {
			cout << "Yes(" << resultRelation.getTuplesCount() << ')' << endl;
		}
		else {
			cout << "No" << endl;
		}
			
		// project once
		resultRelation = resultRelation.project(variables, variableNames);

		// rename once
		resultRelation = resultRelation.rename(variableNames);

		// output tuples that answer the query
		if (!resultRelation.schemeEmpty()) // only print the tuple line when there's something to be printed
		{
			cout << resultRelation.printTuples();
		}

		return resultRelation;
	}

	void evaluateAllQueries()
	{
		// for each query, get the name and the variables of that query
		for (unsigned int i = 0; i < queries.size(); ++i)
		{
			vector<string> queryVector= queries.at(i).getParameterStrings();
			string name = queries.at(i).getName();

			// output the query
			cout << queries.at(i).getName() << '(';
			for (unsigned int j = 0; j < queryVector.size(); ++j)
			{
				cout << queryVector.at(j);
				if (j < queryVector.size() - 1) // iterate through in case there are multiple
				{
					cout << ',';
				}
				else
				{
					cout << ")? "; // end of query
				}
			}

			// answer the query
			evaluateQuery(queryVector, name);
		}
	}
};
