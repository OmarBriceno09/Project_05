//
// Created by OmarB on 11/16/2019.
//

#ifndef PROJECT_04_MAIN_H
#define PROJECT_04_MAIN_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <bits/stdc++.h>
#include "DatalogProgram.h"

using namespace std;

enum state_machine {comma=0, period=1, q_mark=2, left_paren=3, right_paren=4, colon=5, colon_dash=6, multiply=7,
    add=8, schemes=9, facts=10, rules=11, queries=12, s_id=13, s_string=14, comment=15, s_undef=16, e_o_f=17};

const string queries_s = "Queries";
const string schemes_s = "Schemes";
const string facts_s = "Facts";
const string rules_s = "Rules";

bool decide_machine(char, state_machine&);
bool decide_id_or_und(char, state_machine&);
bool id_state1(char);
bool finishes_1_step(state_machine&);
bool is_it_keyid(string);

void tokenizing_state_machine(ifstream&,vector<string>&, vector<string>&, vector<int>&);
void push_to_input_vectors(string, string, int, vector<string>&, vector<string>&, vector<int>&);

#endif //PROJECT_04_MAIN_H
