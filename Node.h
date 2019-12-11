//
// Created by OmarB on 12/10/2019.
//

#ifndef PROJECT_05_NODE_H
#define PROJECT_05_NODE_H
#include <fstream>
#include <iostream>//for output ---- delete later
#include <set>
#include "Rule.h"

class Node {
public:
    Node();
    Node(int, Rule*);
    ~Node();
    string toString_rule();
    string toString_thisRule();
    string get_m_rel_name();
    int get_id();
    void checkNode(Node*);
    void addEdge(Node*);
    set <Node*> node_ptr_set;
    void visiting();
    bool was_visited();
private:
    int id;
    bool visited= false;
    Rule *this_rule;
};


#endif //PROJECT_05_NODE_H
