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
                                //rule_flow += token_input[tk_num]; //begin fact flow - comment out for project 4
                                tk_num++;
                                project_4_output+="Rule Evaluation\n";
                                ruleList(tk_num, token_type, token_input, token_linenum);
                                int passes = evaluate_all_rules();//evaluate all rules once outside of rule list
                                project_4_output+="\nSchemes populated after "+to_string(passes)+" passes through the Rules.\n\n";
                                out_flow +=
                                        to_string(rule_count) + ")" + rule_flow; //append rule flow with nums of facts
                                if (token_type[tk_num] == "QUERIES") { //QUERIES COLON query queryList
                                    out_flow += "\n" + token_input[tk_num] + "(";
                                    tk_num++;
                                    if (token_type[tk_num] == "COLON") {
                                        query_flow += token_input[tk_num];
                                        tk_num++;
                                        project_3_output+="Query Evaluation\n";
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

            Rule rule(tk_num,token_type,token_input,token_linenum);    //creating instance of rule
            rule_list.push_back(rule);
            //evaluate_rule(rule);
            //project_4_output += "EVALUATED\n";
            //cout<<project_4_output<<endl;
            rule_flow+=rule.out_rule();//without \n orig
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

int DatalogProgram::evaluate_all_rules() {
    bool changed=true;
    vector<bool> evaluations_changed; //<- if all evaluated rules are 0, then it changed becomes false;
    int iter=0;
    while(changed){
        iter++;
        evaluations_changed.clear();
        for(int i=0;i<(int)rule_list.size();i++){
            bool temp = evaluate_rule(rule_list.at(i));
            evaluations_changed.push_back(temp);// each rule is evaluated, and its result
        }                                                                     //is pushed back to the vector
        if(all_of(evaluations_changed.begin(), evaluations_changed.end(), [](bool v) { return !v; }))
            changed = false;
    }
    return iter;
}


bool DatalogProgram::evaluate_rule(Rule& rule) {
    bool changed_database = false; //false is database is not changed, if all rules eval output false, STOP EVAL
    int main_rel_indx = return_matching_relation_index(rule.main_relation_name);
    vector<string> saved_rule_rel_att = relation_list.at(main_rel_indx).getAttributes_vector();
    vector<string> rule_rel_att_tkns = rule.main_changed_att_tkns;
    relation_list.at(main_rel_indx).rename(rule_rel_att_tkns,rule.main_changed_attributes);//changes attributes to vars
    int rel_1_indx = return_matching_relation_index(rule.relations_names.at(0));
    Relation relation_copy1 = relation_list.at(rel_1_indx);//-------------CURRENT RELATION COPY
    vector<string> rel_c1_tkns = rule.resp_rel_att_tkns.at(0);
    evaluate_predicates(rel_c1_tkns,rule.resp_rel_attributes.at(0),relation_copy1);
    for(int i=0;i<(int)rule.relations_names.size();i++){
        rel_1_indx = return_matching_relation_index(rule.relations_names.at(i));
        if(i>0){
            Relation relation_copy2 = relation_list.at(rel_1_indx);//-------------IMPORTANT
            vector<string> rel_c2_tkns = rule.resp_rel_att_tkns.at(i);
            evaluate_predicates(rel_c2_tkns,rule.resp_rel_attributes.at(i),relation_copy2);
            relation_copy1.rel_join(relation_copy2);
        }
    }
    vector<string> tkns_for_project;
    for(int i=0;i<(int)relation_copy1.getAttributes_vector().size();i++){
        string id_pr = "STRING";
        for(int j=0;j<(int)rule.main_changed_attributes.size();j++){
            if (relation_copy1.getAttributes_vector().at(i)==rule.main_changed_attributes.at(j)){
                id_pr = "ID";
            }
        }
        tkns_for_project.push_back(id_pr);
    }
    relation_copy1.project(tkns_for_project,relation_copy1.getAttributes_vector());//risky might just use eval predicates
    //bool new_tuples = false;
    if(relation_list.at(main_rel_indx).rel_union(relation_copy1)>0)
        changed_database = true;
    relation_copy1.rename(rule_rel_att_tkns, saved_rule_rel_att);
    relation_list.at(main_rel_indx).rename(rule_rel_att_tkns, saved_rule_rel_att);
    project_4_output+= rule.out_rule()+"\n";
    project_4_output+=relation_list.at(main_rel_indx).toStringNewTuples();//.toStringNewTuples();
    return changed_database;
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
    //thee_big_three
    evaluate_predicates(token_list,parameter_list,relation_copy1);
    /*relation_copy1.select(token_list, parameter_list);
    relation_copy1.project_for_lab(token_list,parameter_list);
    relation_copy1.rename(token_list, parameter_list);*/
    project_3_output+=query_toString(relation_copy1,query_string, token_list); // the OUTPUT
}
//  ----------------- end query evaluation ---------------------------------------------------------------
void DatalogProgram::evaluate_predicates(vector<string> &token_list, vector<string> &parameter_list, Relation &rel) {
    rel.select(token_list, parameter_list);
    rel.project_for_lab(token_list,parameter_list);
    rel.rename(token_list, parameter_list);
}


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

string DatalogProgram::project_4_string() {
    return project_4_output;
}

string DatalogProgram::query_toString(Relation & the_relation, string query_string, vector<string> tokens) {
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