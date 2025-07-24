#ifndef DELIVERYMANAGER_H
#define DELIVERYMANAGER_H

#include "../data_structures/Graph.h"
#include "../data_structures/Heap.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "../data_structures/UFDS.h"

#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;

class DeliveryManager {
private:
    Graph<int> graph_;
    vector<vector<double>> distances_;
    unordered_map<int, Vertex<int>*> vertexSet_;

public:
    /**
     * @brief Creates a distance matrix for the graph.
     *
     * This function creates a distance matrix for the graph, where each entry (i, j) represents the distance between vertex i and vertex j.
     * The distance is calculated using the `getDist` method of the graph.
     * If there is no path between two vertices, the distance is set to -1.
     *
     * @return A 2D vector representing the distance matrix.
     *
     * @note The time complexity of this function is O(n^2).
     */
    vector<vector<double>> createDistanceMatrix();
    /**
     * @brief Loads a graph based on user input.
     *
     * This function presents a menu to the user with different types of graphs to load. The user is asked to select an option by entering a number.
     * If the user's input is not a number or is not one of the presented options, an error message is printed and the function returns.
     * If the input is a valid option, the corresponding graph loading function is called.
     *
     * @note The time complexity of this function is O(1).
     */
    void loadGraph();
    /**
     * @brief Loads a toy graph based on user input.
     *
     * This function presents a menu to the user with different types of toy graphs to load. The user is asked to select an option by entering a number.
     * If the user's input is not a number or is not one of the presented options, an error message is printed and the function returns.
     * If the input is a valid option, the corresponding toy graph loading function is called.
     *
     * @note The time complexity of this function is O(1).
     */
    void loadToyGraph();
    /**
     * @brief Loads a real-world graph based on user input.
     *
     * This function presents a menu to the user with different real-world graphs to load. The user is asked to select an option by entering a number.
     * If the user's input is not a number or is not one of the presented options, an error message is printed and the function returns.
     * If the input is a valid option, the corresponding real-world graph loading function is called.
     * For option 4, the user is asked to provide the paths to the nodes and edges files.
     *
     * @note The time complexity of this function is O(1).
     */
    void loadRealGraph();
    /**
     * @brief Loads a fully connected graph based on user input.
     *
     * This function presents a menu to the user with different fully connected graphs to load. The user is asked to select an option by entering a number.
     * If the user's input is not a number or is not one of the presented options, an error message is printed and the function returns.
     * If the input is a valid option, the corresponding fully connected graph loading function is called.
     * For option 4, the user is asked to provide the number of nodes.
     *
     * @note The time complexity of this function is O(1).
     */
    void loadFullyConnectedGraph();

    /**
     * @brief Reads a toy graph from a file.
     *
     * This function reads a toy graph from a file. The file should contain the edges of the graph, with each line representing an edge.
     * Each line should be in the format "Origin, Destination, Weight".
     * The function first clears the current graph and then reads the edges from the file, adding the vertices and edges to the graph.
     * If the graph is fully connected, it sets the `fullyConnected` attribute of the graph to true.
     * Finally, it creates a distance matrix for the graph.
     *
     * @param edges The path to the file containing the edges of the graph.
     *
     * @note The time complexity of this function is O(n^2).
     */
    void readToyGraph(const string& edges);
    /**
     * @brief Reads a real-world graph from two files.
     *
     * This function reads a real-world graph from two files. One file should contain the nodes of the graph, with each line representing a node.
     * Each line should be in the format "ID, Longitude, Latitude". The other file should contain the edges of the graph, with each line representing an edge.
     * Each line should be in the format "Origin, Destination, Weight".
     * The function first clears the current graph and then reads the nodes and edges from the files, adding the vertices and edges to the graph.
     * If the graph is fully connected, it sets the `fullyConnected` attribute of the graph to true.
     * Finally, it creates a distance matrix for the graph.
     *
     * @param nodes The path to the file containing the nodes of the graph.
     * @param edges The path to the file containing the edges of the graph.
     *
     * @note The time complexity of this function is O(n^2).
     */
    void readRealGraph(const string& nodes, const string& edges);
    /**
     * @brief Reads a fully connected graph from two files.
     *
     * This function reads a fully connected graph from two files. One file should contain the nodes of the graph, with each line representing a node.
     * Each line should be in the format "ID, Longitude, Latitude". The other file should contain the edges of the graph, with each line representing an edge.
     * Each line should be in the format "Origin, Destination, Weight".
     * The function first clears the current graph and then reads the nodes and edges from the files, adding the vertices and edges to the graph.
     * If the number of edges is equal to the number of vertices choose 2 (n*(n-1)/2), it sets the `fullyConnected` attribute of the graph to true.
     * Finally, it creates a distance matrix for the graph.
     *
     * @param nodes The path to the file containing the nodes of the graph.
     * @param edges The path to the file containing the edges of the graph.
     * @param num_of_nodes The number of nodes to read from the nodes file.
     *
     * @note The time complexity of this function is O(n^2).
     */
    void readFullyConnectedGraph(const string& nodes, const string& edges, int num_of_nodes);

