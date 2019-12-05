//
// Created by OmarB on 11/2/2019.
//

#include "Relation.h"

Relation::Relation(string nm) {
    setName(nm);
}

Relation::~Relation() {
    Tuple* d_tpl;
    for(auto it=new_inserted_tuples.begin();it!=new_inserted_tuples.end();++it){
        d_tpl = (*it);
        d_tpl = nullptr;
        delete d_tpl;

    }
    new_inserted_tuples.clear();
}

int Relation::getCols() {
    return attributes.size();
}

int Relation::getRows() {
    return tpl_list.size();
}

void Relation::setName(string nm) {
    name = nm;
}

string Relation::getName() {
    return name;
}

string Relation::toStringTuples() {
    string the_output="";
    Tuple prt_tpl;
    for(auto it=tpl_list.begin();it!=tpl_list.end();++it){
        prt_tpl = (*it);
        the_output+="  ";
        for(int j=0; j<(int)attributes.size();j++){
            the_output += attributes.at(j)+"="+prt_tpl.at(j);
            if (j!=(int)attributes.size()-1)
                the_output+=", ";
        }
        the_output+= "\n";
    }
    return the_output;
}

string Relation::toStringNewTuples() {//-------------------------CHANGE THIS ONE DO IT !!! AHHH NOT IN ORDER!!!--------
    /*Tuple prt_tpl;
    for(auto it=new_inserted_tuples.begin();it!=new_inserted_tuples.end();++it){
        prt_tpl = (**it);
        the_output+="  ";
        for(int j=0; j<(int)attributes.size();j++){
            the_output += attributes.at(j)+"="+prt_tpl.at(j);
            if (j!=(int)attributes.size()-1)
                the_output+=", ";
        }
        the_output+= "\n";
    }*/
    string the_output="";
    Tuple prt_tpl;
    for(auto it=tpl_list.begin();it!=tpl_list.end();++it){
        prt_tpl = (*it);
        if (foundTuple(prt_tpl)) {
            the_output += "  ";
            for (int j = 0; j < (int) attributes.size(); j++) {
                the_output += attributes.at(j) + "=" + prt_tpl.at(j);
                if (j != (int) attributes.size() - 1)
                    the_output += ", ";
            }
            the_output += "\n";
        }
    }
    return the_output;
}

string Relation::toStringAttributeList() {
    string the_output="  ";
    for (int i=0; i<(int)attributes.size(); i++){
        the_output += " "+attributes.at(i);
        if (i!=(int)attributes.size()-1)
            the_output+=", ";
    }
    return the_output;
}

void Relation::setAttribute(string attribute) {
    attributes.push_back (attribute);
}

string Relation::getAttribute(int i) {
    return attributes.at(i);
}

void Relation::setAttribute_as_vector(vector<string> &atts) {
    attributes = atts;
}

vector<string>& Relation::getAttributes_vector() {
    return attributes;
}

bool Relation::setTuple(Tuple & tpl) {
    return tpl_list.insert(tpl).second;
}

void Relation::clearTuples() {
    tpl_list.clear();
}

void Relation::rename(vector <string>& tokens,vector<string>& input) {    //length has to match!!!
    check_for_duplicates_in_query(tokens,input);
    int attribute_index = 0;    // in case list has changes and token list doesn't reflect col change
    for(int i=0;i<(int)tokens.size();i++){
        if (tokens.at(i) == "ID"){  // any chars in the input will result in removed cols
            int curr_tkn_index = return_var_name_index(input.at(i)); //returns index of var in var_instance_list
            int index_of_orig_for_tkn =  stoi(var_instance_list.at(curr_tkn_index).at(0));//index of org
            if (i == index_of_orig_for_tkn) {
                attributes.at(attribute_index) = input.at(i); //Renaming Takes Place
                attribute_index++;
            }
        }
    }
}

