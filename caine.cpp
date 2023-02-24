#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
//using namespace std;
#include <chrono>
using namespace std::chrono;

typedef std::pair<int, int> intPair;

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
        // return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
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
        // int x = FIND(vert1);
        // int y = FIND(vert2);

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

    //std::vector<intPair> krusty() {
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
                tree_weight = tree_weight + edges[i].first;
                MST_edges.push_back(std::make_pair(vert1, vert2));
                UNION(vert1, vert2);
            }
        }

        /*
        std::cout << "The Edges of our MST!" << std::endl;
        for (int i = 0; i < MST_edges.size(); i++){
            std::cout << MST_edges[i].first << " " << MST_edges[i].second << std::endl;
        }
        */


        // std::cout << "The maximum edge weight is: " << max_edge_weight << std::endl;

        return tree_weight; // max_edge_weight; //MST_edges;
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
    // Create a graph given in the above diagram
    /*
    Graph g_e1(7);
    g_e1.add_edge(4, 0, 1);
    g_e1.add_edge(3, 0, 2);
    g_e1.add_edge(2, 2, 1);
    g_e1.add_edge(4, 1, 3);
    g_e1.add_edge(1, 2, 3);
    g_e1.add_edge(2, 3, 6);
    g_e1.add_edge(5, 3, 4);
    g_e1.add_edge(5, 4, 5);
    g_e1.add_edge(3, 2, 4);
    g_e1.sort_edges();
    g_e1.krusty();
    g_e1.print_graph();

    Graph g_e2(8);
    g_e2.add_edge(1, 0, 1);
    g_e2.add_edge(6, 1, 2);
    g_e2.add_edge(10, 2, 3);
    g_e2.add_edge(3, 3, 4);
    g_e2.add_edge(2, 3, 6);
    g_e2.add_edge(3, 6, 4);
    g_e2.add_edge(4, 6, 5);
    g_e2.add_edge(3, 5, 4);
    g_e2.add_edge(3, 2, 6);
    g_e2.add_edge(5, 7, 6);
    g_e2.add_edge(2, 1, 7);
    g_e2.sort_edges();
    g_e2.krusty();
    g_e2.print_graph();
    */

    /*
    // create a graph on n vertices where the weight of each edge is a random number between 0 and 1
    float n = 5000;
    Graph g_rand(n);


    // the percent change of success you want... what are the odds you get a true MST?
    // float confidence = 0.999;
    const float L = 1; //1 - std::pow(1 - confidence, 1/(n-1));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j){
                float weight = (float)rand() / (float)RAND_MAX;
                if(weight < L){
                    g_rand.add_edge(weight, i, j);
                }
            }
        }
    }

    g_rand.sort_edges();
    g_rand.krusty();
    // g_rand.print_graph();
    */

    srand(time(0));

    float n_sizes[] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144};
    int num_tests = 5;
    // loop over the # of vertices
    
    for (int n_idx = 0; n_idx < sizeof(n_sizes) / sizeof(n_sizes[0]); n_idx++){
        
        auto start = high_resolution_clock::now(); // time over all tests
        
        float sum_of_tree_weight = 0;
        for (int test_iter = 0; test_iter < num_tests; test_iter++){
            Graph g_rand(n_sizes[n_idx]);
            const float L = 1.3*(2.33*pow(n_sizes[n_idx], -0.833)); //1 - std::pow(1 - confidence, 1/(n-1));
            for (int i = 0; i < n_sizes[n_idx]; i++){
                // for (int j = 0; j < n_sizes[n_idx]; j++){
                for (int j = 0; j < i + 1; j++){
                    if (i != j){
                        float weight = getWeight("square");
                        if(weight < L){
                            g_rand.add_edge(weight, i, j);
                        }
                    }
                }
            }

            g_rand.sort_edges();
            // float max_edge_weight = g_rand.krusty();
            sum_of_tree_weight += g_rand.krusty();
        }
        auto end = high_resolution_clock::now(); // time over all tests
        auto time = duration_cast<microseconds>(end - start);

        std::cout << "The average of the tree weights after " << num_tests << " tests and for n (num vertices) = " << n_sizes[n_idx] << " is: " << sum_of_tree_weight / num_tests << std::endl;
        std::cout << "Average time per run for " << n_sizes[n_idx] << " vertices is " << time.count()/num_tests << std::endl;
    }


    return 0;
}
