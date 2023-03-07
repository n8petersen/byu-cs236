// DatalogProgram.h - CS 236 - Nathan Petersen
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include "Predicate.h"
#include "Rule.h"
using namespace std; 

class DatalogProgram {
private: 
	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Predicate> queries;
	vector<Rule> rules;
	set<string> domain;

public: 
	DatalogProgram() { }

	void addScheme(Predicate predicate) {
		schemes.push_back(predicate);
	}
    
	void addFact(Predicate predicate) {
		facts.push_back(predicate);
	}
    
	void addQuery(Predicate predicate) {
		queries.push_back(predicate);
	}
    
	void addRule(Rule rule) {
		rules.push_back(rule);
	}
    
	void addDomain(Parameter parameter) {
		domain.insert(parameter.getName());
	}
	    
	string getSchemes() {
		stringstream out;
        out << "Schemes" << '(' << schemes.size() << "):" << endl;
        for (size_t i = 0; i < schemes.size(); i++) {
			out << "  " << schemes.at(i).toString() << endl;
        }
        return out.str();
	}

	string getFacts() {
		stringstream out;
        out << "Facts" << '(' << facts.size() << "):" << endl;
        for (size_t i = 0; i < facts.size(); i++) {
			out << "  " << facts.at(i).toString() << "." << endl;
        }
        return out.str();
	}

	string getRules() {
		stringstream out;
        out << "Rules" << '(' << rules.size() << "):" << endl;
        for (size_t i = 0; i < rules.size(); i++) {
			out << "  " << rules.at(i).toString() << "." << endl;
        }
        return out.str();
	}
    
	string getQueries() {
		stringstream out;
        out << "Queries" << '(' << queries.size() << "):" << endl;
        for (size_t i = 0; i < queries.size(); i++) {
			out << "  " << queries.at(i).toString() << "?" << endl;
        }
        return out.str();
	}
    
    
	string getDomain() {
		stringstream out;
        out << "Domain" << '(' << domain.size() << "):" << endl;
		set<string>::iterator iter;
        for (iter = domain.begin(); iter != domain.end(); iter++) {
			Parameter param = *iter;
			out << "  " << param.getName() << endl;
		}
        return out.str();
	}
    
};
