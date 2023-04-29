// Scanner.h - CS 236 - Nathan Petersen
#pragma once

#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include "Token.h"

using namespace std;

class Scanner
{
private:
    string input;
    int lineNum = 1;
    vector<Token> tokens;

public:
    Scanner(const string &input) : input(input), lineNum(1) {}

    // Helper function that checks for a keyword
    bool checkKeyWord(string str_check, string key)
    {
        while (!str_check.empty())
        {
            // Parses through until check string is empty

            // If the key is empty, but our check string is not,
            // then check if it's followed by whitespace or a colon.
            if (!str_check.empty() && key.empty())
            {
                // if whitespace or colon follows our check string, then the keyword was found!
                if (isspace(str_check.at(0)) || str_check.at(0) == ':')
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            // Otherwise, keep iterating through the strings as long as they are equal.
            else if (str_check.at(0) == key.at(0))
            {
                str_check = str_check.substr(1);
                key = key.substr(1);
            }

            // If the words don't match any any point, its not a keyword.
            else
            {
                return false;
            }
        }

        // if the loop finishes, then the check string is empty.
        // if the key is also empty, then we found the keyword.
        if (key.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Helper function to help check if a string is valid
    int checkString(string str_check)
    {
        if (str_check.find('\'') == string::npos)
        { // if no ' is not found, return -1.
            return -1;
        }
        else
        {
            return str_check.find('\''); // otherwise return its index
        }
    }

    // Main function to scan tokens. Will return a vector of tokens.
    vector<Token> scanToken()
    {

        // Scan tokens until the input is empty
        while (!input.empty())
        {
            Token this_token;
            int index = 0;
            string value = "";

            // Switch to check the current character of the input
            switch (input.at(0))
            {

            case ('\n'):
                lineNum++; // New lines just increment the
                break;

            case ',':
                this_token = {COMMA, ",", lineNum};
                break;

            case '.':
                this_token = {PERIOD, ".", lineNum};
                break;

            case '?':
                this_token = {Q_MARK, "?", lineNum};
                break;

            case '(':
                this_token = {LEFT_PAREN, "(", lineNum};
                break;

            case ')':
                this_token = {RIGHT_PAREN, ")", lineNum};
                break;

            case ':':
                // State machine to check for  :- / COLON_DASH  token
                input = input.substr(1);
                if (!input.empty() && input.at(0) == '-')
                {
                    this_token = {COLON_DASH, ":-", lineNum};
                }
                else
                {
                    this_token = {COLON, ":", lineNum};
                    input.insert(0, "z"); // have to add a dummy char to get removed at end of switch
                }
                break;

            case '*':
                this_token = {MULTIPLY, "*", lineNum};
                break;

            case '+':
                this_token = {ADD, "+", lineNum};
                break;

            case 'S':
                if (checkKeyWord(input, "Schemes"))
                {
                    this_token = {SCHEMES, "Schemes", lineNum};
                    input = input.substr(6);
                }
                else
                {
                    goto Default;
                }
                break;

            case 'F':
                if (checkKeyWord(input, "Facts"))
                {
                    this_token = {FACTS, "Facts", lineNum};
                    input = input.substr(4);
                }
                else
                {
                    goto Default;
                }
                break;

            case 'R':
                if (checkKeyWord(input, "Rules"))
                {
                    this_token = {RULES, "Rules", lineNum};
                    input = input.substr(4);
                }
                else
                {
                    goto Default;
                }
                break;

            case 'Q':
                if (checkKeyWord(input, "Queries"))
                {
                    this_token = {QUERIES, "Queries", lineNum};
                    input = input.substr(6);
                }
                else
                {
                    goto Default;
                }
                break;

            case '\'': // "Let's eat" is invalid. "I''m coding" is valid. // MAYBE-DO: Add a '' escape character, so we get 1 string instead of 2.
                index = checkString(input.substr(1));
                if (index == -1)
                {
                    this_token = {UNDEFINED, input, lineNum};

                    while (!input.empty())
                    {
                        if (input.at(0) == '\n')
                        {
                            lineNum++;
                        }
                        input = input.substr(1);
                    }
                    input = "a";
                }
                else
                {
                    this_token = {STRING, input.substr(0, index + 2), lineNum};
                    input = input.substr(index + 1);
                }
                break;

            case '#': // MAYBE-DO: Add capability for multiline comments #| <comment> |#
                while (!input.empty() && input.at(0) != '\n')
                {
                    string str(1, input.at(0));
                    value = value.append(str);
                    input = input.substr(1);
                }

                this_token = {COMMENT, value, lineNum};
                input.insert(0, "z"); // have to add a dummy char to get removed at end of switch
                break;

            Default:
            default:
                // If we make it to default, we've either been sent here by the keywords not matching
                // Or we haven't hit any of the case conditions yet.
                // We will check if the current token is a valid id, otherwise it is undefined.

                // if the first char is a letter, we have found an id.
                if (isalpha(input.at(0)))
                {
                    string id;

                    // Keep adding chars to the id as long as they are alphanumeric
                    while (!input.empty() && !isspace(input.at(0)) && (isalpha(input.at(0)) || isdigit(input.at(0))))
                    {
                        string letter(1, input.at(0));
                        id = id.append(letter);
                        input = input.substr(1);
                    }

                    input.insert(0, "z"); // have to add a dummy char to get removed at end of switch
                    this_token = {ID, id, lineNum};
                }
                else
                {
                    string und_val(1, input.at(0));
                    this_token = {UNDEFINED, und_val, lineNum};
                }
                break;
            }

            // Push token onto the tokens list
            if (!isspace(input.at(0)))
            {
                if (this_token.getType() != COMMENT)
                { // ADDED FOR PARSER, WE WANT TO IGNORE COMMENTS
                    tokens.push_back(this_token);
                }
            }

            // Update the input by removing one char
            input = input.substr(1, input.length());
        }

        Token endToken(ENDOF, "", lineNum); // End of file token gets pushed onto the vector last
        tokens.push_back(endToken);

        return tokens;
    }
};