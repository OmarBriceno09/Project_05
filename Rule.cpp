//
// Created by OmarB on 11/2/2019.
//

#include "Rule.h"

int Rule::rule_count{0};

Rule::Rule(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum) {
    the_rule(tk_num,token_type,token_input,token_linenum);
    set_rule_count(rule_count+1);
}

Rule::~Rule() {
}

void Rule::the_rule(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum) {
    if(token_type[tk_num]==rl_first) { //if its ID
        this_rule_flow += "\n  ";
        headPredicate(tk_num,token_type,token_input,token_linenum);
        if(token_type[tk_num] == "COLON_DASH") {
            this_rule_flow +=" "+token_input[tk_num]+" ";
            tk_num++;
            Predicate predicate(tk_num,token_type,token_input,token_linenum);
            the_predicateList.push_back(predicate.return_the_predicate());
            this_rule_flow += predicate.return_the_predicate();
            predicateList(tk_num,token_type,token_input,token_linenum);
            if(token_type[tk_num] == "PERIOD") {
                this_rule_flow += token_input[tk_num];
                tk_num++;//rule will end
            }else{throw tk_num;}
        }else{throw tk_num;}
    }else{throw tk_num;}
}

//ID LEFT_PAREN ID idList RIGHT_PAREN
void Rule::headPredicate(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                         vector<int> &token_linenum){
    if(token_type[tk_num]==hPd_first) {//if id is first
        if (token_type[tk_num] == "ID") {//first 1
            the_headPredicate += token_input[tk_num];
            tk_num++;
            if (token_type[tk_num] == "LEFT_PAREN") {
                the_headPredicate += token_input[tk_num];
                tk_num++;
                if (token_type[tk_num] == "ID") {//first 1
                    the_headPredicate += token_input[tk_num];
                    tk_num++;
                    idList(tk_num,token_type,token_input,token_linenum, the_headPredicate);
                    if (token_type[tk_num] == "RIGHT_PAREN") {//first 1
                        the_headPredicate += token_input[tk_num];
                        this_rule_flow+=the_headPredicate; //appends headpredicate to ruleflow
                        tk_num++;//back recurr!!
                    } else {throw tk_num;}
                } else {throw tk_num;}
            } else {throw tk_num;}
        } else {throw tk_num;}
    }else{throw tk_num;}
}

//COMMA predicate predicateList | lambda
void Rule::predicateList(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                         vector<int> &token_linenum){
    if(does_token_match(token_type[tk_num],pdL_first,2)){
        if(token_type[tk_num] == "COMMA"){//first 1
            this_rule_flow+=token_input[tk_num];
            tk_num++;
            Predicate predicate(tk_num,token_type,token_input,token_linenum);
            the_predicateList.push_back(predicate.return_the_predicate());
            this_rule_flow += predicate.return_the_predicate();
            predicateList(tk_num,token_type,token_input,token_linenum);
        }else {//this is for when it's lambda
            //tk_num++;
        }
    }else if(!does_token_match(token_type[tk_num],pdL_follow,12)){
        throw tk_num;//if not in follow list throw error
    }
}

void Rule::idList(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                  vector<int> &token_linenum, string& curr_out_flow){
    if(does_token_match(token_type[tk_num],idL_first,2)){ //if its any first of idList
        if(token_type[tk_num] == "COMMA"){//first 1
            curr_out_flow+=token_input[tk_num];
            tk_num++;
            if(token_type[tk_num] == "ID") {//STRING
                curr_out_flow+=token_input[tk_num];
                tk_num++;
                idList(tk_num,token_type,token_input,token_linenum, curr_out_flow);
            }else{throw tk_num;}
        }else {//this is for when it's lambda
            //tk_num++;
        }
    }else if(!does_token_match(token_type[tk_num],idL_follow,15)){
        throw tk_num;//if not in follow list throw error
    }
}

bool Rule::does_token_match(string token, const string the_list[], int list_size){
    for(int i=0; i<list_size; i++){
        if(token.compare(the_list[i])==0)
            return true;
    }
    return false;
}

void Rule::set_rule_count(int count) {
    rule_count = count;
}

int Rule::get_rule_count() {
    return rule_count;
}

string Rule::out_rule() {
    return this_rule_flow;
}