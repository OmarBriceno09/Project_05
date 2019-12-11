//
// Created by OmarB on 11/16/2019.
//

#ifndef PROJECT_05_TUPLE_H
#define PROJECT_05_TUPLE_H
#include <fstream>
#include <iostream>//for output ---- delete later
#include <vector>

using namespace std;

class Tuple:public std::vector<string> {
public:
    //Tuple();
    //~Tuple();
    void set_var_name(string);
    string get_var_name();
    string toStringTuple();
    void remove_value(int);


private:
    string var_name;
};

#endif //PROJECT_05_TUPLE_H
