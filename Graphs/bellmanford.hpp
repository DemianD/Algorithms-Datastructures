#ifndef BELLMANFORD_HPP
#define BELLMANFORD_HPP

#include "graph.hpp"
#include <deque>
using std::deque;
#include <vector>
using std::vector;
#include <limits>
using std::numeric_limits;

class BellmanFord {
    public:
    BellmanFord(GraphWithEdgeData<DIRECTED,int>& G, int s, vector<int>& P, vector<int>& D){
        D = vector<int>(G.numberOfVertices(),numeric_limits<int>::max());
        P = vector<int>(G.numberOfVertices(),-1);
        P[s] = 0;
        D[s] = 0;


    }    
}

#endif