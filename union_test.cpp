//
// Created by OmarB on 11/16/2019.
//
#include <iostream>
#include <vector>
#include "Relation.h"
#include "Tuple.h"
#include <bits/stdc++.h>

using namespace std;

void add_values_to_tuple(Tuple&,int*,int);

void alpha_test();
void beta_test();
void gamma_test();
void delta_test();
void epsilon_test();

int main(int argc, char **argv) {
    cout<<"--------------PROJECT 04 - UNION TESTER---------------------------"<<endl;
    alpha_test();
    beta_test();
    gamma_test();
    delta_test();
    epsilon_test();
}

void alpha_test(){
    cout<<"Example 1: Union of two sets with equal attributes, one with tuples and one without tuples."<<endl;
    Relation rel_E("E");
    rel_E.setAttribute("'a'");
    rel_E.setAttribute("'b'");
    cout<<"relation: "<<rel_E.getName()<<endl;
    cout<<"attributes: "<<rel_E.toStringAttributeList()<<endl;
    cout<<rel_E.toStringTuples()<<endl;

    Relation rel_B("B");    // relation B
    rel_B.setAttribute("'b'");
    rel_B.setAttribute("'a'");
    int r1[4][2] = {{3,4},{6,4},{4,3},{1,5}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],2);
    rel_B.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],2);
    rel_B.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],2);
    rel_B.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r1[3],2);
    rel_B.setTuple(tpl4);

    cout<<"relation: "<<rel_B.getName()<<endl;
    cout<<"attributes: "<<rel_B.toStringAttributeList()<<endl;
    cout<<rel_B.toStringTuples()<<endl;

    cout<<"Union relation B into relation E <rel_E.union(rel_B)>"<<endl;
    rel_E.rel_union(rel_B);
    cout<<"Unionized!"<<endl;
    cout<<"relation: "<<rel_E.getName()<<endl;
    cout<<"attributes: "<<rel_E.toStringAttributeList()<<endl;
    cout<<rel_E.toStringTuples()<<endl;
}

void beta_test(){
    cout<<"Example 2: Union of two sets with equal attributes, both already with tuples."<<endl;
    Relation rel_J("J");
    rel_J.setAttribute("'c'");
    rel_J.setAttribute("'a'");
    rel_J.setAttribute("'b'");
    int r_a[2][3] = {{2,1,3},{5,5,5}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],3);
    rel_J.setTuple(tpl_a);
    Tuple tpl_b;
    add_values_to_tuple(tpl_b,r_a[1],3);
    rel_J.setTuple(tpl_b);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("K");    // relation B
    rel_K.setAttribute("'a'");
    rel_K.setAttribute("'b'");
    rel_K.setAttribute("'c'");
    int r1[4][3] = {{1,1,1},{1,3,2},{3,2,1},{4,4,4}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],3);
    rel_K.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],3);
    rel_K.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],3);
    rel_K.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r1[3],3);
    rel_K.setTuple(tpl4);

    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    cout<<"Union relation B into relation J <rel_J.union(rel_K)>"<<endl;
    rel_J.rel_union(rel_K);
    cout<<"Unionized!"<<endl;
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
}

void gamma_test(){
    cout<<"Example 3: Union of two sets with equal attributes, both have no tuples(empty)."<<endl;
    Relation rel_E("E");
    rel_E.setAttribute("'a'");
    rel_E.setAttribute("'b'");
    rel_E.setAttribute("'c'");
    cout<<"relation: "<<rel_E.getName()<<endl;
    cout<<"attributes: "<<rel_E.toStringAttributeList()<<endl;
    cout<<rel_E.toStringTuples()<<endl;

    Relation rel_B("B");    // relation B
    rel_B.setAttribute("'b'");
    rel_B.setAttribute("'a'");
    rel_B.setAttribute("'c'");
    cout<<"relation: "<<rel_B.getName()<<endl;
    cout<<"attributes: "<<rel_B.toStringAttributeList()<<endl;
    cout<<rel_B.toStringTuples()<<endl;

    cout<<"Union relation B into relation E <rel_E.union(rel_B)>"<<endl;
    rel_E.rel_union(rel_B);
    cout<<"relation: "<<rel_E.getName()<<endl;
    cout<<"attributes: "<<rel_E.toStringAttributeList()<<endl;
    cout<<rel_E.toStringTuples()<<endl;
}

void delta_test(){
    cout<<"Example 4: Union of two sets with unequal attributes."<<endl;
    Relation rel_J("J");
    rel_J.setAttribute("'c'");
    rel_J.setAttribute("'a'");
    rel_J.setAttribute("'b'");
    int r_a[2][3] = {{2,1,3},{5,5,5}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],3);
    rel_J.setTuple(tpl_a);
    Tuple tpl_b;
    add_values_to_tuple(tpl_b,r_a[1],3);
    rel_J.setTuple(tpl_b);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("K");    // relation B
    rel_K.setAttribute("'d'");
    rel_K.setAttribute("'b'");
    rel_K.setAttribute("'c'");
    int r1[4][3] = {{1,1,1},{1,3,2},{3,2,1},{4,4,4}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],3);
    rel_K.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],3);
    rel_K.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],3);
    rel_K.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r1[3],3);
    rel_K.setTuple(tpl4);

    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    cout<<"Union relation B into relation J <rel_J.union(rel_K)>"<<endl;
    rel_J.rel_union(rel_K);
    cout<<"It relation J should not change since attributed are =/=."<<endl;
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
}

void epsilon_test(){
    cout<<"Example 5: Union of two sets with unequal attributes of different dimensions."<<endl;
    Relation rel_J("J");
    rel_J.setAttribute("'c'");
    rel_J.setAttribute("'a'");
    int r_a[2][3] = {{2,1},{5,5}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],2);
    rel_J.setTuple(tpl_a);
    Tuple tpl_b;
    add_values_to_tuple(tpl_b,r_a[1],2);
    rel_J.setTuple(tpl_b);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("K");    // relation B
    rel_K.setAttribute("'d'");
    rel_K.setAttribute("'b'");
    rel_K.setAttribute("'c'");
    int r1[4][3] = {{1,1,1},{1,3,2},{3,2,1},{4,4,4}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],3);
    rel_K.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],3);
    rel_K.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],3);
    rel_K.setTuple(tpl3);
    Tuple tpl4;
    add_values_to_tuple(tpl4,r1[3],3);
    rel_K.setTuple(tpl4);

    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    cout<<"Union relation B into relation J <rel_J.union(rel_K)>"<<endl;
    rel_J.rel_union(rel_K);
    cout<<"It relation J should not change since attributed are =/=."<<endl;
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
}

void add_values_to_tuple(Tuple& tpl,int* array, int len){
    for(int i=0;i<len;i++){
        tpl.add_value(to_string(array[i]));
    }
}
