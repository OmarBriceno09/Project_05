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
void alpha();
void gamma();

int main(int argc, char **argv) {
    cout<<"--------------UNIT TEST 2 - RENAME OPERATOR---------------------------"<<endl;
    beta();
    alpha();
    gamma();
}

void beta(){
    Relation example1("Beta");
    example1.setAttribute("A");
    example1.setAttribute("B");
    example1.setAttribute("C");
    int r1[2][3] = {{0,1,2},{3,4,5}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],3);
    example1.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],3);
    example1.setTuple(tpl2);

    cout<<example1.getName()<<": "<<endl;
    cout<<example1.toStringTuples()<<endl;

    cout<<"Example 1, renaming attribute A to 'aardvark' and attribute C to 'chicken' on "<<example1.getName()<<": "<<endl;
    vector<string> rename_vector1 = {"'aardvark'","'b'","'chicken'"};
    vector<string> tk_vector1 = {"ID","STRING","ID"};
    Relation relation_copy1 = example1;
    relation_copy1.rename(tk_vector1,rename_vector1);
    cout<<relation_copy1.toStringTuples()<<endl;
}

void alpha(){
    Relation example2("Alpha");
    example2.setAttribute("W");
    example2.setAttribute("X");
    example2.setAttribute("Y");
    example2.setAttribute("Z");

    int r2[4][4] = {{0,1,1,9},{2,1,8,2},{5,7,2,5},{6,5,4,3}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r2[0],4);
    example2.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r2[1],4);
    example2.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r2[2],4);
    example2.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r2[3],4);
    example2.setTuple(tpl4);
    cout<<example2.getName()<<": "<<endl;
    cout<<example2.toStringTuples()<<endl;

    cout<<"Example 2, rename all attributes to H, I, L, O on "<<example2.getName()<<": "<<endl;
    vector<string> rename_vector1 = {"H","I","L","O"};
    vector<string> tk_vector1 = {"ID","ID","ID","ID"};
    Relation relation_copy1 = example2;
    relation_copy1.rename(tk_vector1,rename_vector1);
    cout<<relation_copy1.toStringTuples()<<endl;
}

void gamma(){
    Relation example3("Gamma");
    example3.setAttribute("S");
    example3.setAttribute("N");
    example3.setAttribute("A");
    example3.setAttribute("P");
    example3.setAttribute("C");
    example3.setAttribute("G");
    cout<<example3.getName()<<": "<<endl;
    cout<<example3.toStringAttributeList()<<endl;

    cout<<"Example 2, rename all attributes to S,n,A,P,c,G on "<<example3.getName()<<": "<<endl;
    vector<string> rename_vector1 = {"S","n","A","P","c","G"};
    vector<string> tk_vector1 = {"ID","ID","ID","ID","ID","ID"};
    Relation relation_copy1 = example3;
    relation_copy1.rename(tk_vector1,rename_vector1);
    cout<<relation_copy1.toStringAttributeList()<<endl;
}

void add_values_to_tuple(Tuple& tpl,int* array, int len){
    for(int i=0;i<len;i++){
        tpl.add_value(to_string(array[i]));
    }
}

