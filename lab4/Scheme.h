// Scheme.h - CS 236 - Lab 3 // Modified for Lab/Project 4
#pragma once
#include <vector>
#include <string>
using namespace std;

class Scheme : public vector<string> {

public:
  Scheme(vector<string> names) : vector<string>(names) { }
  Scheme() : vector<string>() { }

};