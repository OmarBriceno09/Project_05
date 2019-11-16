//
// Created by OmarB on 11/2/2019.
//

#include "Tuple.h"
Tuple::Tuple() {
}

Tuple::~Tuple() {
}

void Tuple::add_value(string val) {
    values_list.push_back(val);
}

void Tuple::remove_value(int i) {
    values_list.erase(values_list.begin()+i);
}

string Tuple::get_value(int i) {
    return values_list.at(i);
}

vector<string> Tuple::getValuesList() {
    return values_list;
}

int Tuple::get_size() {
    return values_list.size();
}

string Tuple::toStringTuple() {
    string tuple_string = "";
    for (int i = 0; i<get_size();i++)
        tuple_string+=" "+get_value(i);
    return  tuple_string;
}

void Tuple::set_var_name(string name) { //this is to check for duplicates with tuples
    var_name = name;
}

string Tuple::get_var_name() {
    return var_name;
}