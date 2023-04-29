#pragma once
#include <set>
#include <sstream>
using namespace std;

class Node
{
private:
  set<int> adjacentNodeIDs;
  bool visited;
  int postOrderNum;

public:
  void addEdge(int adjacentNodeID)
  {
    adjacentNodeIDs.insert(adjacentNodeID);
  }

  string toString()
  {
    stringstream out;
    string delim = "";
    for (auto nodeID : adjacentNodeIDs)
    {
      out << delim << "R" << nodeID;
      delim = ",";
    }
    return out.str();
  }
};