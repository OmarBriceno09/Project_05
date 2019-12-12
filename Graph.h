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
    string toStringPostOrderList();
    string toStringSCC();
    string toStringSCCat(int);
    void constructGraphs();
    void constructDependencyGraph(vector<Node>&);
    void constructReverseDependencyGraph();
    vector<Node> get_SCC(int);
    int get_SCC_size();
    bool SelfDepencencyAt(int);

private:
    vector<Node> dependency_nodes;
    vector<Node> reverse_dependency_nodes;
    vector<Node> dep_nodes_copy;
    vector<Node> post_order_list;
    vector<vector<Node>> SCC_lists;
    string toStringChosenGraph(vector<Node>&);
    void addNodetoPostOrder(Node&);
    void RevDepPO_DFS(vector<Node>&);
    void DFSUntil(Node*);
    void DepDFS(vector<Node>&);
    void DFSforSCC(Node*, vector<Node>&);
};


#endif //PROJECT_05_GRAPH_H
