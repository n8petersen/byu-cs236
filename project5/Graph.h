#pragma once
#include <map>
#include <sstream>
#include <stack>
#include <queue>
#include "Node.h"
using namespace std;

class Graph
{

private:
    map<int, Node> nodes;
    // map<int, set<int>> edges;
    stack<int> postorder;

public:
    Graph(int size)
    {
        for (int nodeID = 0; nodeID < size; nodeID++)
        {
            nodes[nodeID] = Node();
        }
    }

    Graph(map<int, Node> inNodes) : nodes(inNodes) {}
    // Graph(map<int, set<int>> inEdges) : edges(inEdges) {}

    void addEdge(int fromNodeID, int toNodeID)
    {
        nodes[fromNodeID].addEdge(toNodeID); // add to the node
        // edges[fromNodeID] = nodes[fromNodeID].getEdges(); // add to our graph as well
    }

    stack<int> getPostOrder()
    {
        return postorder;
    }

    map<int, Node> getNodes()
    {
        return nodes;
    }

    string toString()
    {
        stringstream out;
        for (auto pair : nodes)
        {
            out << "R" << pair.first << ":" << pair.second.toString() << endl;
        }

        return out.str();
    }

    Graph reverse()
    {
        map<int, Node> newNodes;

        for (auto &entry : nodes)
        {
            int key = entry.first;

            for (int value : entry.second.getEdges())
            {
                newNodes[value].addEdge(key);
            }
        }

        return Graph(newNodes);
    }

    void dfsForest()
    {
        for (auto &nodeX : nodes) // for each node x
        {
            nodeX.second.setVisited(false); // clear the visit mark on node x
        }

        for (auto &nodeX : nodes) // for each node x
        {
            // Node nodeX = nodeXPair.second;
            if (!nodeX.second.getVisited()) // if node x is notmarked
            {
                dfs(nodeX.first, nodeX.second); // dfs(x)
            }
        }
    }

    void dfs(int nodeXID, Node &nodeX)
    {
        nodeX.setVisited(true); // mark node x visited

        for (auto &nodeYID : nodeX.getEdges()) // for each adjacent node y
        {
            // Node nodeY = nodes[nodeYID];
            if (!nodes[nodeYID].getVisited()) // if node y is not marked
            {
                dfs(nodeYID, nodes[nodeYID]); // dfs(y)
            }
        }

        // nodeX.setPostOrderNum(1); // how do I increment this as I'm going through the graph?
        postorder.push(nodeXID);
    }

    queue<set<int>> dfsForestSCC(stack<int> order)
    {
        queue<set<int>> result;

        for (auto &nodeX : nodes) // for each node x
        {
            nodeX.second.setVisited(false); // clear the visit mark on node x
        }

        for (auto &node : nodes)
        {
            set<int> tree;
            pair<const int, Node> thisNode = node; // literally just here to get rid of a warning that node wasn't used.

            if (!nodes[order.top()].getVisited())
            {
                tree = dfsSCC(order.top(), nodes[order.top()]);
                result.push(tree);
            }

            order.pop();
        }

        return result;
    }

    set<int> dfsSCC(int nodeXID, Node &nodeX)
    {
        set<int> result;

        nodeX.setVisited(true);

        for (auto &nodeYID : nodeX.getEdges())
        {
            if (!nodes[nodeYID].getVisited())
            {
                result.merge(dfsSCC(nodeYID, nodes[nodeYID]));
            }
        }

        result.insert(nodeXID);
        return result;
    }
};