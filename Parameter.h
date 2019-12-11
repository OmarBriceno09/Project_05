//
// Created by OmarB on 11/16/2019.
//

#ifndef PROJECT_05_PARAMETER_H
#define PROJECT_05_PARAMETER_H
#include <fstream>
#include <vector>
using namespace std;

//STRING | ID | expression
class Parameter {
public:
    Parameter(int &tk_num, vector<string> &, vector<string> &, vector<int> &);
    ~Parameter();

    string return_the_parameter();

    string the_id = "";
    string the_string = "";
    string the_expression="";

private:
    string parameter_string="";

    const string prmt_first[3] = {"STRING","ID","LEFT_PAREN"};
    const string exp_first = "LEFT_PAREN";
    const string opt_first[2] = {"ADD","MULTIPLY"};

    const string prmt_follow[12] = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON",
                                    "MULTIPLY","ADD","QUERIES","ID","STRING","EOF"};

    void the_parameter(int&, vector<string>&, vector<string>&, vector<int>&);
    void expression(int&, vector<string>&, vector<string>&, vector<int>&);
    void the_operator(int&, vector<string>&, vector<string>&, vector<int>&);
    bool does_token_match(string, const string[], int);
};

#endif //PROJECT_05_PARAMETER_H
