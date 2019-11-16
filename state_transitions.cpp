// Created by OmarB on 9/28/2019. this is where the actual magic happens :)
#include "main.h"

bool decide_machine(char the_char, state_machine& mach){
    bool start_machine = true;
    switch(the_char){
        case ',': mach = comma; break;
        case '.': mach = period; break;
        case '?': mach = q_mark; break;
        case '(': mach = left_paren; break;
        case ')': mach = right_paren; break;
        case ':': mach = colon; break; //colon dash is determined later
        case '*': mach = multiply; break;
        case '+': mach = add; break;
        case 'S': mach = schemes; break;
        case 'F': mach = facts; break;
        case 'R': mach = rules; break;
        case 'Q': mach = queries; break;
        case '\'': mach = s_string; break;
        case '#': mach = comment; break;
        default: decide_id_or_und(the_char, mach);break;
    }
    return start_machine;
}

bool decide_id_or_und(char the_char, state_machine& mach){
    bool start_machine = true;
    if (isalpha(the_char))
        mach = s_id;
    else{
        mach = s_undef;
        start_machine = false;
    }
    return start_machine;
}

bool id_state1(char the_char){
    bool critical=false;
    if (isalnum(the_char))
        critical=true;
    return critical;
}

bool finishes_1_step(state_machine& mach){
    bool finished = false;
    if (mach == period || mach == comma || mach == q_mark || mach == left_paren ||
        mach == right_paren || mach == multiply || mach == add)
        finished = true;
    return finished;
}

bool is_it_keyid(string id){
    bool special_id=false;
    if (id.compare(queries_s) == 0||id.compare(schemes_s) == 0
        ||id.compare(facts_s) == 0||id.compare(rules_s) == 0) {
        special_id = true;
    }
    return special_id;
}

void push_to_input_vectors(string id, string out, int ln, vector<string> &t_type, vector<string> &t_out, vector<int> &t_ln){
    //Project 2 edit:
    if (id!="COMMENT") {
        t_type.push_back(id);
        t_out.push_back(out);
        t_ln.push_back(ln);
    }
}