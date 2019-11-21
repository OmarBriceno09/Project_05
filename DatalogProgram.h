//
// Created by OmarB on 11/16/2019.
//

#ifndef PROJECT_04_DATALOGPROGRAM_H
#define PROJECT_04_DATALOGPROGRAM_H
#include <vector>
#include <bits/stdc++.h>
#include "Rule.h"
#include "Predicate.h"
#include "Relation.h"
#include "Tuple.h"

using namespace std;

class DatalogProgram {
public:
    DatalogProgram(vector<string>&, vector<string>&, vector<int>&);
    ~DatalogProgram();

    string datalogProgram_string();
    string project_3_string();
    string project_4_string();
    vector<Relation> relation_list;
    vector<Rule> rule_list;
    //void dataLogProgram(vector<string>&, vector<string>&, vector<int>&);
    string query_toString(Relation&, string, vector<string>); //this will go through many edits

private:
    string the_output = "";
    string out_flow = "";
    string scheme_flow="";
    string fact_flow="";
    string rule_flow="";
    string query_flow="";
    vector <string> domains;

    string project_3_output = "";
    string project_4_output = "";

    int tk_num = 0;
    int scheme_count=0;
    int fact_count=0;
    int rule_count=0;
    int query_count=0;

    void schemeList(int&, vector<string>&, vector<string>&, vector<int>&);
    void factList(int&, vector<string>&, vector<string>&, vector<int>&);
    void ruleList(int&, vector<string>&, vector<string>&, vector<int>&);
    void queryList(int&, vector<string>&, vector<string>&, vector<int>&);

    void scheme(int&, vector<string>&, vector<string>&, vector<int>&);
    void fact(int&, vector<string>&, vector<string>&, vector<int>&);
    void rule(int&, vector<string>&, vector<string>&, vector<int>&);//a
    void query(int&, vector<string>&, vector<string>&, vector<int>&);

    void evaluate_query(vector<string>&, vector<string>&, int, string);//new
    void evaluate_predicates(vector<string>&,vector<string>&, Relation&);
    int evaluate_all_rules(); // new
    bool evaluate_rule(Rule&); // new

    void headPredicate(int&, vector<string>&, vector<string>&, vector<int>&, string&);//a

    void predicateList(int&, vector<string>&, vector<string>&, vector<int>&, string&);//a
    void stringList(int&, vector<string>&, vector<string>&, vector<int>&, Tuple&, string&);
    void idList(int&, vector<string>&, vector<string>&, vector<int>&, Relation&, string&);

    bool does_token_match(string, const string[], int);

    int return_matching_relation_index(string);



//declaring first sets
    const string dP_first = "SCHEMES";
    const string schL_first[2]= {"ID", ""};
    const string fctL_first[2]= {"ID", ""};
    const string rlL_first[2]= {"ID", ""};
    const string qryL_first[2]= {"ID", ""};
    const string sch_first = "ID";
    const string fct_first = "ID";
    const string qry_first = "ID";

    const string strL_first[2] = {"COMMA",""};
    const string idL_first[2] = {"COMMA",""};

//declaring follow sets
    const string dP_follow = "EOF";
    const string schL_follow[15]= {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH",
                                   "MULTIPLY","ADD","FACTS","RULES","QUERIES","ID","STRING","EOF"};
    const string fctL_follow[14]= {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH",
                                   "MULTIPLY","ADD","RULES","QUERIES","ID","STRING","EOF"};
    const string rlL_follow[11]= {"COMMA","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","MULTIPLY","ADD",
                                  "QUERIES","ID","STRING","EOF"};
    const string qryL_follow= "EOF";
    const string sch_follow[15] = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH",
                                   "MULTIPLY","ADD","FACTS","RULES","QUERIES","ID","STRING","EOF"};
    const string fct_follow[14] = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH",
                                   "MULTIPLY","ADD","RULES","QUERIES","ID","STRING","EOF"};
    const string rl_follow[11] = {"COMMA","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","MULTIPLY","ADD",
                                  "QUERIES","ID","STRING","EOF"};
    const string qry_follow[9] = {"COMMA","Q_MARK","LEFT_PAREN","RIGHT_PAREN","MULTIPLY","ADD","ID","STRING","EOF"};
    const string hPd_follow[13] = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH",
                                   "MULTIPLY","ADD","QUERIES","ID","STRING","EOF"};
    const string pd_follow[12] = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON",
                                  "MULTIPLY","ADD","QUERIES","ID","STRING","EOF"};
    const string strL_follow[14] = {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH",
                                    "MULTIPLY","ADD","RULES","QUERIES","ID","STRING","EOF"};
    const string idL_follow[15]= {"COMMA","PERIOD","Q_MARK","LEFT_PAREN","RIGHT_PAREN","COLON","COLON_DASH",
                                  "MULTIPLY","ADD","FACTS","RULES","QUERIES","ID","STRING","EOF"};
};

#endif //PROJECT_04_DATALOGPROGRAM_H
