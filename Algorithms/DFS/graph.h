#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <stack>

//struct to hold the node edges
struct nodeEdges {
    int sourceNode;
    int destinationNode;
};

//graph class
class Graph
{
private:
    //node adjecents contained within a vector, std::list edge-linking data struct
    std::vector<std::list<int>> adjacents;
public:
    //algorithm function declaration, taking parameters nodeI as the current node, vector of type int for whether the given node has been visited 
    //and info about the graph totalnodes and the graph edges (created in main)
    void DFSAlgorithm(int nodeI, std::vector<int>& visited, Graph const& graph);
  
    //passing in a vector of edges, edges being the source and destinaton nodes into graph constructor
    Graph(std::vector<nodeEdges> const& edges, int totalNodes)
    {
        //resize the vector E "container" to hold totalNode elements where totalNodes is the total number of nodes in the graph and not current node
        adjacents.resize(totalNodes);

        //using index based for loop to simplify the loop with auto defined as the data type | pushing edges onto the graph
        for (auto& nodeEdges : edges)
        {
            //using nodeEdges to access the variables within the nodeEdges struct
            //indexing the adjacents sourcenode, pushingback/adding edges to the graph
            adjacents[nodeEdges.sourceNode].push_back(nodeEdges.destinationNode);
        }
    }
};