//
// Created by OmarB on 12/10/2019.
//

#ifndef PROJECT_05_GRAPH_H
#define PROJECT_05_GRAPH_H
#include <fstream>
#include <iostream>//for output ---- delete later
#include <vector>
#include "Node.h"
#include "Rule.h"

class Graph {
public:
    Graph();
    ~Graph();
    void evaluate_Rule(Rule&);
    void addNode(Node&);
    string toStringDependencyGraph();
    string toStringReverseDependencyGraph();
    void constructGraphs();
    void constructDependencyGraph();
    void constructReverseDependencyGraph();

private:
    vector<Node> dependency_nodes;
    vector<Node> reverse_dependency_nodes;
};


#endif //PROJECT_05_GRAPH_H
