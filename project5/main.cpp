#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
using namespace std;

int main(int argc, char *argv[])
{

    // Read in the input file
    ifstream inFile;
    inFile.open(argv[1]);
    stringstream ss;
    ss << inFile.rdbuf();
    string input = ss.str();
    inFile.close();

    // // Test the file was read right
    // cout << input << endl;

    // Scan file for tokens
    Scanner scanner(input);
    vector<Token> tokenVector = scanner.scanToken();

    // Parse the tokens and print to terminal
    Parser parser(tokenVector);
    parser.parse();

    // Get the datalog to pass to interpreter
    DatalogProgram datalog = parser.getDatalog();
    Interpreter interpreter(datalog);

    // Get the rules so we can graph them
    vector<Rule> rules = datalog.getRules();

    // Make a dependency graph
    // Graph graph = Interpreter::makeGraph(rules);
    pair<Graph, Graph> graphs = Interpreter::makeGraph(rules);
    Graph fwdGraph = graphs.first;
    Graph reverseGraph = graphs.second;
    cout << "Dependency Graph" << endl
         << fwdGraph.toString() << endl;

    // our makeGraph now makes the reverse graph too.
    // Reverse dependency graph // don't actually cout this for project5
    // Graph reverseGraph = fwdGraph.reverse();
    // cout << "Reverse Graph" << endl
    //      << reverseGraph.toString() << endl;

    // DFS Forest // don't actually cout this for project5
    reverseGraph.dfsForest();
    // stack<int> testPostorder = reverseGraph.getPostOrder();
    // cout << "Postorder" << endl;
    // while (!testPostorder.empty())
    // {
    //     int el = testPostorder.top();
    //     cout << el << endl;
    //     // cout << "out";
    //     testPostorder.pop();
    // }
    // cout << endl;

    // Find SCC's
    stack<int> postorder = reverseGraph.getPostOrder();
    queue<set<int>> sccForest = fwdGraph.dfsForestSCC(postorder);

    // queue<set<int>> testSccForest = graph.dfsForestSCC(postorder);
    // cout << "SCC's" << endl;
    // int testSccForestSize = testSccForest.size();
    // for (unsigned int i = 0; i < testSccForestSize; i++)
    // {
    //     cout << "SCC " << i << ":";
    //     for (auto &ruleID : testSccForest.front())
    //     {
    //         cout << " R" << ruleID;
    //     }
    //     testSccForest.pop();
    //     cout << endl;
    // }

    // Evaluate all rules and print results
    cout << "Rule Evaluation" << endl;
    interpreter.evaluateAllRules(fwdGraph, sccForest);
    cout << endl;

    // Evaluate and print the result of the queries
    interpreter.evaluateAllQueries();

    return 0;
}