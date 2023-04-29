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

    // Evaluate all rules and print results
    interpreter.evaluateAllRules();

    // Evaluate and print the result of the queries
    interpreter.evaluateAllQueries();
    

    return 0;
}