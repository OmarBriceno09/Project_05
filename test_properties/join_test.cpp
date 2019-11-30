//
// Created by OmarB on 11/18/2019.
//
#include <iostream>
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
void idkwhatcomesnext();

int main(int argc, char **argv) {
    cout<<"--------------PROJECT 04 - JOIN TESTER---------------------------"<<endl;
    //alpha_test();
    //beta_test();
    //gamma_test();
    //delta_test();
    //epsilon_test();
    idkwhatcomesnext();
}

void alpha_test(){
    cout<<"two empty sets with similar attributes"<<endl;
    Relation rel_E("E");
    rel_E.setAttribute("'a'");
    rel_E.setAttribute("'x'");
    rel_E.setAttribute("'y'");
    rel_E.setAttribute("'z'");
    rel_E.setAttribute("'e'");
    cout<<"relation: "<<rel_E.getName()<<endl;
    cout<<"attributes: "<<rel_E.toStringAttributeList()<<endl;
    cout<<rel_E.toStringTuples()<<endl;

    Relation rel_B("B");    // relation B
    rel_B.setAttribute("'b'");
    rel_B.setAttribute("'x'");
    rel_B.setAttribute("'q'");
    rel_B.setAttribute("'z'");
    rel_B.setAttribute("'g'");

    cout<<"relation: "<<rel_B.getName()<<endl;
    cout<<"attributes: "<<rel_B.toStringAttributeList()<<endl;
    cout<<rel_B.toStringTuples()<<endl;

    rel_E.rel_join(rel_B);
    cout<<"relation: "<<rel_E.getName()<<endl;
    cout<<"attributes: "<<rel_E.toStringAttributeList()<<endl;
    cout<<rel_E.toStringTuples()<<endl;
    cout<<endl;
}

void beta_test(){
    cout<<"Example 2: Join of two large relations."<<endl;
    Relation rel_J("J");
    rel_J.setAttribute("'a'");
    rel_J.setAttribute("'b'");
    rel_J.setAttribute("'c'");
    int r_a[6][3] = {{1,1,2},{1,2,1},{2,2,1},{3,2,1},{4,2,1},{5,3,3}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],3);
    rel_J.setTuple(tpl_a);
    Tuple tpl_b;
    add_values_to_tuple(tpl_b,r_a[1],3);
    rel_J.setTuple(tpl_b);
    Tuple tpl_c;
    add_values_to_tuple(tpl_c,r_a[2],3);
    rel_J.setTuple(tpl_c);
    Tuple tpl_d;
    add_values_to_tuple(tpl_d,r_a[3],3);
    rel_J.setTuple(tpl_d);
    Tuple tpl_e;
    add_values_to_tuple(tpl_e,r_a[4],3);
    rel_J.setTuple(tpl_e);
    Tuple tpl_f;
    add_values_to_tuple(tpl_f,r_a[5],3);
    rel_J.setTuple(tpl_f);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("K");    // relation B
    rel_K.setAttribute("'c'");//c
    rel_K.setAttribute("'d'");//d
    rel_K.setAttribute("'b'");//b
    int r1[6][3] = {{1,1,1},{2,2,1},{2,3,1},{1,4,2},{1,5,2},{1,6,2}};
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
    Tuple tpl5;
    add_values_to_tuple(tpl5,r1[4],3);
    rel_K.setTuple(tpl5);
    Tuple tpl6;
    add_values_to_tuple(tpl6,r1[5],3);
    rel_K.setTuple(tpl6);

    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    rel_J.rel_join(rel_K);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
    cout<<endl;
}

void gamma_test(){
    cout<<"Example 3: Join of two medium sized relations."<<endl;
    Relation rel_J("J");
    rel_J.setAttribute("'S'");
    rel_J.setAttribute("'N'");
    rel_J.setAttribute("'A'");
    rel_J.setAttribute("'P'");
    int r_a[3][4] = {{1,10,20,51},{2,15,25,59},{3,19,20,51}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],4);
    rel_J.setTuple(tpl_a);
    Tuple tpl_b;
    add_values_to_tuple(tpl_b,r_a[1],4);
    rel_J.setTuple(tpl_b);
    Tuple tpl_c;
    add_values_to_tuple(tpl_c,r_a[2],4);
    rel_J.setTuple(tpl_c);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("K");    // relation B
    rel_K.setAttribute("'C'");//c
    rel_K.setAttribute("'S'");//d
    rel_K.setAttribute("'G'");//b
    int r1[5][3] = {{1,1,100},{1,2,80},{1,3,70},{2,1,85},{2,2,80}};
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
    Tuple tpl5;
    add_values_to_tuple(tpl5,r1[4],3);
    rel_K.setTuple(tpl5);

    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    rel_J.rel_join(rel_K);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
    cout<<endl;
}

