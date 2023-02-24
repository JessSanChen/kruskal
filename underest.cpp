#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
//using namespace std;

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <random>

using namespace std;

// float dist2 (std::pair<float,float> node, std::pair<float,float> next) {
//     float x1;
//     float y1;
//     float x2;
//     float y2;
//     std::tie(x1, y1) = node;
//     std::tie(x2,y2) = next;
//     return pow((x2-x1), 2) + pow((y2-y1), 2);
// };

typedef std::pair<int, int> intPair;
bool MAX_WEIGHT = false;

bool sortbyfirst(const std::pair<float, intPair>  &a,
                const std::pair<float, intPair>  &b) {
            return (a.first < b.first);
}

// create a function called CalculateWeight that takes in the options "line" "square" or "cube" and returns the weight of the edge
float getWeight(std::string shape) {
    if (shape == "line"){
        return (float)rand() / (float)RAND_MAX;
    }
    else if (shape == "square"){
        float x1 = (float)rand() / (float)RAND_MAX;
        float y1 = (float)rand() / (float)RAND_MAX;
        float x2 = (float)rand() / (float)RAND_MAX;
        float y2 = (float)rand() / (float)RAND_MAX;
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
    else if (shape == "cube"){
        float x1 = (float)rand() / (float)RAND_MAX;
        float y1 = (float)rand() / (float)RAND_MAX;
        float z1 = (float)rand() / (float)RAND_MAX;
        float x2 = (float)rand() / (float)RAND_MAX;
        float y2 = (float)rand() / (float)RAND_MAX;
        float z2 = (float)rand() / (float)RAND_MAX;
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
    }
    else if (shape == "hypercube"){
        float x1 = (float)rand() / (float)RAND_MAX;
        float y1 = (float)rand() / (float)RAND_MAX;
        float z1 = (float)rand() / (float)RAND_MAX;
        float r1 = (float)rand() / (float)RAND_MAX;
        float x2 = (float)rand() / (float)RAND_MAX;
        float y2 = (float)rand() / (float)RAND_MAX;
        float z2 = (float)rand() / (float)RAND_MAX;
        float r2 = (float)rand() / (float)RAND_MAX;
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2) + pow(r1 - r2, 2));
    }
    else {
        std::cout << "Invalid shape!" << std::endl;
        return 0;
    }
}

float getL(std::string shape, float n) {
    if (shape == "line"){
        return 4.1*pow(n, -0.896);
    }
    else if (shape == "square"){
        return 1.74*pow(n, -0.492);
    }
    else if (shape == "cube"){
        return 3;
    }
    else if (shape == "hypercube"){
        return 4;
    }
    else {
        std::cout << "Invalid shape!" << std::endl;
        return 0;
    }
}

struct SET {
    int parent;
    int rank = 0;
    SET(int parent) {
        this->parent = parent;
    };
};

// Create a class called Graph
class Graph
{

public:
    int V, E = 0;
    std::vector< std::pair<float, intPair> > edges;
    std::vector<intPair> MST_edges;
    std::vector<SET> set_of_sets;

    Graph(int V)
    {
        this->V = V;
        for (int i = 0; i < V; i++){
            SET s(i);
            set_of_sets.push_back(s);
        }
    }

    void add_edge(float weight, int u, int v)
    {
        intPair p = std::make_pair(u, v);
        // instead, add to priority queue
        edges.push_back(make_pair(weight, p));
        E = E + 1;
    }

    void sort_edges(){
        // print the length of edges
        std::sort(edges.begin(), edges.end(), sortbyfirst);
    }

    int FIND(int x){
        if (set_of_sets[x].parent != x){
            set_of_sets[x].parent = FIND(set_of_sets[x].parent);
        }
        return set_of_sets[x].parent;
    }

    void LINK(int x, int y){
        // if x has a higher rank than y,
        // then set set the parent of y to x and increase the rank of x
        if (set_of_sets[x].rank > set_of_sets[y].rank){
            set_of_sets[y].parent = x;
        }
        else if (set_of_sets[x].rank < set_of_sets[y].rank){
            set_of_sets[x].parent = y;
        }
        else if (set_of_sets[x].rank == set_of_sets[y].rank){
            set_of_sets[x].parent = y;
            set_of_sets[y].rank = set_of_sets[y].rank + 1;
        }
    }

