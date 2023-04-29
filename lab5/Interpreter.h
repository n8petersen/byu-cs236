#pragma once
#include <iostream>
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Graph.h"
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
	vector<Rule> rules;

public:
	Interpreter() {}
	Interpreter(DatalogProgram data)
	{
		datalog = data;
		schemes = data.getSchemes();
		facts = data.getFacts();
		queries = data.getQueries();
		rules = data.getRules();

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
					variableNames.push_back(queryVector.at(i));				   // save for the project and rename
				}
			}
		}

		// output number of tuples, if any were found
		if (resultRelation.getTuplesCount() > 0)
		{
			cout << "Yes(" << resultRelation.getTuplesCount() << ')' << endl;
		}
		else
		{
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
		cout << "Query Evaluation" << endl;
		// for each query, get the name and the variables of that query
		for (unsigned int i = 0; i < queries.size(); ++i)
		{
			vector<string> queryVector = queries.at(i).getParameterStrings();
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

			evaluateQuery(queryVector, name);
		}
	}

	Relation evaluatePredicate(Predicate pred)
	{
		Relation result = database.at(pred.getName());

		vector<string> variableNames;
		map<string, int> variables;

		// for (auto& param : pred.getParameters())
		for (unsigned int i = 0; i < pred.getParameters().size(); i++)
		{
			Parameter param = pred.getParameters().at(i);
			// check if current token is a constant
			if (param.isConstant())
			{
				result = result.select(i, param.getName()); // select type 1
			}
			// otherwise add it to variables to track
			else
			{
				if (variables.find(param.getName()) != variables.end())
				{
					result = result.select(i, variables.at(param.getName())); // select type 2
				}
				else
				{
					variables.insert(pair<string, int>(param.getName(), i)); // save for the project
					variableNames.push_back(param.getName());				 // save for the project and rename
				}
			}
		}

		result = result.project(variables, variableNames);

		result = result.rename(variableNames);

		return result;
	}

	void evaluateRule(Rule evalRul)
	{
		vector<Relation> relVector;
		map<string, int> variables;
		vector<string> variableNames;

		vector<Predicate> predicates = evalRul.getPredicateList();

		for (unsigned int i = 0; i < predicates.size(); i++)
		{
			Relation tempRel = evaluatePredicate(predicates.at(i));
			relVector.push_back(tempRel);
		}

		Relation joinedRel = relVector.at(0);

		for (unsigned int i = 0; i < relVector.size(); i++)
		{
			joinedRel = joinedRel.join(relVector.at(i));
		}

		for (unsigned int i = 0; i < evalRul.getHead().getParameters().size(); i++)
		{
			for (unsigned j = 0; j < joinedRel.getScheme().size(); j++)
			{
				// get the current parameter in the scheme of the joined Relation
				string thisParamName = joinedRel.getScheme().at(j);

				// get the name of the parameter in this position of the passed rule
				Predicate comparePred = evalRul.getHead();
				vector<Parameter> compareParamList = comparePred.getParameters();
				Parameter compareThisParam = compareParamList.at(i);
				string compareParamName = compareThisParam.getName();

				// compare the two. If they match, then we need to add this index to our vector.
				// if (thisParamName.compare(compareParamName) == 0)
				if (thisParamName == compareParamName)
				{
					variables.insert(pair<string, int>(compareParamName, j));
					variableNames.push_back(compareParamName);
				}
			}
		}

		// project once
		Relation resultRelation = joinedRel.project(variables, variableNames);

		// rename once
		resultRelation = resultRelation.rename(variableNames);

		// union
		database.at(evalRul.getHead().getName()).unionize(resultRelation);
	}

	void evaluateAllRules()
	{
		int sizeBefore;
		int sizeAfter;
		int numPasses = 0;
		cout << "Rule Evaluation" << endl;

		do
		{
			sizeBefore = database.getSize();
			for (auto &rule : rules)
			{
				cout << rule.toString() << "." << endl;
				evaluateRule(rule);
			}
			sizeAfter = database.getSize();
			numPasses++;
		} while (sizeBefore != sizeAfter);

		cout << endl;
		cout << "Schemes populated after ";
		cout << numPasses;
		cout << " passes through the Rules.";
		cout << endl
			 << endl;
	}

	static Graph makeGraph(const vector<Rule> &rules)
	{

		Graph graph(rules.size());
		// add code to add edges to the graph for the rule dependencies
		for (unsigned fromID = 0; fromID < rules.size(); fromID++)
		{
			Rule fromRule = rules.at(fromID);
			// cout << "from rule R" << fromID << ": " << fromRule.toString() << endl; // TODO: Remove for Project5

			for (unsigned pred_idx = 0; pred_idx < fromRule.getBodySize(); pred_idx++)
			{
				Predicate bodyPred = fromRule.getBodyPredicate(pred_idx);
				// cout << "from body predicate: " << bodyPred.toString() << endl;	// TODO: Remove for Project5

				for (unsigned toID = 0; toID < rules.size(); toID++)
				{
					Rule toRule = rules.at(toID);
					// cout << "to rule R" << toID << ": " << toRule.toString() << endl;	// TODO: Remove for Project5
					
					if (bodyPred.getName() == toRule.getHead().getName())
					{
						graph.addEdge(fromID, toID);
						// cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl; // TODO: Remove for Project5
					}
				}
			}
		}

		return graph;
	}
};