void delta_test(){
    cout<<"Example 4: Join of two medium sized relations that have three matching attributes."<<endl;
    Relation rel_J("J");
    rel_J.setAttribute("'A'");
    rel_J.setAttribute("'X'");
    rel_J.setAttribute("'Y'");
    rel_J.setAttribute("'Z'");
    int r_a[4][4] = {{1,1,2,3},{1,2,1,1,},{2,3,1,3},{3,1,2,3}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],4);
    rel_J.setTuple(tpl_a);
    Tuple tpl_b;
    add_values_to_tuple(tpl_b,r_a[1],4);
    rel_J.setTuple(tpl_b);
    Tuple tpl_c;
    add_values_to_tuple(tpl_c,r_a[2],4);
    rel_J.setTuple(tpl_c);
    Tuple tpl_d;
    add_values_to_tuple(tpl_d,r_a[3],4);
    rel_J.setTuple(tpl_d);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("K");    // relation B
    rel_K.setAttribute("'X'");//c
    rel_K.setAttribute("'Y'");//d
    rel_K.setAttribute("'Z'");//b
    rel_K.setAttribute("'E'");//b
    int r1[3][4] = {{1,2,3,5},{2,4,6,6},{3,1,3,7}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],4);
    rel_K.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],4);
    rel_K.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],4);
    rel_K.setTuple(tpl3);
    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    rel_J.rel_join(rel_K);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
    cout<<endl;
}

void epsilon_test(){
    cout<<"Example 5: Join of two medium sized relations have NO attributes in common."<<endl;
    cout<<"NOTE: They should join!!!"<<endl;
    Relation rel_J("J");
    rel_J.setAttribute("'A'");
    rel_J.setAttribute("'B'");
    rel_J.setAttribute("'C'");
    int r_a[2][3] = {{2,2,2},{3,2,1}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],3);
    rel_J.setTuple(tpl_a);
    Tuple tpl_b;
    add_values_to_tuple(tpl_b,r_a[1],3);
    rel_J.setTuple(tpl_b);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("K");    // relation Bcle
    rel_K.setAttribute("'X'");//c
    rel_K.setAttribute("'Y'");//d
    int r1[3][2] = {{1,2},{4,5},{7,8}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],2);
    rel_K.setTuple(tpl1);
    Tuple tpl2;
    add_values_to_tuple(tpl2,r1[1],2);
    rel_K.setTuple(tpl2);
    Tuple tpl3;
    add_values_to_tuple(tpl3,r1[2],2);
    rel_K.setTuple(tpl3);
    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    rel_J.rel_join(rel_K);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
    cout<<endl;
}

void idkwhatcomesnext(){
    cout<<"THE FINAL EXAMPLE"<<endl;
    Relation rel_J("a");
    rel_J.setAttribute("x");
    rel_J.setAttribute("y");
    int r_a[1][2] = {{1,1}};
    Tuple tpl_a;
    add_values_to_tuple(tpl_a,r_a[0],2);
    rel_J.setTuple(tpl_a);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;

    Relation rel_K("b");    // relation B
    rel_K.setAttribute("x");//c
    rel_K.setAttribute("y");//d
    int r1[1][2] = {{1,2}};
    Tuple tpl1;
    add_values_to_tuple(tpl1,r1[0],2);
    rel_K.setTuple(tpl1);

    cout<<"relation: "<<rel_K.getName()<<endl;
    cout<<"attributes: "<<rel_K.toStringAttributeList()<<endl;
    cout<<rel_K.toStringTuples()<<endl;

    rel_J.rel_join(rel_K);
    cout<<"relation: "<<rel_J.getName()<<endl;
    cout<<"attributes: "<<rel_J.toStringAttributeList()<<endl;
    cout<<rel_J.toStringTuples()<<endl;
    cout<<endl;
}

void add_values_to_tuple(Tuple& tpl,int* array, int len){
    for(int i=0;i<len;i++){
        tpl.add_value(to_string(array[i]));
    }
}
