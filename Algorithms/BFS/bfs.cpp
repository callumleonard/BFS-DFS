#include <iostream>
#include <chrono>
#include <queue>
#include <thread>
#include <list>
#include <vector>
#include "graph.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

// using steady_clock for monotonic time, best suits our needs for timing measurements
typedef std::chrono::steady_clock the_clock;

//args current nodeposition, vector of visited ndoes, the graph containing edges/adjacency list
//start the algorithm at node location X and traverse from node X based on nodeI input
void Graph::BFSAlgorithm(int nodeI, std::vector<int>& visited, Graph const& graph)
{
    //FIFO queue data structure 
    std::queue<int> BFSqueue;

    //indexing current node in visited and setting equalt to 1 (true)
    //making the node visited
    visited[nodeI] = 1;

    //insert/push current node at the end of the queue
    BFSqueue.push(nodeI);
    
    //neater output for execution output text
    std::cout << "Visited Nodes: ";
    //loop until the queue is empty, then return the completed bfs tree traversal
    while (!BFSqueue.empty())
    {
        //assign the front of the queue to the current node
        nodeI = BFSqueue.front();
        //pop the current node from the queue
        BFSqueue.pop();
        std::cout << "| " << nodeI << " ";

        //loop over the adjacents of the current node (indexed)
        for (auto i : graph.adjacents[nodeI])
        {
            //if the currentnode is not visited...
            if (!visited[i])
            {
                //assign it as visitedand push the node onto the queue
                visited[i] = 1;
                BFSqueue.push(i);
            }
        }
    }
}