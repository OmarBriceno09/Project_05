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

void beta();

int main(int argc, char **argv) {
    cout<<"--------------UNIT TEST 3 - SELECT OPERATOR---------------------------"<<endl;
    beta();
}

void beta(){
    Relation example1("Beta");
    example1.setAttribute("A");
    example1.setAttribute("B");
    example1.setAttribute("C");
    example1.setAttribute("D");
    int r1[4][4] = {{0,1,2,1},{1,2,1,2},{4,3,4,3},{1,5,6,7}};
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
    cout<<example1.getName()<<": "<<endl;
    cout<<example1.toStringTuples()<<endl;

    cout<<"Example 1, select all rows where A = 1 from "<<example1.getName()<<": "<<endl;
    vector<string> select_vector1 = {"1","B","C","D"};
    vector<string> tk_vector1 = {"STRING","ID","ID","ID"};
    Relation relation_copy1 = example1;
    relation_copy1.select(tk_vector1,select_vector1);
    cout<<relation_copy1.toStringTuples()<<endl;

    cout<<"Example 2, select all rows where A = C and B = D from "<<example1.getName()<<": "<<endl;
    vector<string> select_vector2 = {"X","Y","X","Y"};
    vector<string> tk_vector2 = {"ID","ID","ID","ID"};
    Relation relation_copy2 = example1;
    relation_copy2.select(tk_vector2,select_vector2);
    cout<<relation_copy2.toStringTuples()<<endl;
}

void add_values_to_tuple(Tuple& tpl,int* array, int len){
    for(int i=0;i<len;i++){
        tpl.add_value(to_string(array[i]));
    }
}