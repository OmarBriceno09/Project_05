//
// Created by OmarB on 12/10/2019.
//

#include "Graph.h"
Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::evaluate_Rule(Rule& c_rule) {
    int the_id = dependency_nodes.size();
    Node node(the_id,&c_rule);
    addNode(node);
}

void Graph::addNode(Node &node) {
    dependency_nodes.push_back(node);
    Node rev_node = node;
    reverse_dependency_nodes.push_back(rev_node);
}

string Graph::toStringDependencyGraph() {
    string the_output="Dependency Graph\n";
    for(int i=0;i<(int)dependency_nodes.size();i++){
        the_output+=dependency_nodes.at(i).toString_rule();
        the_output+= "\n";
    }
    return the_output;
}

string Graph::toStringReverseDependencyGraph() {
    string the_output="Reverse Dependency Graph\n";
    for(int i=0;i<(int)reverse_dependency_nodes.size();i++){
        the_output+=reverse_dependency_nodes.at(i).toString_rule();
        the_output+= "\n";
    }
    return the_output;
}

void Graph::constructGraphs() {
    constructDependencyGraph();
    constructReverseDependencyGraph();
}

void Graph::constructDependencyGraph() {
    for(int i=0;i<(int)dependency_nodes.size();i++){
        for(int j=0;j<(int)dependency_nodes.size();j++){
            dependency_nodes.at(i).checkNode(&dependency_nodes.at(j));

        }
    }
}

void Graph::constructReverseDependencyGraph() {// do this AFTER constructing dependency graph, saves runtime s
    for(int i=0;i<(int)dependency_nodes.size();i++){
        //dependency_nodes.at(i).node_ptr_set
        //cout<<dependency_nodes.at(i).get_id()<<":|s| "<<endl;
        Node c_node;
        for(auto it=dependency_nodes.at(i).node_ptr_set.begin();it!=dependency_nodes.at(i).node_ptr_set.end();++it){
            c_node = (**it);
            reverse_dependency_nodes.at(c_node.get_id()).addEdge(&reverse_dependency_nodes.at(i));
            //cout<<c_node.get_id()<<",";
        }
        //cout<<endl;
    }

    //test debug::
    reverse_dependency_nodes.at(1).visiting();
}