    void printToy();
    void printReal();
    void printFullyConnectedGraph(string n);
    /**
     * @brief Applies a selected algorithm to the graph.
     *
     * This function presents a menu to the user with different algorithms to apply to the graph. The user is asked to select an option by entering a number.
     * If the user's input is not a number or is not one of the presented options, an error message is printed and the function returns.
     * If the input is a valid option, the corresponding algorithm is applied to the graph.
     * For options 1 (Backtracking) and 3 (Lin-Kernighan), if the graph does not meet the requirements for the algorithm (more than 15 vertices for Backtracking, not fully connected for Lin-Kernighan), the user is asked if they want to continue.
     *
     * @note The time complexity of this function is O(1).
     */
    void apply_algorithm();

    /**
     * @brief Applies the Backtracking algorithm to the graph.
     *
     * This function applies the Backtracking algorithm to the graph to find the shortest path that visits all vertices. It uses the `backtrackingAux` function to explore all possible paths.
     * The function measures the time it takes to find the shortest path.
     * If a path that visits all vertices is not found, it prints a message and the time it took to search for the path.
     * If a path that visits all vertices is found, it prints the path, the total distance, and the time it took to find the path.
     * After the function finishes, it asks the user to press any key to continue and then calls the `apply_algorithm` function.
     *
     * @note The time complexity of this function is O(n!).
     */
    void backtracking();
    /**
     * @brief Auxiliary function for the Backtracking algorithm.
     *
     * This function is an auxiliary function for the Backtracking algorithm. It is a recursive function that explores all possible paths in the graph, keeping track of the current path and its cost.
     * If the cost of the current path is greater than the cost of the best path found so far, the function returns.
     * If a path that visits all vertices is found, its cost is compared with the cost of the best path found so far. If it is less, the best path and its cost are updated.
     * The function uses a priority queue to explore the edges in order of their weight, starting with the smallest.
     *
     * @param v The current vertex.
     * @param path The current path.
     * @param cost The cost of the current path.
     * @param minCost The cost of the best path found so far.
     * @param bestPath The best path found so far.
     *
     * @note The time complexity of this function is O(n!).
     */
    void backtrackingAux(Vertex<int> *& v, std::vector<Vertex<int> *> &path, double& cost, double &minCost, std::vector<Vertex<int> *> &bestPath);

    /**
     * @brief Applies the Triangular Approximation heuristic to the graph.
     *
     * This function applies the Triangular Approximation heuristic to the graph to find a path that visits all vertices. The heuristic is based on the idea of creating a minimum cost spanning tree and then performing a pre-order traversal of the tree.
     * The function measures the time it takes to find the path.
     * If a path that visits all vertices is found, it prints the path, the total distance, and the time it took to find the path.
     * After the function finishes, it asks the user to press any key to continue and then calls the `apply_algorithm` function.
     *
     * @note The time complexity of this function is O(E log E + n), where E is the number of edges in the graph and n is the number of vertices. This is because the function uses Prim's algorithm to create a minimum cost spanning tree (O(E log E)) and then performs a pre-order traversal of the tree (O(n)).
     */
    void triangularApproximation();
    /**
     * @brief Performs a pre-order traversal of the graph and calculates the total distance of the path.
     *
     * This function performs a pre-order traversal of the graph starting from a given vertex. It keeps track of the path and the total distance.
     * The function uses a stack to keep track of the vertices to visit. It starts by pushing the starting vertex onto the stack.
     * Then, while the stack is not empty, it pops a vertex from the stack, adds it to the path, and marks it as visited.
     * If the vertex is not the first one in the path, it calculates the distance to the previous vertex in the path and adds it to the total distance.
     * The distance is calculated using the Haversine formula if it has not been calculated before.
     * Then, it pushes all unvisited children of the vertex onto the stack.
     * Finally, it adds the starting vertex to the end of the path and adds the distance to the previous vertex in the path to the total distance.
     *
     * @param path A reference to a vector where the path will be stored.
     * @param current A reference to the starting vertex.
     *
     * @return The total distance of the path.
     *
     * @note The time complexity of this function is O(n).
     */
    double preOrder(vector<Vertex<int>*>& path, Vertex<int>* &current);
    /**
     * @brief Applies the Prim's algorithm to the graph to find the minimum cost spanning tree.
     *
     * This function applies the Prim's algorithm to the graph to find the minimum cost spanning tree. It starts from the first vertex in the graph.
     * The function uses a priority queue to keep track of the edges to explore, starting with the edge with the smallest weight.
     * For each edge, if the destination vertex has not been visited, it is marked as visited and added to the tree.
     * Then, for each unvisited vertex, if there is an edge from the destination vertex to the unvisited vertex, the edge is added to the priority queue.
     * If there is no edge and the graph uses coordinates, the Haversine distance between the vertices is calculated and used as the weight of the edge.
     * The function continues until all vertices have been visited.
     *
     * @note The time complexity of this function is O(E log E), where E is the number of edges in the graph. This is because the function uses a priority queue to keep track of the edges to explore, and each insertion into a priority queue takes O(log E) time.
     */
    void primMinimumCostSpanningTree();

