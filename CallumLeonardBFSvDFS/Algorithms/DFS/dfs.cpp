#include <iostream>
#include <chrono>
#include <stack>
#include <thread>
#include <list>
#include <vector>
#include "graph.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

//using steady_clock for monotonic time, best suits our needs for timing measurements
typedef std::chrono::steady_clock the_clock;

//args currentnodeposition, vector of visited ndoes, the graph containing edges/adjacency list
//perform DFS start at node location X and traverse from node X based on nodeI input
void Graph::DFSAlgorithm(int nodeI, std::vector<int>& visited, Graph const& graph)
{
    //LIFO stack data structure 
    std::stack<int> stack;

    //insert/push current node into the stack
    stack.push(nodeI);

    //neater output for execution output text
    std::cout << "Visited Nodes: ";

    //loop until the stack is empty, then return the completed bfs tree traversal
    while (!stack.empty())
    {
        //assign the top of the stack to the current node
        nodeI = stack.top();
        //pop the current node from the stack
        stack.pop();

        //if the node has already been discovered, break out of 1 iterations (this iteration)
        //and force next iteration
        if (visited[nodeI]) {

            continue;
        }

        //if the node is not discovered assign it to be discovered now
        visited[nodeI] = 1;
        //print the popped and then newly discovered node
        std::cout << "| " << nodeI << " ";

        //use a reverse iterator to iterate over the adjacents of nodeI (current node) whilst there are still
        //adjacents to iterate over
		//standard iterator would traverse through the right subtree of nodeI (current node) first.
        for (auto it = graph.adjacents[nodeI].rbegin(); it != graph.adjacents[nodeI].rend(); it++)
        {
            //dereference the iterator and assign deref value into int i
            int i = *it;
            //check if I (current node) exists in visited  and push onto the stack if not visited
            if (!visited[i]) {
                //std::cout << "--------------------------" << std::endl;
                //std::cout << i << std::endl;
                stack.push(i);
            }
        }
    }
}