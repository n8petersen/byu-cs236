#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"
using namespace std;


int main(int argc, char* argv[]) {
  int numTokens = 0;
  if (!argv[1]) {
    cout << "No input file passed." << endl;
    cout << "Total Tokens = "<< numTokens << endl;
  } 
  
  else {

    // Open the input file
    string fileName = argv[1];
    ifstream in;
    in.open(fileName);

    if (in.is_open()) {
			//cout << "Input File opened successfully.\n";
		}
		else {
			cout << "File couldn't open." << endl;
      cout << "Total Tokens = 0" << endl;
			return 1;
		}


    // Read the input file to string and close
    stringstream ss; 
    ss << in.rdbuf(); 
    string input = ss.str(); 
    in.close();
    //cout << input << endl;
    
    
    //Scan file for tokens
    Scanner file(input, 1);
    static vector<Token> tokens;


    // Print tokens
    tokens = file.scanToken(); 
      for (size_t i = 0; i < tokens.size(); i++) {
        Token iter = tokens.at(i);
        string print = iter.toString();
        cout << print << endl; 
        numTokens++; 
      }
      
	  cout << "Total Tokens = " << numTokens << endl; 
  }

  return 0;
}