//
// Created by OmarB on 11/2/2019.
//

#include "Tuple.h"
/*Tuple::Tuple() {
}

Tuple::~Tuple() {
}*/

string Tuple::toStringTuple() {
    string tuple_string = "";
    for (unsigned int i=0; i<this->size();i++)
        tuple_string+=" "+this->at(i);
    return  tuple_string;
}

void Tuple::set_var_name(string name) { //this is to check for duplicates with tuples
    var_name = name;
}

string Tuple::get_var_name() {
    return var_name;
}

void Tuple::remove_value(int i) {
    this->erase(this->begin()+i);
}