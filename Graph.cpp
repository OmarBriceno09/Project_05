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
    Node cp_node = node;
    dep_nodes_copy.push_back(cp_node);//this one will remain unaffected till post order node list is made
}

void Graph::addNodetoPostOrder(Node &node) {
    post_order_list.push_back(node);
}

string Graph::toStringDependencyGraph() {
    string the_output="Dependency Graph\n";
    the_output+=toStringChosenGraph(dependency_nodes);
    return the_output;
}

string Graph::toStringReverseDependencyGraph() {
    string the_output="Reverse Dependency Graph\n";
    the_output+=toStringChosenGraph(reverse_dependency_nodes);
    return the_output;
}

string Graph::toStringPostOrderList() {
    string the_output="Post Order List (from smallest to largest post order #)\n";
    the_output+=toStringChosenGraph(post_order_list);
    return the_output;
}

string Graph::toStringChosenGraph(vector <Node> & the_graph) {
    string the_output="";
    for(int i=0;i<(int)the_graph.size();i++){
        the_output+=the_graph.at(i).toString_rule();
        the_output+= "\n";
    }
    return the_output;
}

string Graph::toStringSCC() {
    string the_output="SCC's\n";
    for(int i=0;i<(int)SCC_lists.size();i++){
        the_output+="Group "+to_string(i)+":\n";
        for(int j=0;j<(int)SCC_lists.at(i).size();j++){
            the_output+="   R"+to_string(SCC_lists.at(i).at(j).get_id())+"|:| "+SCC_lists.at(i).at(j).toString_thisRule()+"\n";
        }
    }
    return the_output;
}

string Graph::toStringSCCat(int i){
    string the_output="";
        for(int j=0;j<(int)SCC_lists.at(i).size();j++){
            the_output+="R"+to_string(SCC_lists.at(i).at(j).get_id());
            if(j != (int)SCC_lists.at(i).size()-1)
                the_output+=',';
        }
    return the_output;
}

void Graph::constructGraphs() {
    constructDependencyGraph(dependency_nodes);// have to do this again for post node list ;(
    cout<<"In graph, is node at 0 self dependent?"<<to_string(dependency_nodes.at(0).selfDependent())<<endl;
    cout<<"In graph, is node at 2 self dependent?"<<to_string(dependency_nodes.at(2).selfDependent())<<endl;
    constructReverseDependencyGraph();
    RevDepPO_DFS(reverse_dependency_nodes);// after post order graph is constructed
    constructDependencyGraph(post_order_list);// link nodes
    DepDFS(post_order_list);
}

void Graph::constructDependencyGraph(vector<Node>& node_list) {
    for(int i=0;i<(int)node_list.size();i++){
        for(int j=0;j<(int)node_list.size();j++){
            node_list.at(i).checkNode(&node_list.at(j));

        }
    }
}

void Graph::constructReverseDependencyGraph() {// do this AFTER constructing dependency graph, saves runtime s
    for(int i=0;i<(int)dependency_nodes.size();i++){
        Node c_node;
        for(auto it=dependency_nodes.at(i).node_ptr_set.begin();it!=dependency_nodes.at(i).node_ptr_set.end();++it){
            c_node = (**it);
            reverse_dependency_nodes.at(c_node.get_id()).addEdge(&reverse_dependency_nodes.at(i));
        }
    }
}

void Graph::RevDepPO_DFS(vector <Node> & node_list) {
    for(int i=0;i<(int)node_list.size();i++){
        if(!node_list.at(i).was_visited()){
            DFSUntil(&node_list.at(i));
        }
    }
}

void Graph::DFSUntil(Node * node) {//dont pass untill it wasn't visited!!
    if(!node->was_visited()){
        node->visiting();
        Node *c_node;
        for(auto it=node->node_ptr_set.begin();it!=node->node_ptr_set.end();++it){
            c_node = (*it);
            DFSUntil(c_node);
        }
        c_node = nullptr;
        delete c_node;
        addNodetoPostOrder(dep_nodes_copy.at(node->get_id()));
    }
}

void Graph::DepDFS(vector <Node> & node_list) { //here we'll work with making tiny forests :)
    for(int i=(int)node_list.size()-1;i>-1;i--){
        if(!node_list.at(i).was_visited()){
            vector<Node> curr_node_vect;
            DFSforSCC(&node_list.at(i),curr_node_vect);
            SCC_lists.push_back(curr_node_vect);
        }
    }
}

void Graph::DFSforSCC(Node *node, vector<Node>& v_list) {
    if(!node->was_visited()){
        node->visiting();
        v_list.push_back(dep_nodes_copy.at(node->get_id()));    //pre order for org reasons
        Node *c_node;
        for(auto it=node->node_ptr_set.begin();it!=node->node_ptr_set.end();++it){
            c_node = (*it);
            DFSforSCC(c_node, v_list);
        }
        c_node = nullptr;
        delete c_node;
    }
}

vector<Node> Graph::get_SCC(int i){
    return SCC_lists.at(i);
}

int Graph::get_SCC_size(){
    return SCC_lists.size();
}

bool Graph::SelfDepencencyAt(int i){
    return  dependency_nodes.at(i).selfDependent();
}