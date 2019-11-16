//
// Created by OmarB on 11/2/2019.
//

#include "DatalogProgram.h"
DatalogProgram::DatalogProgram(vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum) {
    try {
        if (token_type[tk_num] == dP_first) {//tk_num is zero, it has to start at SCHEMES
            out_flow += token_input[tk_num] + "(";//this is were schemes go...
            tk_num++;
            if (token_type[tk_num] == "COLON") {
                scheme_flow += token_input[tk_num];
                tk_num++;
                scheme(tk_num, token_type, token_input, token_linenum);
                schemeList(tk_num, token_type, token_input, token_linenum);
                out_flow += to_string(scheme_count) + ")" + scheme_flow;
                if (token_type[tk_num] == "FACTS") {
                    out_flow += "\n" + token_input[tk_num] + "(";
                    tk_num++;
                    if (token_type[tk_num] == "COLON") {
                        fact_flow += token_input[tk_num]; //begin fact flow
                        tk_num++;
                        factList(tk_num, token_type, token_input, token_linenum);
                        out_flow += to_string(fact_count) + ")" + fact_flow; //append fact flow with nums of facts
                        if (token_type[tk_num] == "RULES") {
                            out_flow += "\n" + token_input[tk_num] + "(";
                            tk_num++;
                            if (token_type[tk_num] == "COLON") {
                                rule_flow += token_input[tk_num]; //begin fact flow
                                tk_num++;
                                ruleList(tk_num, token_type, token_input, token_linenum);
                                out_flow +=
                                        to_string(rule_count) + ")" + rule_flow; //append rule flow with nums of facts
                                if (token_type[tk_num] == "QUERIES") { //QUERIES COLON query queryList
                                    out_flow += "\n" + token_input[tk_num] + "(";
                                    tk_num++;
                                    if (token_type[tk_num] == "COLON") {
                                        query_flow += token_input[tk_num];
                                        tk_num++;
                                        query(tk_num, token_type, token_input, token_linenum);
                                        queryList(tk_num, token_type, token_input, token_linenum);
                                        out_flow += to_string(query_count) + ")" +
                                                    query_flow; //append query flow with nums of facts
                                    } else { throw tk_num; }
                                } else { throw tk_num; }
                            } else { throw tk_num; }
                        } else { throw tk_num; }
                    } else { throw tk_num; }
                } else { throw tk_num; }
            } else { throw tk_num; }
        } else { throw tk_num; }

        the_output = "Success!\n";
        the_output += out_flow;
        sort(domains.begin(), domains.end());
        domains.erase(unique(domains.begin(), domains.end()), domains.end());
        the_output += "\nDomain(" + to_string(domains.size()) + "):";
        for (int i = 0; i < (int) domains.size(); i++) {
            the_output += "\n" + domains[i];
        }
        the_output += "\n";
    }
    catch (int tk_num) {
        the_output = "Failure!\n";
        the_output +=
                "  (" + token_type[tk_num] + ",\"" + token_input[tk_num] + "\"," + to_string(token_linenum[tk_num]) +
                ")";
    }
}

DatalogProgram::~DatalogProgram() {
}

void DatalogProgram::schemeList(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum) {
    if (does_token_match(token_type[tk_num], schL_first, 2)) { //if its any first of idList
        if(token_type[tk_num] == "ID"){//do not count token bc line is not passed
            scheme(tk_num,token_type,token_input,token_linenum);
            schemeList(tk_num,token_type,token_input,token_linenum);
        }else {//this is for when it's lambda
            //tk_num++;
        }
    }else if (!does_token_match(token_type[tk_num],schL_follow,15)){
        throw tk_num;
    }
}

void DatalogProgram::factList(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum){
    if (does_token_match(token_type[tk_num], fctL_first, 2)) { //if its any first of fctList
        if(token_type[tk_num] == "ID"){//do not count token bc line is not passed
            fact(tk_num,token_type,token_input,token_linenum);
            factList(tk_num,token_type,token_input,token_linenum);
        }else {//this is for when it's lambda
            //tk_num++;
        }
    }else if (!does_token_match(token_type[tk_num],fctL_follow,14)){
        throw tk_num;
    }
}

