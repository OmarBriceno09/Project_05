//
// Created by OmarB on 11/2/2019.
//
#include "Parameter.h"
//STRING | ID | expression
Parameter::Parameter(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                     vector<int> &token_linenum){
    the_parameter(tk_num,token_type,token_input,token_linenum);

}

Parameter::~Parameter() {
}

void Parameter::the_parameter(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                              vector<int> &token_linenum){
    if(does_token_match(token_type[tk_num],prmt_first,3)){
        if(token_type[tk_num] == "STRING") {//first #1
            the_string = token_input[tk_num];
            parameter_string+=the_string;
            tk_num++;//end #1
        }else if (token_type[tk_num] == "ID"){//first #2
            the_id = token_input[tk_num];
            parameter_string+=the_id;
            tk_num++;//end #2
        }else if(token_type[tk_num] == "LEFT_PAREN"){
            expression(tk_num,token_type,token_input,token_linenum);
        }//no lambda this time ;(
    }else if(!does_token_match(token_type[tk_num],prmt_follow,12)){
        throw tk_num;//if not in follow list throw error
    }
}

//LEFT_PAREN parameter the_operator parameter RIGHT_PAREN
void Parameter::expression(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                           vector<int> &token_linenum){
    if(token_type[tk_num]==exp_first){
        parameter_string += token_input[tk_num];
        tk_num++;
        the_parameter(tk_num,token_type,token_input,token_linenum);
        the_operator(tk_num,token_type,token_input,token_linenum);
        the_parameter(tk_num,token_type,token_input,token_linenum);
        if(token_type[tk_num]=="RIGHT_PAREN"){
            parameter_string += token_input[tk_num];
            tk_num++;//recurr back
        }else{throw tk_num;}
    }else{throw tk_num;}
}

//ADD | MULTIPLY
void Parameter::the_operator(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                             vector<int> &token_linenum){
    if(does_token_match(token_type[tk_num],opt_first,3)){
        if(token_type[tk_num]=="ADD"){
            the_expression = token_input[tk_num];
            tk_num++;//end #1 recurr back
        }if(token_type[tk_num]=="MULTIPLY"){
            the_expression = token_input[tk_num];
            tk_num++;//end #2 recurr back
        }
        parameter_string+=the_expression;
    }else{throw tk_num;}
}

bool Parameter::does_token_match(string token, const string the_list[], int list_size){
    for(int i=0; i<list_size; i++){
        if(token.compare(the_list[i])==0)
            return true;
    }
    return false;
}

string Parameter::return_the_parameter(){
    return parameter_string;
}