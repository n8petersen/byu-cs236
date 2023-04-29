#pragma once
#include <set>
#include <sstream>
using namespace std;

class Node
{
private:
  set<int> adjacentNodeIDs;
  bool visited;
  // int postOrderNum;

public:
  void addEdge(int adjacentNodeID)
  {
    adjacentNodeIDs.insert(adjacentNodeID);
  }

  set<int> getEdges()
  {
    return adjacentNodeIDs;
  }

  bool getVisited()
  {
    return visited;
  }

  void setVisited(bool set)
  {
    visited = set;
  }

  // void setPostOrderNum(int num)
  // {
  //   postOrderNum = num;
  // }

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