
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;


float dist1 (float node, float next) {
    return pow(node, 2) + pow(next, 2);
};

class Graph1D {
    public: 
        int n;
        int d;
   
        Graph1D(int numVertices) { // constructor
            n = numVertices;
            d = dim;
            vector<vector<tuple<float, int>>> adj(n);
            generateAdj1D(adj, n);
        } 
        
        void generateAdj1D(vector<vector<tuple<float, int>>> adj, int n) {
            for(int u = 0; u < n; u++) { // iterate through nodes
                float nodeVal = float(rand())/float((RAND_MAX));
                for(int v = u + 1; v < n; v++) { // iterate through remaining nodes
                    float nextVal = float(rand())/float((RAND_MAX));
                    float weight = dist1(nodeVal, nextVal); // generate weight
                    adj[u].push_back(tuple(weight, v));
                    adj[v].push_back(tuple(weight, u));
                }
            }
        }

        // bool prune(float weight) {
        //     if weight
        // }
};


int main(int argc, char** argv) {
    srand(time(0));
    char* flag, numpoints, numtrials, dimension;
    if (argc == 5) {
        int flag = int(argv[1]);
        int numpoints = int(argv[2]);
        int numtrials = int(argv[3]);
        int dimension = int(argv[4]);
    }
    Graph1D graph = Graph1D(numpoints);
    return 0;
}