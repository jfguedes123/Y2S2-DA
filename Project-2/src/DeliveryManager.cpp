#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <limits>
#include "DeliveryManager.h"

using namespace std;

// Helper function to create a distance matrix
vector<vector<double>> DeliveryManager::createDistanceMatrix() {
    const vector<Vertex<int>*> &vertices = graph_.getVertexSet();
    auto numVertices = vertices.size();

    vector<vector<double>> distanceMatrix(numVertices, vector<double>(numVertices, -1.0));

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            unsigned int id1 = vertices[i]->getInfo();
            unsigned int id2 = vertices[j]->getInfo();
            double dist = graph_.getDist(id1, id2);

            distanceMatrix[i][j] = dist;
            distanceMatrix[j][i] = dist;
        }
    }

    return distanceMatrix;
}

// Display the main menu and handle user input
void DeliveryManager::loadGraph() {
    cout << "===========START MENU===========\n";
    cout << "Select a Graph: \n";
    cout << "1. Toy Graphs\n";
    cout << "2. Real World Graphs\n";
    cout << "3. Fully Connected Graphs\n";
    cout << "0. Exit\n";
    cout << "================================\n";
    int option;
    cout << "Option: ";
    cin >> option;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n";
        return;
    }
    switch(option) {
        case 1:
            loadToyGraph();
            break;
        case 2:
            loadRealGraph();
            break;
        case 3:
            loadFullyConnectedGraph();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option\n";
            break;
    }
}

// Display the toy graph menu and handle user input
void DeliveryManager::loadToyGraph() {
    cout << "================================\n";
    cout << "Load a Toy Graph: \n";
    cout << "1. Shipping \n";
    cout << "2. Stadiums \n";
    cout << "3. Tourism\n";
    cout << "4. Other\n";
    cout << "5. Back\n";
    cout << "0. Exit\n";
    cout << "================================\n";
    int option;
    cout << "Option: ";
    cin >> option;
    cout << "\n...LOADING THE GRAPH...\n\n";
    string graphFile;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n";
        return;
    }
    switch(option) {
        case 1:
            readToyGraph("../Graphs/Toy-Graphs/shipping.csv");
            apply_algorithm();
            break;
        case 2:
            readToyGraph("../Graphs/Toy-Graphs/stadiums.csv");
            apply_algorithm();
            break;
        case 3:
            readToyGraph("../Graphs/Toy-Graphs/tourism.csv");
            apply_algorithm();
            break;
        case 4:
            cout << "Enter the path to the file with the graph: ";
            cin >> graphFile;
            readToyGraph(graphFile);
            apply_algorithm();
            break;
        case 5:
            loadGraph();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option\n";
            loadToyGraph();
            break;
    }
}

// Display the real-world graph menu and handle user input
void DeliveryManager::loadRealGraph() {
    cout << "================================\n";
    cout << "Load graph: \n";
    cout << "1. Graph 1\n";
    cout << "2. Graph 2\n";
    cout << "3. Graph 3\n";
    cout << "4. Other\n";
    cout << "0. Exit\n";
    cout << "================================\n";
    int option;
    cout << "Option: ";
    cin >> option;
    cout << "\n...LOADING THE GRAPH...\n\n";
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n";
        return;
    }

    string edgesFile, nodesFile;
    switch(option) {
        case 1:
            readRealGraph("../Graphs/Real-world Graphs/graph1/nodes.csv", "../Graphs/Real-world Graphs/graph1/edges.csv");
            apply_algorithm();
            break;
        case 2:
            readRealGraph("../Graphs/Real-world Graphs/graph2/nodes.csv", "../Graphs/Real-world Graphs/graph2/edges.csv");
            apply_algorithm();
            break;
        case 3:
            readRealGraph("../Graphs/Real-world Graphs/graph3/nodes.csv", "../Graphs/Real-world Graphs/graph3/edges.csv");
            apply_algorithm();
            break;
        case 4:
            cout << "Enter the path to the file with the nodes: ";
            cin >> nodesFile;
            cout << "Enter the path to the file with the edges: ";
            cin >> edgesFile;
            readRealGraph(nodesFile, edgesFile);
            apply_algorithm();
            break;
        case 0:
            loadGraph();
            return;
        default:
            cout << "Invalid option\n";
            break;
    }
}