void DatalogProgram::ruleList(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum){
    if (does_token_match(token_type[tk_num], rlL_first, 2)) { //if its any first of fctList
        if(token_type[tk_num] == "ID"){//do not count token bc line is not passed
            //rule(tk_num,token_type,token_input,token_linenum);
            Rule rule(tk_num,token_type,token_input,token_linenum);    //creating instance of rule
            rule_flow+=rule.out_rule();
            rule_count = rule.get_rule_count();
            //Make rule object here by placing in the inputs-------------------------------------------------------------------
            ruleList(tk_num,token_type,token_input,token_linenum);
        }else {//this is for wh2en it's lambda
            //tk_num++;
        }
    }else if (!does_token_match(token_type[tk_num],rlL_follow,11)){
        throw tk_num;
    }
}

//query queryList | lambda
void DatalogProgram::queryList(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum){
    if (does_token_match(token_type[tk_num], qryL_first, 2)) { //if its any first of fctList
        if(token_type[tk_num] == "ID"){//do not count token bc line is not passed
            query(tk_num,token_type,token_input,token_linenum);
            queryList(tk_num,token_type,token_input,token_linenum);
        }else {//this is for wh2en it's lambda
            //tk_num++;
        }
    }else if (token_type[tk_num]!=qryL_follow){
        throw tk_num;
    }
}

void DatalogProgram::scheme(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum){
    if(token_type[tk_num]==sch_first){ //if its ID
        scheme_flow+="\n  "+token_input[tk_num];
        Relation relation(token_input[tk_num]); //RELATION IS CREATED
        //cout<<relation.getName()<<endl; //-----------------------------------------------------------------
        tk_num++;
        if(token_type[tk_num] == "LEFT_PAREN"){
            scheme_flow+=token_input[tk_num];
            tk_num++;
            if(token_type[tk_num] == "ID"){
                scheme_flow+=token_input[tk_num];
                relation.setAttribute(token_input[tk_num]);    //pushing attribute to relation
                tk_num++;
                idList(tk_num,token_type,token_input,token_linenum, relation, scheme_flow);
                if(token_type[tk_num] == "RIGHT_PAREN"){
                    scheme_flow+=token_input[tk_num];
                    tk_num++;//here scheme will end
                }else{throw tk_num;}
            }else{throw tk_num;}
        }else{throw tk_num;}
        //if scheme is successful, add Relation to relation_list
        relation_list.push_back (relation);
    }else{throw tk_num;}
    scheme_count++;
}

void DatalogProgram::fact(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum){
    if(token_type[tk_num]==fct_first) { //if its ID
        fact_flow += "\n  " + token_input[tk_num];
        int rel_index = return_matching_relation_index(token_input[tk_num]);    // index of relation
        tk_num++;
        if(token_type[tk_num] == "LEFT_PAREN") {
            fact_flow += token_input[tk_num];
            tk_num++;
            if(token_type[tk_num] == "STRING"){
                fact_flow+=token_input[tk_num];
                domains.push_back(token_input[tk_num]);
                Tuple n_tuple; // ----this is where you start adding vals to your tuples
                n_tuple.add_value(token_input[tk_num]);
                tk_num++;
                stringList(tk_num,token_type,token_input,token_linenum, n_tuple,fact_flow);
                if(token_type[tk_num] == "RIGHT_PAREN"){
                    fact_flow+=token_input[tk_num];
                    tk_num++;
                    if(token_type[tk_num] == "PERIOD"){
                        fact_flow+=token_input[tk_num];
                        tk_num++;//here fact will end
                    }else{throw tk_num;}
                }else{throw tk_num;}
                //IF TUPLE IS SUCCESSFUL, IT IS ADDED TO THE TUPLES LIST OF ITS RESPECTIVE
                relation_list.at(rel_index).setTuple(n_tuple);
            }else{throw tk_num;}
        }else{throw tk_num;}
    }else{throw tk_num;}
    fact_count++;
}

//predicate Q_MARK
void DatalogProgram::query(int &tk_num, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum){
    if(token_type[tk_num]==qry_first) { //if its ID
        query_flow += "\n  ";

        int curr_rel_index = return_matching_relation_index(token_input[tk_num]);

        Predicate predicate(tk_num,token_type,token_input,token_linenum);
        query_flow += predicate.return_the_predicate();
        if(token_type[tk_num] == "Q_MARK") {
            query_flow += token_input[tk_num];
            tk_num++;
        }else{throw tk_num;}

        //  ----------------- this is where query is being evaluated ---------------------------------------
        evaluate_query(predicate.params_tkn_type, predicate.the_parameter_list,curr_rel_index,predicate.return_the_predicate());
        //  ----------------- end query evaluation ---------------------------------------------------------------
    }else{throw tk_num;}
    query_count++;
}

