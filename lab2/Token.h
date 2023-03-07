// Token.h - CS 236 - Lab 1
#pragma once
#include <string>
#include <sstream>
using namespace std;

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON,
     COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES,
     ID, STRING, COMMENT, WHITESPACE, UNDEFINED, ENDOF
     // Can't use EOF when strings are being used, using ENDOF instead.
};

class Token {
private:
    TokenType type;
    string value;
    int line;
    
public:
    Token () {type = UNDEFINED, value = "", line = 0;}
    Token(TokenType type, string value, int line) : type(type), value(value), line(line) {}

    string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }

    string typeName(TokenType type) const {
        switch (type){
            case (COMMA): return "COMMA"; break;
            case (PERIOD): return "PERIOD"; break;
            case (Q_MARK): return "Q_MARK"; break;
            case (LEFT_PAREN): return "LEFT_PAREN"; break;
            case (RIGHT_PAREN): return "RIGHT_PAREN"; break;
            case (COLON): return "COLON"; break;
            case (COLON_DASH): return "COLON_DASH"; break;
            case (MULTIPLY): return "MULTIPLY"; break;
            case (ADD): return "ADD"; break;
            case (SCHEMES): return "SCHEMES"; break;
            case (FACTS): return "FACTS"; break;
            case (RULES): return "RULES"; break;
            case (QUERIES): return "QUERIES"; break;
            case (ID): return "ID"; break;
            case (STRING): return "STRING"; break;
            case (COMMENT): return "COMMENT"; break;
            case (UNDEFINED): return "UNDEFINED"; break;
            case (ENDOF): return "EOF"; break;
            default: return "INVALID"; break;
        }
        return "ERROR";
    } 

    TokenType getType () const{
        return type;
    }
};