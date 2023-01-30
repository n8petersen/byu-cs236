#pragma once

#include <string>
// #include <cctype>
#include "Token.h"

using namespace std;

class Scanner {
private:
    string input;
    int lineNum = 0;

    // Function that trims white space from the beginning of a line
    string trimWhiteSpace(string input) {
        while (isspace(input.at(0))) {
            input = input.substr(1);
        }
        return input;
    }

public:
    Scanner(const string &input) : input(input) {}

    Token scanToken() {
        // Initialize Token to bogus values
        TokenType type = UNDEFINED;
        string value = "";
        int line = 0;

        unsigned int length = 0; // Use a length integer to get Token values of lines and remove them from the input

        input = trimWhiteSpace(input); // Trim any existing whitespace from the input line

        switch (input.at(0)) {
            case ',':
                type = COMMA;
                length = 1; // size of value for COMMA is 1, since ',' is 1 char long.
                break;
            default:
                type = UNDEFINED;
                break;
        }

        value = input.substr(0, length);                // Gets the value of the token by going from the beginning of the line, to however long the value is.
        input = input.substr(length, input.length() - 1); // Removes it from the input line.


        // TODO: Find a way to get the line number to input in Token constructor.
        return Token(type, value, line);
    }
};