#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[]) {

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

    // Parse the tokens and print to terminal
    Parser parser = scanner.scanToken();
    parser.parse();

    return 0;
}