void Relation::select(vector <string>& tokens,vector<string>& input) {
    check_for_duplicates_in_query(tokens,input);
    for(int i=0;i<(int)attributes.size();i++){
        if (tokens.at(i) == "STRING"){
            //-----------------------------------for when erasing something during iter------------------
            Tuple s_tpl;
            for(auto it=tpl_list.begin();it!=tpl_list.end();){
                s_tpl = (*it);
                if(s_tpl.at(i) != input.at(i)){
                    it = tpl_list.erase(it);
                } else{
                    ++it;
                }
            }
            //--------------------------------------------------------------------------------------------------
        } else if (tokens.at(i) == "ID"){   // ex ('a',X,X)?
            int curr_id_i = return_var_name_index(input.at(i));
            if (var_instance_list.at(curr_id_i).size()>1){// if variables repeat in the query
                Tuple i_tpl;
                for(auto it=tpl_list.begin();it!=tpl_list.end();){
                    i_tpl = (*it);
                    bool same_val = true;
                    int curr_var_i = 0;
                    string previous_var = "";
                    while(curr_var_i < (int)var_instance_list.at(curr_id_i).size() && same_val){
                        int current_index = stoi(var_instance_list.at(curr_id_i).at(curr_var_i));

                        string current_var = i_tpl.at(current_index);
                        if (current_var != previous_var && curr_var_i>0) {
                            same_val = false;
                        }
                        previous_var = current_var;
                        curr_var_i++;
                    }
                    if (!same_val){
                        it = tpl_list.erase(it);
                    }else{
                        ++it;
                    }
                }
            }
        }
    }
}

void Relation::project(vector <string>& tokens,vector<string>& input) {
    check_for_duplicates_in_query(tokens,input);
    vector <bool> removed_indexes;// set removed to true
    vector <bool> temp_removed_indexes;
    for (int i=0;i<(int)tokens.size();i++){ //interpret query first!!!
        if (tokens.at(i) != "ID") {
            removed_indexes.push_back(true);
        }else{
            int curr_id_i = return_var_name_index(input.at(i)); //returns index of var in var_instance_list
            if ((var_instance_list.at(curr_id_i).size()>1)&&(i!=stoi(var_instance_list.at(curr_id_i).at(0)))){
                // if its a repeating query att, but its it's first instance ...
                removed_indexes.push_back(true);
            } else
                removed_indexes.push_back(false);
        }
    }
    temp_removed_indexes = removed_indexes;
    for(int k=0;k<(int)temp_removed_indexes.size();k++){
        if (temp_removed_indexes.at(k)) {
            attributes.erase(attributes.begin() + k);
            temp_removed_indexes.erase(temp_removed_indexes.begin()+k);// so it matches
            k--;
        }
    }

    string debug_str="";//-----------------------------------------------------------------
    Relation temp_relation("t");    //creates a temp relation
    temp_relation.setAttribute_as_vector(attributes);
    Tuple p_tpl;
    for(auto it=tpl_list.begin();it!=tpl_list.end();++it){
        p_tpl = (*it);
        temp_removed_indexes = removed_indexes;
        for(int k=0;k<(int)temp_removed_indexes.size();k++){
            if (temp_removed_indexes.at(k)) {
                p_tpl.remove_value(k);
                temp_removed_indexes.erase(temp_removed_indexes.begin()+k);// so it matches
                k--;
            }
        }
        temp_relation.setTuple(p_tpl);  //sets new tuples in temp relation
        //deubg..
        /*debug_str.clear();
        debug_str="in project of rel "+name+": "+to_string(j)+" out of "+to_string(tuples_list.size());
        cout <<debug_str<< "\t\r" << std::flush;*/
        //deubg...
    }
    tpl_list.clear();
    tpl_list = temp_relation.tpl_list;    //copies temp relation tuples into tuples of this relation
}