// Display the fully connected graph menu and handle user input
void DeliveryManager::loadFullyConnectedGraph() {
    cout << "================================\n";
    cout << "1. Insert number of nodes\n";
    cout << "2. Other files\n";
    cout << "================================\n";
    int option;
    cout << "Option: ";
    cin >> option;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n";
        return;
    }

    string edgesFile, nodesFile, numNodes;
    switch(option) {
        case 1:
            cout << "Enter the number of nodes: ";
            cout << "Valid options: \n- 25; \n- 50; \n- 75; \n- 100; \n- 200; \n- 300; \n- 400; \n- 500; \n- 600; \n- 700; \n- 800; \n- 900;\n";
            cout << "Number of nodes: ";
            cin >> numNodes;
            cout << "\n...LOADING THE GRAPH...\n\n";
            if(numNodes == "25" || numNodes == "50" || numNodes == "75" || numNodes == "100" || numNodes == "200" || numNodes == "300" || numNodes == "400" || numNodes == "500" || numNodes == "600" || numNodes == "700" || numNodes == "800" || numNodes == "900") {
                readFullyConnectedGraph("../Graphs/Extra_Fully_Connected_Graphs/nodes.csv",
                                        "../Graphs/Extra_Fully_Connected_Graphs/edges_" + numNodes + ".csv", stoi(numNodes));
                cout << "Number of vertices: " << graph_.getVertexSet().size() << endl;
                apply_algorithm();
            } else {
                cout << "Invalid number of nodes\n";
                apply_algorithm();
            }
            break;
        case 2:
            cout << "Enter the path to the file with the nodes: ";
            cin >> nodesFile;
            cout << "Enter the path to the file with the edges: ";
            cin >> edgesFile;
            readFullyConnectedGraph(nodesFile, edgesFile, stoi(edgesFile));
            apply_algorithm();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option\n";
            break;
    }
}

// Function to read a toy graph from a file
void DeliveryManager::readToyGraph(const string& edgesFile) {
    // Clear the graph and vertex set
    graph_.clear();
    vertexSet_.clear();
    distances_.clear();

    ifstream file(edgesFile);
    if (!file.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    string line;
    getline(file, line);

    int edgeCount = 0;
    int vertexCount = 0;

    int source, target;
    double weight;

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> source;
        ss.ignore(1);
        ss >> target;
        ss.ignore(1);
        ss >> weight;

        if(vertexSet_.find(source) == vertexSet_.end()) {
            auto vertex = new Vertex<int>(source);
            vertexSet_.insert(make_pair(source, vertex));
            graph_.addVertex(vertex);
            vertexCount++;
        }
        if(vertexSet_.find(target) == vertexSet_.end()) {
            auto vertex = new Vertex<int>(target);
            vertexSet_.insert(make_pair(target, vertex));
            graph_.addVertex(vertex);
            vertexCount++;
        }

        auto sourceVertex = vertexSet_.find(source)->second;
        auto targetVertex = vertexSet_.find(target)->second;
        graph_.addBidirectionalEdge(sourceVertex, targetVertex, weight);
        edgeCount++;
    }

    if(edgeCount == vertexCount * (vertexCount - 1) / 2) {
        graph_.setFullyConnected(true);
    }

    distances_ = createDistanceMatrix();
    file.close();
}

