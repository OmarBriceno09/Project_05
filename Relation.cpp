//
// Created by OmarB on 11/2/2019.
//

#include "Relation.h"

Relation::Relation(string nm) {
    setName(nm);
}

/*Relation::Relation(Relation & relation) {
    Relation& operator = (Relation & relation){};
}*/

Relation::~Relation() {
}

int Relation::getCols() {
    return attributes.size();
}

int Relation::getRows() {
    return tuples_list.size();
}

void Relation::setName(string nm) {
    name = nm;
}

string Relation::getName() {
    return name;
}

string Relation::toStringTuples() {
    string the_output="";
    for (int i=0; i<(int)tuples_list.size(); i++){
        the_output+="  ";
        for(int j=0; j<(int)attributes.size();j++){
            the_output += attributes.at(j)+"="+tuples_list.at(i).get_value(j);
            if (j!=(int)attributes.size()-1)
                the_output+=", ";
        }
        the_output+= "\n";
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

vector<string> Relation::getAttributes_vector() {
    return attributes;
}

void Relation::setTuple(Tuple tpl) { // make sure tuple is added in alphabetical order, based on 1st element of tuple
    bool does_it_match = false;
    for (int i=0; i<getRows(); i++){
        if (tpl.getValuesList() == getTuple(i).getValuesList()) {
            does_it_match = true;
        }
    }
    if (!does_it_match) {
        int insert_index = returnRowToInsert(tpl);  //row of insertion is determined here, ordered alphabetically
        tuples_list.insert(tuples_list.begin() + insert_index, tpl);
    }
}

Tuple Relation::getTuple(int i) {
    return tuples_list.at(i);
}

int Relation::returnRowToInsert(Tuple tpl) {
    int insert_index = 0;
    int curr_r = 0;
    bool stop = false;
    while(curr_r<=getRows()-1){
        int curr_c = 0;
        //BE SURE TO SET THE ATTRIBUTES BEFORE PLACING TUPLES
        while (curr_c<=getCols()-1){
            if ((tpl.get_value(curr_c).compare(tuples_list.at(curr_r).get_value(curr_c))) == 0) {   //if elements of tuples are ==
                curr_c++;   //move ahead 1 col
            } else if ((tpl.get_value(curr_c).compare(tuples_list.at(curr_r).get_value(curr_c))) > 0) { //if element is greater move to next row...
                curr_r++;   //next row
                curr_c = getCols(); //restart cols
            } else{// if dif < 0, stop all!!!!
                stop = true;
                insert_index = curr_r;
                curr_r = getRows();
                curr_c = getCols();
            }
        }
    }
    if (!stop){
        insert_index = tuples_list.size();
    }
    return insert_index;
}

void Relation::rename(vector <string> tokens,vector<string> input) {    //length has to match!!!
    check_for_duplicates(tokens,input);
    int attribute_index = 0;
    for(int i=0;i<(int)tokens.size();i++){
        if (tokens.at(i) == "ID"){  // any chars in the input will result in removed cols
            int curr_id_i = return_var_name_index(input.at(i)); //returns index of var in var_instance_list
            if (i== stoi(var_instance_list.at(curr_id_i).get_value(0))){
                if(attributes.at(attribute_index) != input.at(i)){
                    attributes.at(attribute_index) = input.at(i); //Renaming Takes Place
                    attribute_index++;
                }
            }
        }else if (tokens.size() == attributes.size()){
            attribute_index++;
        }
    }
}

void Relation::select(vector <string> tokens,vector<string> input) {
    check_for_duplicates(tokens,input);
    for(int i=0;i<(int)attributes.size();i++){
        if (tokens.at(i) == "STRING"){
            for (int j=0;j<(int)tuples_list.size();j++){
                if (tuples_list.at(j).get_value(i) != input.at(i)){
                    tuples_list.erase(tuples_list.begin()+j);
                    j=-1;    //reset search, will be zero back at beginning of for loop
                }
            }
        } else if (tokens.at(i) == "ID"){   // ex ('a',X,X)?
            int curr_id_i = return_var_name_index(input.at(i));
            if (var_instance_list.at(curr_id_i).get_size()>1){// if variables repeat in the query
                for (int j=0;j<(int)tuples_list.size();j++){ //looking through each row
                    bool same_val = true;    //will it not match on all variables???
                    int curr_var_i = 0;
                    string previous_var = "";
                    while(curr_var_i < var_instance_list.at(curr_id_i).get_size() && same_val){
                        int current_index = stoi(var_instance_list.at(curr_id_i).get_value(curr_var_i));

                        string current_var = tuples_list.at(j).get_value(current_index);
                        if (current_var != previous_var && curr_var_i>0) {
                            same_val = false;
                        }
                        previous_var = current_var;
                        curr_var_i++;
                    }
                    if (!same_val){
                        tuples_list.erase(tuples_list.begin()+j);
                        j=-1;    //reset search, will be zero back at beginning of for loop
                    }
                }
            }
        }
    }


    vector <Tuple> temp_tuples = tuples_list;
    tuples_list.clear();
    for (int k=0;k<(int)temp_tuples.size();k++){
        setTuple(temp_tuples.at(k));
    }
}

void Relation::project(vector <string> tokens,vector<string> input) {
    check_for_duplicates(tokens,input);
    int attribute_index = 0;
    for (int i=0;i<(int)tokens.size();i++){
        bool was_deleted = false;
        if (tokens.at(i) != "ID") {
            attributes.erase(attributes.begin()+attribute_index);
            for (int j=0;j<(int)tuples_list.size();j++){
                tuples_list.at(j).remove_value(attribute_index);
            }
            was_deleted = true;
        }else{
            int curr_id_i = return_var_name_index(input.at(i)); //returns index of var in var_instance_list
            if (var_instance_list.at(curr_id_i).get_size()>1) {// if variables repeat in the query
                if (i!= stoi(var_instance_list.at(curr_id_i).get_value(0))){// if the current index of i is not equal to
                    attributes.erase(attributes.begin()+attribute_index);//the index of where the first instance of that
                    for (int j=0;j<(int)tuples_list.size();j++){              //variable appeared, delete the column.
                        tuples_list.at(j).remove_value(attribute_index);
                    }
                    was_deleted = true;
                }

            }
        }
        if (!was_deleted)//in the case a row was deleted, it does not count up through the columns.
            attribute_index++;
    }

    vector <Tuple> temp_tuples = tuples_list;
    tuples_list.clear();
    for (int k=0;k<(int)temp_tuples.size();k++){
        setTuple(temp_tuples.at(k));
    }
}

void Relation::project_for_lab(vector <string> tokens,vector<string> input) {    // projects for lab, so that if
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

void Relation::rel_union(Relation rel) {
    if (attributesMatch(rel.getAttributes_vector())){
        rel.re_sortAttributes(attributes);
        for(int i=0;i<(int)rel.tuples_list.size();i++){
            setTuple(rel.tuples_list.at(i));
        }
    }
}

void Relation::re_sortAttributes(vector<string> new_order) {
    if(attributesMatch(new_order)){
        vector<Tuple> saved_list = tuples_list;
        tuples_list.clear();

        for (int i=0;i<(int)saved_list.size();i++){
            Tuple organizedTpl;
            for (int j=0;j<(int)new_order.size();j++){
                for(int k=0;k<(int)attributes.size();k++){
                    if (new_order.at(j)==attributes.at(k)) {
                        organizedTpl.add_value(saved_list.at(i).get_value(k));
                    }
                }
            }
            setTuple(organizedTpl);
        }
        attributes = new_order;
    }
}

void Relation::check_for_duplicates(vector <string> tokens,vector<string> input) {
    var_instance_list.clear();
    for (int i=0; i<(int)input.size(); i++) {
        if (tokens.at(i) == "ID"){  // only with id's
            bool found_match = false;
            int j = 0;
            int curr_var =0;
            while(curr_var<(int)var_instance_list.size() && !found_match){
                if (input.at(i)==var_instance_list.at(curr_var).get_var_name()){
                    found_match = true;
                    j=curr_var;
                }
                curr_var++;
            }
            if(found_match){
                var_instance_list.at(j).add_value(to_string(i));
            }else{
                Tuple tuple;
                tuple.set_var_name(input.at(i));
                tuple.add_value(to_string(i));
                var_instance_list.push_back(tuple);
            }
        }
    }

    //printing var_instance_list, will erase eventually
    /*for (int k=0; k<var_instance_list.size(); k++) {
        cout<<" "<<var_instance_list.at(k).get_var_name()<<": "<<var_instance_list.at(k).toStringTuple()<<endl;
    }
    cout<<"ok if no tokens..."<<endl;
    cout<<endl;*/
}

int Relation::return_var_name_index(string name) {
    int index =-1;
    for (int k=0; k<(int)var_instance_list.size(); k++) {
        if (var_instance_list.at(k).get_var_name() == name)
            index = k;
    }
    return index;
}

bool Relation::attributesMatch(vector<string> att) {
    vector<string> v1 = attributes;
    vector<string> v2 = att;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    return v1 == v2;
}