void Relation::project_for_lab(vector <string>& tokens,vector<string>& input) {    // projects for lab, so that if
    int i=0;
    bool all_string= true;
    while(i<(int)tokens.size()&&all_string){
        if (tokens.at(i)=="ID")
            all_string = false;
        i++;
    }
    if (!all_string)
        project(tokens,input);
}

int Relation::rel_union(Relation& rel) {
    // cout<<"----in UNION of relation class, new tuples ----------"<<endl;
    Tuple* d_tpl;
    for(auto it=new_inserted_tuples.begin();it!=new_inserted_tuples.end();++it){
        d_tpl = (*it);
        d_tpl = nullptr;
        delete d_tpl;
    }
    new_inserted_tuples.clear();

    if (attributesMatch(rel.getAttributes_vector())){
        Tuple organizedTpl;
        Tuple s_tpl;
        for(auto it=rel.tpl_list.begin();it!=rel.tpl_list.end();++it) {
            organizedTpl.clear();
            s_tpl = (*it);
            for (int j = 0; j < (int) attributes.size(); j++) {
                for (int k = 0; k < (int) rel.getAttributes_vector().size(); k++) {
                    if (attributes.at(j) == rel.getAttributes_vector().at(k)) {
                        organizedTpl.push_back(s_tpl.at(k));
                    }
                }
            }
            if(setTuple(organizedTpl)){
                Tuple *tpl = new Tuple;
                *tpl = organizedTpl;
                new_inserted_tuples.insert(tpl);
                tpl = nullptr;
                delete tpl;
            }
            //deubg..
            /*debug_str.clear();
            debug_str="in union of rel "+name+": "+to_string(i)+" out of "+to_string(saved_list.size());
            cout <<debug_str<< "\t\r" << std::flush;*/
            //deubg...
        }
    }
    return new_inserted_tuples.size();
}

void Relation::rel_join(Relation& rel) {//----------------------------------CHECK---------------------------------------
    string debug_str="";//ERASE LATER
    vector<string> new_attributes;  // the new set of attributes this relation will have
    //vector<string> old_attributes;  //old attributes will be saved for future comparisons
    vector<Tuple> matching_pairs;
    vector<int> other_indexes;  //indexes of the different attributes
    formNewAttributes(matching_pairs, new_attributes,other_indexes, attributes, rel.getAttributes_vector());
    /*cout<<"------------------------matching pairs len: "<<matching_pairs.size()<<endl;
    for(int h=0;h<(int)matching_pairs.size();h++){
        cout<<"  "<<matching_pairs.at(h).get_value(0)<<" vs. "<<matching_pairs.at(h).get_value(1)<<endl;
    }*/
    set<Tuple> saved_list = tpl_list;
    tpl_list.clear();
    //old_attributes = attributes;
    attributes = new_attributes; // so that program doesn't break in setTuples part.
    Tuple joined_tpl;

    Tuple r1_tpl;
    Tuple r2_tpl;
    for(auto it=saved_list.begin();it!=saved_list.end();++it) {
        r1_tpl = (*it);
        for(auto it2=rel.tpl_list.begin();it2!=rel.tpl_list.end();++it2) {
            r2_tpl = (*it2);
            bool comp_match = true;
            int v=0;
            while((v<(int)matching_pairs.size())&&comp_match) {// loops through all pairs made
                int j = stoi(matching_pairs.at(v).at(0));
                int k = stoi(matching_pairs.at(v).at(1));
                if (r1_tpl.at(j) != r2_tpl.at(k)) {
                    comp_match = false;
                }
                v++;
            }
            if (comp_match) {//IF TUPLES MATCH THEY WILL BE JOINED
                joined_tpl.clear();//changing joined_tpl
                create_row_tuple(joined_tpl,r1_tpl,r2_tpl,other_indexes);
                tpl_list.insert(joined_tpl);
            }
        }
        //deubg..
        /*debug_str.clear();
        debug_str="in join of rel "+name+": "+to_string(i)+" out of "+to_string(saved_list.size());
        cout <<debug_str<< "\t\r" << std::flush;*/
        //deubg...
    }
}