    /**
     * @brief Applies the Nearest Neighbor heuristic to the graph.
     *
     * This function applies the Nearest Neighbor heuristic to the graph to find a path that visits all vertices. The heuristic starts from a given vertex and, at each step, visits the nearest unvisited vertex.
     * The function uses a priority queue to keep track of the edges to explore, starting with the edge with the smallest weight.
     * For each edge, if the destination vertex has not been visited, it is marked as visited, added to the path, and the weight of the edge is added to the total distance.
     * The function continues until all vertices have been visited or there are no more edges to explore.
     * Finally, it adds the starting vertex to the end of the path and adds the distance to the previous vertex in the path to the total distance.
     *
     * @param path A reference to a vector where the path will be stored.
     * @param distance A reference to a double where the total distance of the path will be stored.
     *
     * @note The time complexity of this function is O(n^2).
     */
    void nearestNeighbor(int startvertex, vector<Vertex<int> *> &path, double& distance);
    /**
     * @brief Reverses a subpath of a given path.
     *
     * This function reverses a subpath of a given path. The subpath is specified by two indices, i and j, with i <= j. The function swaps the vertices at indices i and j, then increments i and decrements j, and continues until i >= j.
     *
     * @param path A reference to a vector where the path is stored.
     * @param i The starting index of the subpath.
     * @param j The ending index of the subpath.
     *
     * @note The time complexity of this function is O(n).
     */
    void reverseSubpath(vector<Vertex<int> *> &path, int i, int j);
    /**
     * @brief Applies the Lin-Kernighan heuristic to the graph.
     *
     * This function applies the Lin-Kernighan heuristic to the graph to improve a given path. The heuristic iteratively reverses subpaths of the path to try to reduce the total distance.
     * The function starts with the given path and distance as the best path and distance found so far.
     * Then, it enters a loop that continues until no improvement can be made. In each iteration of the loop, it tries reversing each subpath of the best path found so far.
     * If reversing a subpath results in a shorter path, the new path and distance become the best path and distance found so far, and the loop continues.
     * If no subpath reversal results in a shorter path, the loop ends.
     * Finally, the function updates the given path and distance with the best path and distance found.
     *
     * @param path A reference to a vector where the path will be stored.
     * @param distance A reference to a double where the total distance of the path will be stored.
     *
     * @note The time complexity of this function is O(n^3), where n is the number of vertices in the path. This is because the function tries reversing each subpath of the path, and each reversal takes O(n) time.
     */
    void linKernighan(vector<Vertex<int> *> &path, double& distance);
    /**
     * @brief Applies the Lin-Kernighan heuristic to the graph and prints the results.
     *
     * This function applies the Lin-Kernighan heuristic to the graph to improve a path found by the Nearest Neighbor heuristic. It measures the time it takes to find the path and to improve it, and prints the path, the total distance, and the time it took.
     * The function starts by marking all vertices as unvisited and then applies the Nearest Neighbor heuristic to find a path.
     * If a path that visits all vertices is not found, it prints a message and the time it took, asks the user to press any key to continue, and then calls the `apply_algorithm` function.
     * If a path is found, it prints the total distance and the time it took, and then applies the Lin-Kernighan heuristic to improve the path.
     * Finally, it prints the improved total distance and the time it took to improve the path, asks the user to press any key to continue, and then calls the `apply_algorithm` function.
     *
     * @note The time complexity of this function is O(n^3).
     */
    void LK();

    /**
     * @brief Solves the Travelling Salesman Problem (TSP) for a real-world scenario.
     *
     * This function uses the Nearest Neighbor heuristic to solve the TSP. It starts from a given vertex,
     * then repeatedly visits the nearest unvisited vertex until all vertices have been visited. The path
     * is then outputted along with the total distance and the time taken to compute the path.
     *
     * @param startVertex The starting vertex for the TSP.
     *
     * @note The time complexity of this function is O(n^2), where n is the number of vertices in the graph.
     */
    void solveTSPRealWorld(int startVertex);
    /**
     * @brief Checks if the graph is connected starting from a given vertex.
     *
     * This function uses Breadth-First Search (BFS) to traverse the graph. It starts from a given vertex,
     * then repeatedly visits all unvisited neighbors of the current vertex. If all vertices are visited,
     * the graph is connected.
     *
     * @param startVertex The starting vertex for the BFS.
     *
     * @return True if the graph is connected, false otherwise.
     *
     * @note The time complexity of this function is O(V + E), where V is the number of vertices and E is the number of edges in the graph.
     */
    bool isGraphConnected(int startVertex);
};

#endif // DELIVERYMANAGER_H