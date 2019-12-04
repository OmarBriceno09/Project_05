//
// Created by OmarB on 11/7/2019.
//
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include "Relation.h"
#include "Tuple.h"
#include <bits/stdc++.h>

using namespace std;

void add_values_to_tuple(Tuple&,int*,int);

void gamma();
void beta();
void alpha();

int main(int argc, char **argv) {
    cout<<"--------------UNIT TEST 1 - PROJECT OPERATOR---------------------------"<<endl;
    gamma();
    beta();
    alpha();
}

void gamma(){
    Relation example1("Gamma");
    example1.setAttribute("'cat'");
    example1.setAttribute("'fish'");
    example1.setAttribute("'bird'");
    example1.setAttribute("'bunny'");
    int r1[6][4] = {{3,4,2,4},{6,4,9,2},{4,3,2,7},{1,5,2,4},{1,5,8,3},{3,4,2,4}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],4);
    example1.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],4);
    example1.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],4);
    example1.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r1[3],4);
    example1.setTuple(tpl4);
    Tuple tpl5;
    add_values_to_tuple(tpl5,r1[4],4);
    example1.setTuple(tpl5);
    Tuple tpl6;
    add_values_to_tuple(tpl6,r1[5],4);
    example1.setTuple(tpl6);
    cout<<example1.getName()<<": "<<endl;
    cout<<example1.toStringTuples()<<endl;

    cout<<"query is <a,b,a,a>"<<endl;
    vector<string> project_vector1 = {"a","b","a","a"};
    cout<<"Example a, project c from "<<example1.getName()<<": "<<endl;
    vector<string> tk_vector1 = {"STRING","STRING","STRING","ID"};
    Relation relation_copy1 = example1;
    relation_copy1.project(tk_vector1,project_vector1);
    cout<<relation_copy1.toStringAttributeList()<<endl;
    cout<<relation_copy1.toStringTuples()<<endl;

    cout<<"Example b, project all "<<example1.getName()<<": "<<endl;
    cout<<"..bird,bird,... should return the left most matching attribute pos..."<<endl;
    vector<string> tk_vector2 = {"ID","ID","ID","ID"};
    Relation relation_copy2 = example1;
    relation_copy2.project(tk_vector2,project_vector1);
    cout<<relation_copy2.toStringAttributeList()<<endl;
    cout<<relation_copy2.toStringTuples()<<endl;
}

void beta(){
    Relation example1("Beta");
    example1.setAttribute("'cat'");
    example1.setAttribute("'fish'");
    example1.setAttribute("'bird'");
    example1.setAttribute("'bunny'");
    int r1[5][4] = {{3,4,2,4},{6,4,9,2},{4,3,2,7},{1,5,2,4},{1,5,8,3}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],4);
    example1.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],4);
    example1.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],4);
    example1.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r1[3],4);
    example1.setTuple(tpl4);
    Tuple tpl5;
    add_values_to_tuple(tpl5,r1[4],4);
    example1.setTuple(tpl5);
    cout<<example1.getName()<<": "<<endl;
    cout<<example1.toStringTuples()<<endl;

    cout<<"Example 1, project 'bunny' from "<<example1.getName()<<": "<<endl;
    vector<string> project_vector1 = {"'cat'","'fish'","'bird'","'bunny'"};
    vector<string> tk_vector1 = {"STRING","STRING","STRING","ID"};
    Relation relation_copy1 = example1;
    relation_copy1.project(tk_vector1,project_vector1);
    cout<<relation_copy1.toStringTuples()<<endl;

    cout<<"Example 2, project 'cat', 'bird', and 'bunny' from "<<example1.getName()<<": "<<endl;
    vector<string> tk_vector2 = {"ID","STRING","ID","ID"};
    Relation relation_copy2 = example1;
    relation_copy2.project(tk_vector2,project_vector1);
    cout<<relation_copy2.toStringTuples()<<endl;
}

void alpha(){
    Relation example2("Alpha");
    example2.setAttribute("'cat'");
    example2.setAttribute("'dog'");
    example2.setAttribute("'fish'");
    int r2[4][3] = {{1,2,5},{1,4,1},{2,3,2},{6,7,4}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r2[0],3);
    example2.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r2[1],3);
    example2.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r2[2],3);
    example2.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r2[3],3);
    example2.setTuple(tpl4);
    cout<<example2.getName()<<": "<<endl;
    cout<<example2.toStringTuples()<<endl;

    cout<<"Example 3, project 'fish' and 'dog' from "<<example2.getName()<<": "<<endl;
    vector<string> project_vector1 = {"'cat'","'fish'","'dog'"};
    vector<string> tk_vector1 = {"STRING","ID","ID"};
    Relation relation_copy1 = example2;
    relation_copy1.project(tk_vector1,project_vector1);
    cout<<relation_copy1.toStringTuples()<<endl;
}

void add_values_to_tuple(Tuple& tpl,int* array, int len){
    for(int i=0;i<len;i++){
        tpl.add_value(to_string(array[i]));
    }
}