// Function to read a real-world graph from files
void DeliveryManager::readRealGraph(const string& nodesFile, const string& edgesFile) {
    // Clear the graph and vertex set
    graph_.clear();
    vertexSet_.clear();
    distances_.clear();

    ifstream file(nodesFile);
    if (!file.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    int edgeCount = 0;
    int vertexCount = 0;

    string line;
    getline(file, line);

    int id;
    double latitude, longitude;

    clock_t startNodes = clock();

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> id;
        ss.ignore(1);
        ss >> longitude;
        ss.ignore(1);
        ss >> latitude;

        if (vertexSet_.find(id) == vertexSet_.end()) {
            Vertex<int>* vertex = new Vertex<int>(id, longitude, latitude);
            vertexSet_.insert(make_pair(id, vertex));
            graph_.addVertex(vertex);
            vertexCount++;
        }
    }

    clock_t endNodes = clock();
    cout << "Time to read nodes: " << fixed << setprecision(6) << (double)(endNodes - startNodes) / CLOCKS_PER_SEC << " seconds.\n";
    file.close();

    ifstream fileE(edgesFile);
    if (!fileE.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    int source, target;
    double weight;

    distances_ = vector<vector<double>>(vertexSet_.size(), vector<double>(vertexSet_.size(), -1.0));

    getline(fileE, line);

    clock_t startEdges = clock();

    while (getline(fileE, line)) {
        stringstream ss(line);
        ss >> source;
        ss.ignore(1);
        ss >> target;
        ss.ignore(1);
        ss >> weight;

        if (vertexSet_.find(source) == vertexSet_.end() || vertexSet_.find(target) == vertexSet_.end()) continue;

        auto sourceVertex = vertexSet_.find(source)->second;
        auto targetVertex = vertexSet_.find(target)->second;

        graph_.addBidirectionalEdge(sourceVertex, targetVertex, weight);
        distances_[source][target] = weight;
        distances_[target][source] = weight;
        edgeCount++;
    }

    clock_t endEdges = clock();
    cout << "Time to read edges: " << fixed << setprecision(6) << (double)(endEdges - startEdges) / CLOCKS_PER_SEC << " seconds.\n";
    fileE.close();
    graph_.setHasCoords(true);

    if(edgeCount == vertexCount * (vertexCount - 1) / 2) {
        graph_.setFullyConnected(true);
    }
}

// Function to read a fully connected graph from files
void DeliveryManager::readFullyConnectedGraph(const std::string &nodesFile, const std::string &edgesFile, int numNodes) {
    // Clear the graph and vertex set
    graph_.clear();
    vertexSet_.clear();
    distances_.clear();

    ifstream file(nodesFile);
    if (!file.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    int edgeCount = 0;
    int vertexCount = 0;

    string line;
    getline(file, line);

    int id;
    double latitude, longitude;
    int counter = 0;

    while (getline(file, line) && counter < numNodes) {
        stringstream ss(line);
        ss >> id;
        ss.ignore(1);
        ss >> longitude;
        ss.ignore(1);
        ss >> latitude;

        Vertex<int>* vertex = new Vertex<int>(id, longitude, latitude);
        vertexSet_.insert(make_pair(id, vertex));
        graph_.addVertex(vertex);
        vertexCount++;
        counter++;
    }

    file.close();

    file.open(edgesFile);
    if (!file.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    int source, target;
    double weight;

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> source;
        ss.ignore(1);
        ss >> target;
        ss.ignore(1);
        ss >> weight;

        auto sourceVertex = vertexSet_.find(source)->second;
        auto targetVertex = vertexSet_.find(target)->second;
        graph_.addBidirectionalEdge(sourceVertex, targetVertex, weight);
        edgeCount++;
    }

    if(edgeCount == vertexCount * (vertexCount - 1) / 2) {
        graph_.setFullyConnected(true);
    }

    file.close();
    distances_ = createDistanceMatrix();
}

// Print details of the toy graph
void DeliveryManager::printToy() {
    for(auto vertex : graph_.getVertexSet()){
        cout << "Vertex " << vertex->getInfo() << ":\n";
        for(auto edge : vertex->getAdj()){
            cout << "  -> " << edge->getDest()->getInfo() << " (weight:" << edge->getWeight() << ")\n";
        }
    }
    cout << endl;
}

// Print details of the real-world graph
void DeliveryManager::printReal() {
    for(auto vertex : graph_.getVertexSet()){
        cout << "Vertex " << vertex->getInfo() << ":\n";
        cout << "  Latitude: " << vertex->getLatitude() << endl;
        cout << "  Longitude: " << vertex->getLongitude() << endl;
    }
    cout << endl;
}

// Print details of the fully connected graph
void DeliveryManager::printFullyConnectedGraph(string numEdges) {
    int n = stoi(numEdges);
    for(auto vertex : graph_.getVertexSet()){
        cout << "Vertex " << vertex->getInfo() << ":\n";
        for(auto edge : vertex->getAdj()) {
            cout << "  -> " << edge->getDest()->getInfo() << " (weight:" << edge->getWeight() << ")\n";
        }
    }
    cout << graph_.getVertexSet().size() << " vertices\n";
}

// Backtracking algorithm to solve TSP
void DeliveryManager::backtrackingAux(Vertex<int> * &vertex, std::vector<Vertex<int> *> &path, double& cost, double &minCost, std::vector<Vertex<int> *> &bestPath) {
    if (cost >= minCost) return;

    vertex->setVisited(true);
    path.push_back(vertex);

    if (path.size() == graph_.getVertexSet().size()) {
        for (const auto& edge: vertex->getAdj()) {
            if (edge->getDest() == graph_.getVertexSet()[0]){
                cost += edge->getWeight();
                path.push_back(graph_.getVertexSet()[0]);

                if (cost < minCost) {
                    minCost = cost;
                    bestPath = path;
                }

                cost -= edge->getWeight();
                path.pop_back();
                break;
            }
        }
        path.pop_back();
        vertex->setVisited(false);
        return;
    }

    priority_queue<Edge<int>*, vector<Edge<int>*>, CompareEdges> pq;
    for (auto edge : vertex->getAdj()) {
        pq.push(edge);
    }

    while (!pq.empty()) {
        auto edge = pq.top();
        pq.pop();

        Vertex<int> * dest = edge->getDest();
        double weight = edge->getWeight();

        if (cost + weight >= minCost) break;

        if (!dest->isVisited()){
            cost += weight;
            dest->setVisited(true);
            backtrackingAux(dest, path, cost, minCost, bestPath);
            dest->setVisited(false);
            cost -= weight;
        }
    }

    path.pop_back();
    vertex->setVisited(false);
}

// Main function for the backtracking algorithm
void DeliveryManager::backtracking() {
    clock_t start = clock();
    vector<Vertex<int>*> path, bestPath;
    double distance = 0, minDistance = numeric_limits<double>::max();
    auto vertices = graph_.getVertexSet();

    for (const auto& vertex: vertices) vertex->setVisited(false);

    backtrackingAux(graph_.getVertexSet()[0], path, distance, minDistance, bestPath);

    clock_t end = clock();

    cout << "\n========= BACKTRACKING =========\n";

    if (bestPath.size() != (vertexSet_.size() + 1)) {
        cout << "No solution found\n";
        if((double)(end - start) / CLOCKS_PER_SEC < 1) {
            cout << "Time: " << fixed << setprecision(3) << (double)(end - start) / 1000 << " milliseconds.\n";
        } else {
            cout << "Time: " << fixed << setprecision(6) << (double)(end - start) / CLOCKS_PER_SEC << " seconds.\n";
        }
        cout << "\n\n Press any key to continue...\n";
        string key;
        cin >> key;
        apply_algorithm();
    }

    cout << "Path: ";
    cout << bestPath[0]->getInfo();

    for (int i = 1; i < bestPath.size(); i++) {
        cout << " -> " << bestPath[i]->getInfo();
    }

    if (minDistance >= 1000) {
        cout << "\nTotal Distance: " << minDistance / 1000 << " kilometers" << endl;
    } else {
        cout << "\nTotal Distance: " << minDistance << " meters" << endl;
    }
    if (((double)(end - start) / CLOCKS_PER_SEC) < 1) {
        cout << "Time: " << fixed << setprecision(3) << (double)(end - start) / 1000  << " milliseconds.\n";
    } else {
        cout << "Time: " << fixed << setprecision(6) << (double)(end - start) / CLOCKS_PER_SEC << " seconds.\n";
    }

    cout << "================================\n";
    cout << "\n\nPress any key to continue...\n";
    string key;
    cin >> key;
    apply_algorithm();
}

// Helper function for pre-order traversal
double DeliveryManager::preOrder(vector<Vertex<int>*>& path, Vertex<int>* &current) {
    double distance = 0;
    stack<Vertex<int>*> stack;
    stack.push(current);
    int i = 0;

    while (!stack.empty()) {
        Vertex<int>* vertex = stack.top();
        stack.pop();
        path.push_back(vertex);
        vertex->setVisited(true);

        if(i >= 1) {
            double weight = distances_[path[i-1]->getInfo()][path[i]->getInfo()];
            if(weight == -1.0) {
                weight = graph_.haversine(path[i-1]->getLatitude(), path[i-1]->getLongitude(), path[i]->getLatitude(), path[i]->getLongitude());
                distances_[path[i-1]->getInfo()][path[i]->getInfo()] = weight;
                distances_[path[i]->getInfo()][path[i-1]->getInfo()] = weight;
            }
            distance += weight;
        }

        for(auto it = vertex->sons.rbegin(); it != vertex->sons.rend(); it++) {
            Vertex<int>* son = *it;
            if(!son->isVisited()) {
                stack.push(son);
            }
        }
        i++;
    }
    path.push_back(current);
    distance += distances_[path[path.size()-2]->getInfo()][path[path.size()-1]->getInfo()];
    return distance;
}

// Function to generate a minimum spanning tree using Prim's algorithm
void DeliveryManager::primMinimumCostSpanningTree() {
    for(const auto& vertex : graph_.getVertexSet()) {
        vertex->setVisited(false);
        vertex->sons.clear();
    }

    Vertex<int>* origin = graph_.getVertexSet()[0];
    origin->setVisited(true);

    priority_queue<Edge<int>*, vector<Edge<int>*>, CompareEdges> pq;
    for (auto edge : origin->getAdj()) {
        pq.push(edge);
    }

    while(!pq.empty()) {
        auto edge = pq.top();
        pq.pop();

        auto dest = edge->getDest();
        if(!dest->isVisited()) {
            dest->setVisited(true);
            edge->getOrig()->sons.push_back(dest);

            for (auto vertex : graph_.getVertexSet()) {
                if(vertex->isVisited()) continue;
                Edge<int>* newEdge = graph_.getEdge(dest, vertex);
                if (newEdge == nullptr) {
                    if(graph_.usesCoords()) {
                        double weight = graph_.haversine(dest->getLatitude(), dest->getLongitude(), vertex->getLatitude(), vertex->getLongitude());
                        distances_[dest->getInfo()][vertex->getInfo()] = weight;
                        distances_[vertex->getInfo()][dest->getInfo()] = weight;
                        newEdge = new Edge<int>(dest, vertex, weight);
                    } else {
                        continue;
                    }
                }
                pq.push(newEdge);
            }
        }
    }
}

// Triangular approximation heuristic for TSP
void DeliveryManager::triangularApproximation() {
    clock_t start = clock();

    vector<Vertex<int>*> path;
    primMinimumCostSpanningTree();

    for(auto vertex : graph_.getVertexSet()) { vertex->setVisited(false); }

    double totalDistance = preOrder(path, graph_.getVertexSet()[0]);

    clock_t end = clock();

    if (path.size() != (vertexSet_.size() + 1)) {
        cout << "No solution found\n";
        if((double)(end - start) / CLOCKS_PER_SEC < 1) {
            cout << "Time: " << fixed << setprecision(3) << (double)(end - start) / 1000 << " milliseconds.\n";
        } else {
            cout << "Time: " << fixed << setprecision(6) << (double)(end - start) / CLOCKS_PER_SEC << " seconds.\n";
        }
        cout << "\n\nPress any key to continue...\n";
        string key;
        cin >> key;
        apply_algorithm();
    }

    cout << "\n========= TRIANGULAR APPROXIMATION HEURISTIC =========\n";
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i]->getInfo();
        if (i != path.size() - 1) cout << " -> ";
    }
    if (totalDistance >= 1000) {
        cout << "\nTotal Distance: " << totalDistance / 1000 << " kilometers" << endl;
    } else {
        cout << "\nTotal Distance: " << totalDistance << " meters" << endl;
    }
    if (((double)(end - start) / CLOCKS_PER_SEC) < 1) {
        cout << "Time: " << fixed << setprecision(3) << (double)(end - start) / 1000 << " milliseconds.\n";
    } else {
        cout << "Time: " << fixed << setprecision(6) << (double)(end - start) / CLOCKS_PER_SEC << " seconds.\n";
    }
    cout << "======================================================\n";
    cout << "\n\nPress any key to continue...\n";
    string key;
    cin >> key;
    apply_algorithm();

    for (const auto& vertex : graph_.getVertexSet()) {
        vertex->setVisited(false);
    }
}

