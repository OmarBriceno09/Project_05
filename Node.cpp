//
// Created by OmarB on 12/10/2019.
//

#include "Node.h"
Node::Node() {

}

Node::Node(int nm, Rule* rule) {
    id = nm;
    this_rule = rule;
}

Node::~Node() {// safely gets rid of node pointers when destructed...
    Node* n_ptr;
    for(auto it=node_ptr_set.begin();it!=node_ptr_set.end();++it){
        n_ptr = (*it);
        n_ptr = nullptr;
        delete n_ptr;

    }
    node_ptr_set.clear();
    this_rule = nullptr;
    delete this_rule;
}

string Node::toString_rule() {
    string the_output="";
    the_output = "R"+to_string(id)+":";
    Node c_node;
    for(auto it=node_ptr_set.begin();it!=node_ptr_set.end();++it){
        c_node = (**it);
        the_output+="R"+to_string(c_node.get_id())/*+"["+to_string(c_node.was_visited())+"]"*/;
        if (next(it)!=node_ptr_set.end())
            the_output+=",";
    }
    //this_rule->main_relation_name to get main rel name...
    //this_rule->relations_names.at(i) to get all dependent names in rule...
    return the_output;
}

string Node::toString_thisRule() {
    return this_rule->out_rule();
}

string Node::get_m_rel_name() {
    return this_rule->main_relation_name;
}

int Node::get_id() {
    return id;
}

void Node::checkNode(Node *c_node) {
    for(int i=0;i<(int)this_rule->relations_names.size();i++){
        if(this_rule->relations_names.at(i) == c_node->get_m_rel_name()){
            addEdge(c_node);
        }
    }
}

void Node::addEdge(Node *a_node) {
    node_ptr_set.insert(a_node);
}

void Node::visiting() {
    visited=true;
}

bool Node::was_visited() {
    return visited;
}