//  ----------------- this is where query is being evaluated ---------------------------------------
void DatalogProgram::evaluate_query(vector <string> &token_list, vector <string> &parameter_list, int curr_rel_index,
                                    string query_string) {
    //relation_list.at(curr_rel_index).rename(token_list, parameter_list);
    Relation relation_copy1 = relation_list.at(curr_rel_index);
    relation_copy1.select(token_list, parameter_list);
    relation_copy1.project_for_lab(token_list,parameter_list);
    //maybe change later
    relation_copy1.rename(token_list, parameter_list);
    project_3_output+=relation_toString(relation_copy1,query_string, token_list); // the OUTPUT
}
//  ----------------- end query evaluation ---------------------------------------------------------------

//COMMA STRING stringList | lambda
void DatalogProgram::stringList(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                                vector<int> &token_linenum, Tuple& n_tuple, string& curr_out_flow){
    if(does_token_match(token_type[tk_num],strL_first,2)){
        if(token_type[tk_num] == "COMMA"){//first 1
            curr_out_flow+=token_input[tk_num];
            tk_num++;
            if(token_type[tk_num] == "STRING") {//STRING
                curr_out_flow+=token_input[tk_num];
                domains.push_back(token_input[tk_num]);
                n_tuple.add_value(token_input[tk_num]); // ADDING TO TUPPLE
                tk_num++;
                stringList(tk_num,token_type,token_input,token_linenum, n_tuple, curr_out_flow);
            }else{throw tk_num;}
        }else {//this is for when it's lambda
            //tk_num++;
        }
    }else if(!does_token_match(token_type[tk_num],strL_follow,14)){
        throw tk_num;//if not in follow list throw error
    }
}

void DatalogProgram::idList(int &tk_num, vector<string> &token_type, vector<string> &token_input,
                            vector<int> &token_linenum, Relation &relation, string& curr_out_flow){
    if(does_token_match(token_type[tk_num],idL_first,2)){ //if its any first of idList
        if(token_type[tk_num] == "COMMA"){//first 1
            curr_out_flow+=token_input[tk_num];
            tk_num++;
            if(token_type[tk_num] == "ID") {//STRING
                curr_out_flow+=token_input[tk_num];
                relation.setAttribute(token_input[tk_num]);    //pushing attribute to relation
                tk_num++;
                idList(tk_num,token_type,token_input,token_linenum, relation, curr_out_flow);
            }else{throw tk_num;}
        }else {//this is for when it's lambda
            //tk_num++;
        }
    }else if(!does_token_match(token_type[tk_num],idL_follow,15)){
        throw tk_num;//if not in follow list throw error
    }
}

bool DatalogProgram::does_token_match(string token, const string the_list[], int list_size){
    for(int i=0; i<list_size; i++){
        if(token.compare(the_list[i])==0)
            return true;
    }
    return false;
}

string DatalogProgram::datalogProgram_string(){//prints the out string
    return the_output;
}

string DatalogProgram::project_3_string() {
    return project_3_output;
}

string DatalogProgram::relation_toString(Relation & the_relation, string query_string, vector<string> tokens) {
    string rel_string = "";
    rel_string += query_string+"? ";
    if (!the_relation.getRows())
        rel_string += "No";
    else
        rel_string += "Yes("+ to_string(the_relation.getRows())+")";
    rel_string+="\n";
    int i=0; // if list is all STRING types, don't print out the tuple!!!!!!!!!!---------------------
    bool all_string= true;
    while((i<(int)tokens.size())&&all_string){
        if (tokens.at(i)=="ID")
            all_string = false;
        i++;
    }
    if (!all_string)
        rel_string+=the_relation.toStringTuples();
    return rel_string;
}

int DatalogProgram::return_matching_relation_index(string nm) {// returns relation that names matches input
    int rel_index = -1;
    for (int i=0; i<(int)relation_list.size(); i++){
        if(nm == relation_list.at(i).getName())
            rel_index = i;
    }
    return rel_index;
}