// Nearest neighbor algorithm for TSP starting from a specified vertex
void DeliveryManager::nearestNeighbor(int startVertex, vector<Vertex<int> *> &path, double& totalDistance) {
    auto vertices = graph_.getVertexSet();
    auto numVertices = vertices.size();
    bool found = true;

    Vertex<int>* currentVertex = vertices[startVertex];
    currentVertex->setVisited(true);
    path.push_back(currentVertex);

    while (path.size() < numVertices && found) {
        priority_queue<Edge<int>*, vector<Edge<int>*>, CompareEdges> pq;
        for (auto edge: currentVertex->getAdj()) { pq.push(edge); }
        found = false;

        while (!pq.empty()) {
            auto edge = pq.top();
            pq.pop();

            Vertex<int>* dest = edge->getDest();
            double weight = edge->getWeight();

            if (!dest->isVisited()) {
                totalDistance += weight;
                dest->setVisited(true);
                path.push_back(dest);
                currentVertex = dest;
                found = true;
                break;
            }
        }
    }

    path.push_back(graph_.getVertexSet()[0]);
    totalDistance += distances_[path[path.size()-2]->getInfo()][path[path.size()-1]->getInfo()];
}

// Lin-Kernighan heuristic for TSP
void DeliveryManager::linKernighan(vector<Vertex<int> *> &path, double& distance){
    vector<Vertex<int>*>& bestPath = path;
    double bestDistance = distance;
    bool improved = true;
    auto pathSize = bestPath.size();

    while (improved) {
        improved = false;
        for (int i = 0; i < pathSize - 2; ++i) {
            for (int j = i + 1; j < pathSize - 1; ++j) {
                vector<Vertex<int>*> newPath = bestPath;
                reverseSubpath(newPath, i + 1, j);

                double newDistance = bestDistance
                                     - distances_[bestPath[i + 1]->getInfo()][bestPath[i]->getInfo()]
                                     - distances_[bestPath[j + 1]->getInfo()][bestPath[j]->getInfo()]
                                     + distances_[newPath[i + 1]->getInfo()][newPath[i]->getInfo()]
                                     + distances_[newPath[j + 1]->getInfo()][newPath[j]->getInfo()];

                if (newDistance < bestDistance) {
                    bestPath = newPath;
                    bestDistance = newDistance;
                    improved = true;
                }
            }
        }
    }

    path = bestPath;
    distance = bestDistance;
}