void Relation::create_row_tuple(Tuple &joined_tpl,Tuple &origTpl, Tuple &otherTpl, vector<int> &other_indexes) {
    for (unsigned int i=0; i<origTpl.size();i++){//adds all values of t1 in rel1
        joined_tpl.push_back(origTpl.at(i));
    }
    for(unsigned int j=0;j<other_indexes.size();j++){//adds all but the values that match in t1, form t2 in rel2
        joined_tpl.push_back(otherTpl.at(other_indexes.at(j)));
    }
}

bool Relation::attributesMatch(vector<string>& att) {
    vector<string> v1 = attributes;
    vector<string> v2 = att;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    return v1 == v2;
}

void Relation::formNewAttributes(vector<Tuple> &matching_pairs, vector<string> &changed_att, vector<int>& other_indexes,
                                 vector<string>& att1, vector<string>& att2) {//CHECKS IF ATTRIBUTES ARE COMPARABLE OR NOT ...
    //bool can_join=true;
    vector<int> match_att_index;
    //if (!attributesMatch(att2)/*&&!all_attributesDiffer(att2)*/) {
    for (int i = 0; i < (int)att1.size(); i++) {
        for (int j = 0; j < (int)att2.size(); j++){
            if (att1.at(i) == att2.at(j)) {
                Tuple match_index;
                match_index.push_back(to_string(i));//from rel1
                match_index.push_back(to_string(j));//from rel2
                matching_pairs.push_back(match_index);
                match_att_index.push_back(j);//pushes back index of matching att
            }
        }
    }
    for(int q=0;q<(int)att2.size();q++){
        if(!foundIndex(match_att_index,q)){
            other_indexes.push_back(q);
        }
    }
    //other_indexes
    changed_att.reserve(att1.size() + att2.size());//creating the new attributes
    changed_att.insert(changed_att.end(), att1.begin(), att1.end());
    changed_att.insert(changed_att.end(), att2.begin(), att2.end());
    for (int i = 0; i < (int)changed_att.size(); i++) {
        for (int j = i + 1; j < (int)changed_att.size(); j++)
            if (changed_att.at(i) == changed_att.at(j)) {
                //matched_att.push_back(changed_att.at(j));
                changed_att.erase(changed_att.begin() + j); // these are the new attributes in the relation
            }
    }
}

void Relation::check_for_duplicates_in_query(vector <string>& tokens,vector<string> &input) {//duplicates in the query
    var_instance_list.clear();
    for (int i = 0; i < (int) input.size(); i++) {
        if (tokens.at(i) == "ID") {  // only with id's
            bool found_match = false;
            int j = 0;
            int curr_var = 0;
            while (curr_var < (int) var_instance_list.size() && !found_match) {
                if (input.at(i) == var_instance_list.at(curr_var).get_var_name()) {
                    found_match = true;
                    j = curr_var;
                }
                curr_var++;
            }
            if (found_match) {
                var_instance_list.at(j).push_back(to_string(i));
            } else {
                Tuple tuple;
                tuple.set_var_name(input.at(i));
                tuple.push_back(to_string(i));
                var_instance_list.push_back(tuple);
            }
        }
    }
}

int Relation::return_var_name_index(string& name) {
    int index =-1;
    for (int k=0; k<(int)var_instance_list.size(); k++) {
        if (var_instance_list.at(k).get_var_name() == name)
            index = k;
    }
    return index;
}

bool Relation::foundIndex(vector<int> & vect, int val) {
    for(int i=0;i<(int)vect.size();i++){
        if (vect.at(i)==val){
            return true;
        }
    }
    return false;
}

bool Relation::foundTuple(Tuple& tpl) {
    Tuple prt_tpl;
    for(auto it=new_inserted_tuples.begin();it!=new_inserted_tuples.end();++it){
        prt_tpl = (**it);
        if (prt_tpl == tpl){return true;}
    }
    return false;
}