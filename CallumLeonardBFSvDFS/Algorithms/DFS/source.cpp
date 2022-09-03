#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include "graph.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

//using steady_clock for monotonic time, best suits our needs for timing measurements
typedef std::chrono::steady_clock the_clock;

int main()
{
    //simple int to setup the node number input for the graph generation
	//node input used for the assessment 15,30 or 60
    int totalNodes = 60;

    //vector to keep track of whether node has been visited or not, setting all element content of the vector to 0 (false) 
    //could have represented the vector of type bool (personal preference to use type int)
    std::vector<int> visited(totalNodes);
    //setting all elements in the visited vector to 0 (false)
    for (int i = 0; i < totalNodes; i++)
    {
        visited[i] = 0;
    }

    //differnet struct could also be defined to allow for the node population
    //defined as (0,{0,4, 0,18, 0,12}), struct would contain the current node itself

    //populating the vector of edges below, to represent our tree structure 
    //the way that we wish
    std::vector<nodeEdges> nodeEdges = {

        //edges for level 0 (root node)
         {0, 4}, {0, 8}, {0, 12},

         //edges for level 1
         //edges for node 4
         {4,0}, {4,1}, {4,2},
         //edges for node 8
         {8,0}, {8,3}, {8,10},
         //edges for node 12
         {12,0}, {12,1},

         //edges for level 2
         //edges for node 1
         {1,4}, {1,6}, {1,12},
         //edges for node 2
         {2,4},
         //edges for node 3
         {3,8},
         //edges for node 10
         {10,6},{10,8},{10,7},{10,5}, {10,9},

         //edges for level 3
         //edges for node 6
         {6,1}, {6,10},
         //edges for node 7
         {7,10}, {7,11},
         //edges for node 5
         {5,10},
         //edges for node 9
         {9,10},{9,14}, {9,13},{9,11},

         //edges for level 4
         //edges for node 11
         {11,7},{11,23}, {11,16}, {11,24},{11,9},
         //edges for node 14
         {14,9},
         //edges for node 13
         {13,9}, {13,23},

         //edges for level 5
         //edges for node 23
         {23,11},{23,18}, {23,20}, {23,13},
         //edges for node 16
         {16,11}, {16,21},
         //edges for node 24
         {24,11}, {24,18}, {24,15}, {24,19},

         //edges for level 6
         //edges for node 18
         {18,23}, {18,24},
         //edges for node 20
         {20,23},
         //edges for node 21
         {21,16}, {21,25}, {21,26},
         //edges for node 15
         {15,24}, {15,27},
         //edges for node 19
         {19,24}, {19,25},

         //edges for level 7
         //edges for node 25
         {25,21}, {25,17}, {25,22}, {25,19},
         //edges for node 26
         {26,21},
         //edges for node 27
         {27,15}, {27,17}, {27,28}, {27,29},

         //edges for level 8
         //edges for node 17
         {17,25}, {17,27},
         //edges for node 22
         {22,25}, {22,26}, {22,32}, {22,36},
         //edges for node 28
         {28,27},
         //edges for node 29
         {29,27}, {29,26},

         //edges for level 9
         //edges for node 26
         {26,22}, {26,48}, {26,39}, {26,29},
         //edges for node 32
         {32,22}, {32,29},
         //edges for node 36
         {36,22}, {36,48}, {36,42}, {36,43}, {36,50},

         //edges for level 10
         //edges for node 48
         {48,26}, {48,30}, {48, 44}, {48,36},
         //edges for node 39
         {39,26}, {39,44}, {39,28},
         //edges for node 29
         {29,32}, {29,28}, {29,51},
         //edges for node 42
         {42,36},
         //edges for node 43
         {43,36},
         //edges for node 50
         {50,36}, {50,30}, {50,40},

         //edges for level 11
         //edges for node 30
         {30,48}, {30,50},
         //edges for node 44
         {44,48}, {44,39}, {44,46}, {44,35}, {44,27},
         //edges for node 28
         {28,39}, {28,29},
         //edges for node 51
         {51,29},
         //edges for node 40
         {40,50}, {40,46}, {40,38},

         //edges for level 12
         //edges for node 46
         {46,44}, {46,40},
         //edges for node 35
         {35,44},
         //edges for node 27
         {27,44}, {27,31}, {27,41},
         //edges for node 38
         {38,40}, {38,31}, {38,33}, {38,34}, {38,49},

         //edges for level 13
         //edges for node 31
         {31,27}, {31,37}, {31,47}, {31,45}, {31,38},
         //edges for node 41
         {41,27},
         //edges for node 33
         {33,38},
         //edges for node 34
         {34,38},
         //edges for node 49
         {49,38}, {49,37},

         //edges for level 14
         //edges for node 37
         {37,31}, {37,49},
         //edges for node 47
         {47,31},
         //edges for node 45
         {45,31}, {45,54}, {45,56}, {45,52},

         //edges for level 15
         //edges for node 54
         {54,45}, {54,58}, {54,57},
         //edges for node 56
         {56,45}, {56,53}, {56,55},
         //edges for node 52
         {52,45}, {52,58}, {52,59},

         //edges for level 16
         //edges for node 58
         {58,54}, {58,52},
         //edges for node 57
         {57,54}, {57,59},
         //edges for node 53
         {53,56},
         //edges for node 55
         {55,56},
         //edges for node 59
         {59,52}, {59,57}
    };

   
    //build a graph from the given edges, defintion needs to be AFTER the populated
    //nodeEdges vector
    Graph graph(nodeEdges, totalNodes);
    
	//start timing using "the_clock"
	the_clock::time_point start = the_clock::now();

	//initalizing i to the 0th node (root node), to start traversal of other sub-nodes
    //initalizing i to ANY value within the node scope starts the DFS traversal at given node I (I = 5 starts traversal from node 5 in the graph)
    int nodeI = 0;
	
	//pass in number of nodes, pass in unvisited parameter to be visited and then generate graph based on inputs
	//access algorithm function through the graph class
	graph.DFSAlgorithm(nodeI, visited, graph);

	//end timing
	the_clock::time_point end = the_clock::now();

	//compute algorithm execution time by minusing end from start and storing the content in time_taken variable
	auto time_taken = duration_cast<milliseconds>(end - start).count();
	std::cout << "| ";
	std::cout << std::endl;
	std::cout << "It took " << time_taken << " ms to compute the algorithm." << std::endl;

	//pause the algorithm and wait for keystroke to allow for the individual .exe to be ran and read outside of visual studio
    std::cin.get();
    return 0;
}