// Helper function to reverse a subpath in the Lin-Kernighan algorithm
void DeliveryManager::reverseSubpath(vector<Vertex<int> *> &path, int i, int j) {
    while (i < j) {
        swap(path[i], path[j]);
        ++i;
        --j;
    }
}

// Main function for the Lin-Kernighan heuristic
void DeliveryManager::LK() {
    cout << "\n\n================================\n";
    cout << "Lin-Kernighan: \n";
    cout << "================================\n";

    clock_t start = clock();
    vector<Vertex<int>*> path;

    for (const auto& vertex: graph_.getVertexSet()) { vertex->setVisited(false); }

    double distance = 0;
    nearestNeighbor(0, path, distance);

    if (path.size() != (vertexSet_.size() + 1)) {
        cout << "No solution found\n";
        if((double)(clock() - start) / CLOCKS_PER_SEC < 1) {
            cout << "Time: " << fixed << setprecision(3) << (double)(clock() - start) / 1000 << " milliseconds.\n";
        } else {
            cout << "Time: " << fixed << setprecision(6) << (double)(clock() - start) / CLOCKS_PER_SEC << " seconds.\n";
        }
        cout << "\n\n Press any key to continue...\n";
        string key;
        cin >> key;
        apply_algorithm();
    }

    if (distance >= 1000) {
        cout << "Distance calculated with Nearest Neighbor: " << distance / 1000 << " kilometers. \n" << endl;
    } else {
        cout << "Distance calculated with Nearest Neighbor: " << distance << " meters. \n" << endl;
    }

    if((double)(clock() - start) / CLOCKS_PER_SEC < 1) {
        cout << "Time: " << fixed << setprecision(3) << (double)(clock() - start) / 1000 << " milliseconds.\n";
    } else {
        cout << "Time: " << fixed << setprecision(6) << (double)(clock() - start) / CLOCKS_PER_SEC << " seconds.\n";
    }

    clock_t start2 = clock();
    linKernighan(path, distance);

    if (distance >= 1000) {
        cout << "\nDistance calculated with Lin-Kernighan: " << distance / 1000 << " kilometers. \n" << endl;
    } else {
        cout << "Distance calculated with Lin-Kernighan: " << distance << " meters. \n" << endl;
    }

    if((double)(clock() - start2) / CLOCKS_PER_SEC < 1) {
        cout << "Time: " << fixed << setprecision(3) << (double)(clock() - start2) / 1000 << " milliseconds.\n";
    } else {
        cout << "Time: " << fixed << setprecision(6) << (double)(clock() - start2) / CLOCKS_PER_SEC << " seconds.\n";
    }
    cout << "\n\nPress any key to continue...\n";
    string key;
    cin >> key;
    apply_algorithm();
}

