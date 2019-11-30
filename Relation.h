//
// Created by OmarB on 11/16/2019.
//

#ifndef PROJECT_04_RELATION_H
#define PROJECT_04_RELATION_H
#include <fstream>
#include <iostream>//for output ---- delete later
#include <vector>
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
    int getNumberOfNewTuples();
    string toStringAttributeList();
    void setAttribute(string);   //sets Attribute ^
    string getAttribute(int);   //gets Attribute from attributes ^
    void setAttribute_as_vector(vector<string>);
    vector<string> getAttributes_vector();
    int setTuple(Tuple);    //adds Tuple ^s
    void removeTuple(int);
    Tuple getTuple(int);    //gets Tuple from tuples_list
    void clearTuples();

    void rename(vector<string>,vector<string>);
    void select(vector<string>,vector<string>);
    void project(vector<string>,vector<string>);
    void project_for_lab(vector<string>,vector<string>);

    int rel_union(Relation);
    void re_sortAttributes(vector<string>);

    bool rel_join(Relation);

    void check_for_duplicates_in_query(vector<string>,vector<string>);

    int return_var_name_index(string);

private:
    string name = "";
    vector <string> attributes;
    vector <Tuple> tuples_list;
    vector <Tuple> var_instance_list; //will store list of tuples, in each 'tuple' it will state the index, or indexes of that var
    vector <int> union_n_inserted_tuples_indexes;
    //from query
    bool does_match_tuples(Tuple);
    int returnRowToInsert(Tuple);//cur row, curr col, tuple in contention
    bool attributesMatch(vector<string>);
    bool all_attributesDiffer(vector<string>);
    bool foundIndex(vector<int>&,int);
    Tuple create_row_tuple(Tuple,Tuple,vector<int>);
    bool formNewAttributes(vector<string>&,vector<string>&,vector<int>&,vector<int>&,vector<string>,vector<string>);
};

#endif //PROJECT_04_RELATION_H