    void UNION(int vert1, int vert2){
        int x = FIND(vert1);
        int y = FIND(vert2);
        // set_of_sets[x].parent = y;
        LINK(x, y);
    }

    float krusty() {
        float max_edge_weight = 0;
        float tree_weight = 0;
        for (int i = 0; i < E; i++){
            int vert1 = edges[i].second.first;
            int vert2 = edges[i].second.second;

            // if the left vertex of the edge is in the same set as the right vertex of the edge
            if(FIND(vert1) != FIND(vert2)){
                // this edge is part of the MST, so add it!
                if(edges[i].first > max_edge_weight){
                    max_edge_weight = edges[i].first;
                }
                tree_weight += edges[i].first;
                MST_edges.push_back(std::make_pair(vert1, vert2));
                UNION(vert1, vert2);
            }
        // std::cout << "MST edge count: " << MST_edges.size() << std::endl;
        }

        /*
        std::cout << "The Edges of our MST!" << std::endl;
        for (int i = 0; i < MST_edges.size(); i++){
            std::cout << MST_edges[i].first << " " << MST_edges[i].second << std::endl;
        }
        */

        if (MAX_WEIGHT == true){
            return max_edge_weight;
        }
        else if(MAX_WEIGHT == false){
            return tree_weight;
        }
    }

    void print_graph()
    {
        std::cout << "The Edges of our graph!" << std::endl;
        for (int i = 0; i < E; i++)
        {
            std::cout << edges[i].second.first << " " << edges[i].second.second << " | Weight: " << edges[i].first << std::endl;
        }
    }
};



int main()
{
    srand(time(0));

    //mersenne twister
    // std::random_device rd;     // used to initialise (seed) engine
    // std::mt19937 mt(rd());    // random-number engine used (Mersenne-Twister in this case)

    // thread_local std::mt19937 generator;

    std::mt19937 generator;
    std::random_device random_dev;
    generator.seed(random_dev());
    std::uniform_real_distribution<double> unif(0.0, 1.0);

    float n_sizes[] = {128, 256, 512, 1024, 2048, 4096};//, 8192, 16384, 32768, 65536, 131072, 262144};
    int num_tests = 5;
    // loop over the # of vertices
    // for(int n_idx = 0; n_idx < sizeof(n_sizes) / sizeof(n_sizes[0]); n_idx++){
    for(int p = 7; p < 13; p++) {
        int n = pow(2,p);
        float sum_of_tree_weight = 0;
        float max_of_max_edge_weight = 0;
        for (int test_iter = 0; test_iter < num_tests; test_iter++){
            // std::random_device rd;   
            // std::mt19937 mt(rd());
            // Graph g_rand(n_sizes[n_idx]);
            Graph g_rand(n);
            const float L = 10;//getL("square", n_sizes[n_idx]);
            for (int i = 0; i < n; i++){
                //jess
                // float x1 = float(mt())/float((mt.max()));
                // float y1 = float(mt())/float((mt.max()));
                float x1 = unif(generator);
                float y1 = unif(generator);
                // cout << x1 << " " << y1 << endl;
                for (int j = i + 1; j < n; j++){
                    //jess
                    // float x2 = float(mt())/float((mt.max()));
                    // float y2 = float(mt())/float((mt.max()));
                    float x2 = unif(generator);
                    float y2 = unif(generator);
                    float weight = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
                    // if(weight < L){
                    //     g_rand.add_edge(weight, i, j);
                    // }
                    // std::cout << weight << endl;
                    g_rand.add_edge(weight, i, j);
                    // g_rand.add_edge(weight, j, i);
                }
            }

            g_rand.sort_edges();
            if(MAX_WEIGHT == true){
                float max_edge_weight = g_rand.krusty();
                if (max_edge_weight > max_of_max_edge_weight){
                    max_of_max_edge_weight = max_edge_weight;
                }
            }
            else if (MAX_WEIGHT == false){
                sum_of_tree_weight += g_rand.krusty();
            }
        }

        if( MAX_WEIGHT == 1){
            std::cout << "The maximum MST edge weight after testing " << num_tests << " separate MSTs and for n (num vertices) = " << n << " is: " << max_of_max_edge_weight << std::endl;
        }

        else if (MAX_WEIGHT == 0){
            std::cout << "The average of the tree weights after " << num_tests << " tests and for n (num vertices) = " << n << " is: " << sum_of_tree_weight / num_tests << std::endl;
        }
    }


    return 0;
}