// Function to check if the graph is connected
bool DeliveryManager::isGraphConnected(int startVertex) {
    unordered_map<int, bool> visited;
    queue<int> q;
    q.push(startVertex);
    visited[startVertex] = true;

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        for (const auto& edge : graph_.findVertex(vertex)->getAdj()) {
            int neighbor = edge->getDest()->getInfo();
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return visited.size() == vertexSet_.size();
}

// Function to solve the TSP for real-world graphs
void DeliveryManager::solveTSPRealWorld(int startVertex) {
    if (!isGraphConnected(startVertex)) {
        cout << "The graph is not fully connected. No feasible TSP path exists." << endl;
        return;
    }

    clock_t start = clock();
    vector<Vertex<int>*> tspPath;
    double totalDistance = 0;

    nearestNeighbor(startVertex, tspPath, totalDistance);

    if (tspPath.size() != vertexSet_.size() + 1) {
        cout << "No feasible path exists to visit all nodes." << endl;
        loadGraph();
    }

    clock_t end = clock();
    cout << "TSP Path: ";
    for (auto vertex : tspPath) {
        cout << vertex->getInfo() << " ";
    }
    cout << endl;

    if (totalDistance >= 1000) {
        cout << "Total Distance: " << totalDistance / 1000 << " kilometers" << endl;
    } else {
        cout << "Total Distance: " << totalDistance << " meters" << endl;
    }

    if((double)(clock() - start) / CLOCKS_PER_SEC < 1) {
        cout << "Time: " << fixed << setprecision(3) << (double)(clock() - start) / 1000 << " milliseconds.\n";
    } else {
        cout << "Time: " << fixed << setprecision(6) << (double)(clock() - start) / CLOCKS_PER_SEC << " seconds.\n";
    }

    loadGraph();
}

// Function to display the algorithm selection menu
void DeliveryManager::apply_algorithm() {
    cout << "\n================================\n";
    cout << "Choose the algorithm to apply: \n";
    cout << "1. Backtracking\n";
    cout << "2. Triangular\n";
    cout << "3. Lin-Kernighan\n";
    cout << "4. Real-World TSP\n";
    cout << "0. Exit\n";
    cout << "================================\n";
    int option;
    cout << "Option: ";
    cin >> option;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input\n";
        return;
    }
    string choice;
    switch(option) {
        case 1:
            if (vertexSet_.size() >= 15) {
                cout << "================================\n";
                cout << "The backtracking algorithm is not recommended for graphs with more than 15 vertices\n";
                cout << "Do you want to continue? (y/n): ";
                cin >> choice;
                if (choice == "n") {
                    apply_algorithm();
                    break;
                }
                if (choice != "y" && choice != "n") {
                    cout << "Invalid option\n";
                    apply_algorithm();
                    break;
                }
            }
            backtracking();
            break;
        case 2:
            triangularApproximation();
            break;
        case 3:
            if (!graph_.isFullyConnected()) {
                cout << "================================\n";
                cout << "The Lin-Kernighan algorithm requires a fully connected graph\n";
                cout << "Do you want to continue? (y/n): ";
                cin >> choice;
                if (choice == "n") {
                    apply_algorithm();
                    break;
                }
                if (choice != "y" && choice != "n") {
                    cout << "Invalid option\n";
                    apply_algorithm();
                    break;
                }
            }
            LK();
            break;
        case 4:
            cout << "Enter the starting vertex: ";
            int startVertex;
            cin >> startVertex;
            solveTSPRealWorld(startVertex);
            break;
        case 0:
            loadGraph();
            return;
        default:
            cout << "Invalid option\n";
            apply_algorithm();
            break;
    }
}
