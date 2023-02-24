
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

float dist2 (tuple<float,float> node, tuple<float,float> next) {
    float x1;
    float y1;
    float x2;
    float y2;
    tie(x1, y1) = node;
    tie(x2,y2) = next;
    return pow((x2-x1), 2) + pow((y2-y1), 2);
};

class Graph {
    public: 
        int n;
        int d;
   
        Graph(int numVertices, int dim) { // constructor
            n = numVertices;
            d = dim;
            vector<vector<tuple<float, int>>> adj(n);
            if (d == 1) {
                generateAdj1D(adj, n);
            }
            else if (d == 2) {
                generateAdj2D(adj, n);
            }    

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
        void generateAdj2D(vector<vector<tuple<float, int>>> adj, int n) {
            for(int u = 0; u < n; u++) { // iterate through nodes
                tuple<float,float> nodeVal = tuple(float(rand())/float((RAND_MAX)),float(rand())/float((RAND_MAX)));
                for(int v = u + 1; v < n; v++) { // iterate through remaining nodes
                    tuple<float,float> nextVal = tuple(float(rand())/float((RAND_MAX)),float(rand())/float((RAND_MAX)));
                    float weight = dist2(nodeVal, nextVal); // generate weight
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
    Graph graph = Graph(numpoints, dimension);
    return 0;
}