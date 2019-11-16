//
// Created by OmarB on 11/2/2019.
//
#include "Predicate.h"
Predicate::Predicate(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                     vector<int> &token_linenum){
    the_predicate(tk_num, token_type,token_input,token_linenum);
}

Predicate::~Predicate() {
}

void Predicate::the_predicate(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                              vector<int> &token_linenum){
    if(token_type[tk_num]==pd_first) {//if id is first
        id = token_input[tk_num];
        predicate_string+= id;
        tk_num++;
        if (token_type[tk_num] == "LEFT_PAREN") {//first 1
            predicate_string += token_input[tk_num];
            tk_num++;

            params_tkn_type.push_back(token_type[tk_num]);   //pushing back parameter type for relations

            //instantiating parameter object
            Parameter parameter(tk_num,token_type,token_input,token_linenum);
            //appending parameter to DatalogProgram string

            the_parameter_list.push_back(parameter.return_the_parameter());

            predicate_string += parameter.return_the_parameter();
            parameterList(tk_num,token_type,token_input,token_linenum);

            if (token_type[tk_num] == "RIGHT_PAREN") {//first 1
                predicate_string += token_input[tk_num];
                tk_num++;//predicate ends, recurr back
            } else {throw tk_num;}
        } else {throw tk_num;}
    }else{throw tk_num;}
}

//COMMA parameter parameterList | lambda
void Predicate::parameterList(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                              vector<int> &token_linenum){
    if(does_token_match(token_type[tk_num],prmtL_first,2)){
        if(token_type[tk_num] == "COMMA"){//first 1
            predicate_string+=token_input[tk_num];
            tk_num++;

            params_tkn_type.push_back(token_type[tk_num]);  //pushing back parameter type for relations

            //instantiating parameter object
            Parameter parameter(tk_num,token_type,token_input,token_linenum);
            //appending parameter to DatalogProgram string
            the_parameter_list.push_back(parameter.return_the_parameter());
            predicate_string += parameter.return_the_parameter();
            parameterList(tk_num,token_type,token_input,token_linenum);
        }else {//this is for when it's lambda
            //tk_num++;
        }
    }else if(!does_token_match(token_type[tk_num],prmtL_follow,12)){
        throw tk_num;//if not in follow list throw error
    }
}

bool Predicate::does_token_match(string token, const string the_list[], int list_size){
    for(int i=0; i<list_size; i++){
        if(token.compare(the_list[i])==0)
            return true;
    }
    return false;
}

string Predicate::return_the_predicate(){
    return predicate_string;
}

string Predicate::toString_paramList() {
    string the_strList = "";
    for (int i =0; i<(int)the_parameter_list.size();i++){
        the_strList+= the_parameter_list.at(i)+" ";
    }
    return the_strList;
}

string Predicate::toString_paramType() {
    string typ_string = "";
    for (int i =0; i<(int)params_tkn_type.size();i++){
        typ_string+= params_tkn_type.at(i)+" ";
    }
    return typ_string;
}