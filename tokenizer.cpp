//this is Project 01 code
// Created by OmarB on 9/28/2019.
//
#include "main.h"
void tokenizing_state_machine(ifstream &txt_file, vector<string> &token_type, vector<string> &token_input, vector<int> &token_linenum){
    string token_label[18] = {"COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
                              "MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT",
                              "UNDEFINED", "EOF"};
    if (txt_file.fail()){
        cout<<"ERROR: Incorrect directory.";
    }
    else{ //this is where the magic happens :)
        char curr_char = ' ';
        int line_number = 1;
        int displayed_line_number = 1;
        bool critical_state = false; // when final or fail state is reached after reading a set of characters
        bool processing_state = false;
        bool enclosed_comment = false;
        bool apostrophe_char = false;
        state_machine mach = s_id;
        string output_t_value;

        while (!txt_file.eof()) {
            char next_char = txt_file.peek();//looks ahead
            if (isprint(curr_char) && curr_char!=' ' && mach != s_string && mach != comment) {
                if (!processing_state) {// to skip over spaces when beginning a state
                    processing_state = decide_machine(curr_char, mach);
                }
                if (processing_state) { //these are for all tokens that are not strings or comments
                    if (mach == s_undef){
                        processing_state = false;
                        critical_state = true;
                    }else if(finishes_1_step(mach)) { // for first step state machine
                        processing_state = false;
                        critical_state = true;
                    } else if(mach == colon || mach == colon_dash){
                        if (curr_char == ':' && next_char != '-'){ //stops when its just colon
                            processing_state = false;
                            critical_state = true;
                        }else if (curr_char == '-'){ // stops when it's colon dash
                            mach = colon_dash;
                            processing_state = false;
                            critical_state = true;
                        }
                    }else if (id_state1(curr_char)) { // decides if it's still an id or any special key
                        if (!id_state1(next_char)) { // if next char is not alphanum
                            if (!is_it_keyid(output_t_value+curr_char)) // if it is not a special key
                                mach = s_id;    // its just a regular id
                            processing_state = false;
                            critical_state = true;
                        }
                    }
                    output_t_value+= curr_char;
                }
            }else{
                if (mach == s_string){  //string already begun, skips over any char
                    if (curr_char == '\'' && !apostrophe_char) {
                        if (next_char != '\'') { // any character but another ' means it ends
                            processing_state = false;
                            critical_state = true;
                            output_t_value += curr_char; //to include the next char
                        } else {
                            apostrophe_char = true; // otherwise it sets a bool so that the next ' is ignored
                        }   // that way '' = ', so a '' is read the same as any character
                    }else{
                        apostrophe_char = false;    // one it passes the second ' it resumes looking for an end quote
                    }
                }// end string state machine
                else if (mach == comment){ // for comments
                    if (output_t_value.back() == '#' && curr_char == '|' && !enclosed_comment) {// determines beginning of comment is enclosed
                        enclosed_comment = true;
                    }
                    else if (enclosed_comment){
                        if (output_t_value.back() == '|' && curr_char == '#'){ // checking if comment closed
                            enclosed_comment = false;
                            processing_state = false;
                            critical_state = true;
                            output_t_value += curr_char; // as a means of avoiding new line in single lined comments
                        }
                    }else if(!enclosed_comment && next_char == '\n'){ //looks over all chars ti'll the end of line
                        processing_state=false;
                        critical_state=true;
                        output_t_value += curr_char; // as a means of avoiding new line in single lined comments
                    }
                } // end comment state machine
                if ((mach == s_string || mach == comment)&&!critical_state) { //use this to avoid extra \n
                    output_t_value += curr_char;
                }
            }

            if (curr_char == '\n'){//line number increments if end of line
                ++line_number;
                if (mach != s_string && mach != comment) { // apparently, i need to print the line
                    displayed_line_number = line_number;    //where the string/comment starts
                }
            }

            if (critical_state){
                push_to_input_vectors(token_label[mach],output_t_value,displayed_line_number,token_type,token_input,token_linenum);
                critical_state = false;
                output_t_value.clear();
                mach = s_id; // resets mach to default id
            }
            txt_file.get(curr_char); //this gets next char
        }
        if (mach == comment && !enclosed_comment){ // in case last line is an unenclosed comment
            push_to_input_vectors(token_label[mach],output_t_value,displayed_line_number,token_type,token_input,token_linenum);
            output_t_value.clear();
        }else if (mach != s_id) { // if it doesn't end at it's default machine selection
            mach = s_undef; // it is undefined, most likely an unclosed comment/ string
            push_to_input_vectors(token_label[mach],output_t_value,displayed_line_number,token_type,token_input,token_linenum);
            output_t_value.clear();
        }

        mach = e_o_f;
        push_to_input_vectors(token_label[mach],output_t_value,line_number,token_type,token_input,token_linenum);
    }
}