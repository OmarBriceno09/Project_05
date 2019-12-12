//
// Created by OmarB on 11/16/2019.
//

#ifndef PROJECT_05_RELATION_H
#define PROJECT_05_RELATION_H
#include <fstream>
#include <iostream>//for output ---- delete later
#include <vector>
#include <set>
#include <algorithm>
#include "Tuple.h"

using namespace std;

class Relation {
public:
    Relation(string);
    ~Relation();
    //Relation(Relation&);
    string getName();

    int getCols();    //returns # of Cols
    int getRows();    //returns # of Rows
    void setName(string);
    string toStringTuples();
    string toStringNewTuples();
    //int getNumberOfNewTuples();
    string toStringAttributeList();
    void setAttribute(string);   //sets Attribute ^
    string getAttribute(int);   //gets Attribute from attributes ^
    void setAttribute_as_vector(vector<string>&);
    vector<string>& getAttributes_vector();
    bool setTuple(Tuple&);    //adds Tuple ^s
    //void removeTuple(int);
    //Tuple getTuple(int);    //gets Tuple from tuples_list
    void clearTuples();

    void rename(vector<string>&,vector<string>&);
    void select(vector<string>&,vector<string>&);
    void project(vector<string>&,vector<string>&);
    void project_for_lab(vector<string>&,vector<string>&);

    int rel_union(Relation&);

    void rel_join(Relation&);

    void check_for_duplicates_in_query(vector<string>&,vector<string>&);

    int return_var_name_index(string&);

private:
    string name = "";
    vector <string> attributes;
    //vector <Tuple> tuples_list;
    set <Tuple> tpl_list;
    vector <Tuple> var_instance_list; //will store list of tuples, in each 'tuple' it will state the index, or indexes of that var
    //JUST USE SETS
    //vector <int> union_n_inserted_tuples_indexes;
    set <Tuple> new_inserted_tuples;//JUST USE SETS
    //from query
    //bool does_match_tuples(Tuple);
    bool attributesMatch(vector<string>&);
    //bool all_attributesDiffer(vector<string>&);
    bool foundIndex(vector<int>&,int);
    bool foundTuple(Tuple&);
    void create_row_tuple(Tuple&,Tuple&,Tuple&,vector<int>&);
    void formNewAttributes(vector<Tuple>&,vector<string>&,vector<int>&,vector<string>&,vector<string>&);
};

#endif //PROJECT_05_RELATION_H
