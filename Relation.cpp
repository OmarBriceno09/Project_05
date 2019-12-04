//
// Created by OmarB on 11/2/2019.
//

#include "Relation.h"

Relation::Relation(string nm) {
    setName(nm);
}

Relation::~Relation() {
    for (int x=0;x<(int)new_inserted_tuples.size();x++){
        Tuple* tpl = new_inserted_tuples.at(x);
        tpl = nullptr;
        delete tpl;
    }
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

string Relation::toStringNewTuples() {
    string the_output="";
    for (int i=0; i<(int)tuples_list.size(); i++){
        if(foundTuple(tuples_list.at(i))) {
            the_output += "  ";
            for (int j = 0; j < (int) attributes.size(); j++) {
                the_output += attributes.at(j) + "=" + tuples_list.at(i).get_value(j);
                if (j != (int) attributes.size() - 1)
                    the_output += ", ";
            }
            the_output += "\n";
        }
    }
    //debug
    /*cout<<"the new tuples"<<endl;
    for(int j=0;j<(int)union_n_inserted_tuples_indexes.size();j++){
        int x = union_n_inserted_tuples_indexes.at(j);
        cout<<"at ["<<x<<"]:"<<getTuple(x).toStringTuple()<<endl;
    }
    cout<<"vs"<<endl;
    cout<<toStringTuples()<<endl;
    */
    return the_output;
}

int Relation::getNumberOfNewTuples(){
    return new_inserted_tuples.size();
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

void Relation::setAttribute_as_vector(vector<string> atts) {
    attributes = atts;
}

string Relation::getAttribute(int i) {
    return attributes.at(i);
}

vector<string> Relation::getAttributes_vector() {
    return attributes;
}

int Relation::setTuple(Tuple tpl) { // make sure tuple is added in alphabetical order, based on 1st element of tuple
    int insert_index=-1;//compares current tuple with all others and checks for match
    insert_index = returnRowToInsert(tpl);  //row of insertion is determined here, ordered alphabetically
    if (insert_index!=-1)
        tuples_list.insert(tuples_list.begin() + insert_index, tpl);
    return insert_index;
}

/*bool Relation::does_match_tuples(Tuple tpl) {// compare all but indx
    bool does_it_match = false;
    int i=0;
    while(!does_it_match&&i<getRows()){
        if (tpl.getValuesList() == getTuple(i).getValuesList()) {// compare all but index
            does_it_match = true;
        }
        i++;
    }
    return does_it_match;
}*/

/*void Relation::removeTuple(int i) {
    tuples_list.erase(tuples_list.begin()+i);
}*/

void Relation::clearTuples() {
    tuples_list.clear();
}

Tuple Relation::getTuple(int i) {
    return tuples_list.at(i);
}

int Relation::returnRowToInsert(Tuple tpl) {
    int insert_index = 0;
    int curr_r = 0;
    bool stop = false;
    while(curr_r<=getRows()-1) {
        if (tpl.getValuesList() == getTuple(curr_r).getValuesList()) {// compare all but index
            stop = true;
            insert_index = -1;// loop ends if tuples are equal and returns index of -1
            curr_r = getRows();
        } else {
            int curr_c = 0;
            //BE SURE TO SET THE ATTRIBUTES BEFORE PLACING TUPLES
            while (curr_c <= getCols() - 1) {
                int eq_val = tpl.get_value(curr_c).compare(tuples_list.at(curr_r).get_value(curr_c));
                if (eq_val == 0) {   //if elements of tuples are ==
                    curr_c++;   //move ahead 1 col
                } else if (eq_val > 0) { //if element is greater move to next row...
                    curr_r++;   //next row
                    curr_c = getCols(); //restart cols
                } else {// if dif < 0, stop all!!!!
                    stop = true;
                    insert_index = curr_r;
                    curr_r = getRows();
                    curr_c = getCols();
                }
            }
            if (!stop) {
                insert_index = tuples_list.size();
            }
        }
    }
    return insert_index;
}

void Relation::rename(vector <string> tokens,vector<string> input) {    //length has to match!!!
    check_for_duplicates_in_query(tokens,input);
    int attribute_index = 0;    // in case list has changes and token list doesn't reflect col change
    for(int i=0;i<(int)tokens.size();i++){
        if (tokens.at(i) == "ID"){  // any chars in the input will result in removed cols
            int curr_tkn_index = return_var_name_index(input.at(i)); //returns index of var in var_instance_list
            int index_of_orig_for_tkn =  stoi(var_instance_list.at(curr_tkn_index).get_value(0));//index of org
            if (i == index_of_orig_for_tkn) {
                attributes.at(attribute_index) = input.at(i); //Renaming Takes Place
                attribute_index++;
            }
        }
    }
}

void Relation::select(vector <string> tokens,vector<string> input) {
    check_for_duplicates_in_query(tokens,input);
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
}

void Relation::project(vector <string> tokens,vector<string> input) {
    check_for_duplicates_in_query(tokens,input);
    vector <bool> removed_indexes;// set removed to true
    for (int i=0;i<(int)tokens.size();i++){ //interpret query first!!!
        if (tokens.at(i) != "ID") {
            removed_indexes.push_back(true);
        }else{
            int curr_id_i = return_var_name_index(input.at(i)); //returns index of var in var_instance_list
            if ((var_instance_list.at(curr_id_i).get_size()>1)&&(i!=stoi(var_instance_list.at(curr_id_i).get_value(0)))){
                // if its a repeating query att, but its it's first instance ...
                removed_indexes.push_back(true);
            } else
                removed_indexes.push_back(false);
        }
    }
    vector <bool> rm_i_copy = removed_indexes;
    for(int k=0;k<(int)rm_i_copy.size();k++){
        if (rm_i_copy.at(k)) {
            attributes.erase(attributes.begin() + k);
            rm_i_copy.erase(rm_i_copy.begin()+k);// so it matches
            k--;
        }
    }

    Relation temp_relation("t");    //creates a temp relation
    temp_relation.setAttribute_as_vector(attributes);
    for (int j=0;j<(int)tuples_list.size();j++){//for each tuple
        vector <bool> rm_i_copy2 = removed_indexes;
        for(int k=0;k<(int)rm_i_copy2.size();k++){
            if (rm_i_copy2.at(k)) {
                tuples_list.at(j).remove_value(k);
                rm_i_copy2.erase(rm_i_copy2.begin()+k);// so it matches
                k--;
            }
        }
        temp_relation.setTuple(tuples_list.at(j));  //sets new tuples in temp relation
    }
    tuples_list.clear();
    tuples_list = temp_relation.tuples_list;    //copies temp relation tuples into tuples of this relation
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

int Relation::rel_union(Relation rel) {
   // cout<<"----in UNION of relation class, new tuples ----------"<<endl;
    for (int x=0;x<(int)new_inserted_tuples.size();x++){
        Tuple* tpl = new_inserted_tuples.at(x);
        tpl = nullptr;
        delete tpl;
    }
    new_inserted_tuples.clear();
    if (attributesMatch(rel.getAttributes_vector())){
        vector<Tuple> saved_list = rel.tuples_list;// saves other relation list
        for (int i=0;i<(int)saved_list.size();i++){
            Tuple organizedTpl;
            for (int j=0;j<(int)attributes.size();j++){
                for(int k=0;k<(int)rel.getAttributes_vector().size();k++){
                    if (attributes.at(j)==rel.getAttributes_vector().at(k)) {
                        organizedTpl.add_value(saved_list.at(i).get_value(k));
                    }
                }
            }
            int new_index = setTuple(organizedTpl);
            if (new_index>-1) {  //adds i to list if does not match already placed tuples
                Tuple *tpl = new Tuple;
                *tpl = organizedTpl;
                new_inserted_tuples.push_back(tpl);
                tpl= nullptr;
                delete tpl;
            }
        }
    }
    return new_inserted_tuples.size();
}

/*void Relation::re_sortAttributes(vector<string> new_order) {
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
}*/

void Relation::rel_join(Relation rel) {//----------------------------------CHECK---------------------------------------
    vector<string> new_attributes;  // the new set of attributes this relation will have
    vector<string> old_attributes;  //old attributes will be saved for future comparisons
    vector<Tuple> matching_pairs;
    vector<int> other_indexes;  //indexes of the different attributes
    formNewAttributes(matching_pairs, new_attributes,other_indexes, attributes, rel.getAttributes_vector());
    /*cout<<"------------------------matching pairs len: "<<matching_pairs.size()<<endl;
    for(int h=0;h<(int)matching_pairs.size();h++){
        cout<<"  "<<matching_pairs.at(h).get_value(0)<<" vs. "<<matching_pairs.at(h).get_value(1)<<endl;
    }*/
    vector<Tuple> saved_list = tuples_list;
    tuples_list.clear();
    old_attributes = attributes;
    attributes = new_attributes; // so that program doesn't break in setTuples part.
    for (int i=0;i<(int)saved_list.size();i++){ //for each tuple t1 in r1
        for(int h=0;h<(int)rel.tuples_list.size();h++){// for each  tuple t2 in r2
            bool comp_match = true;
            int v=0;
            while((v<(int)matching_pairs.size())&&comp_match) {// loops through all pairs made
                int j = stoi(matching_pairs.at(v).get_value(0));
                int k = stoi(matching_pairs.at(v).get_value(1));
                if (saved_list.at(i).get_value(j) != rel.tuples_list.at(h).get_value(k)) {
                    comp_match = false;
                }
                v++;
            }
            if (comp_match) {//IF TUPLES MATCH THEY WILL BE JOINED
                Tuple joined_tpl;
                joined_tpl = create_row_tuple(saved_list.at(i),rel.tuples_list.at(h),other_indexes);
                setTuple(joined_tpl);
            }
        }
    }
}

Tuple Relation::create_row_tuple(Tuple origTpl, Tuple otherTpl, vector<int> other_indexes) {
    Tuple joined_tpl;
    for (int i=0; i<(int)origTpl.get_size();i++){//adds all values of t1 in rel1
        joined_tpl.add_value(origTpl.get_value(i));
    }
    for(int j=0;j<(int)other_indexes.size();j++){//adds all but the values that match in t1, form t2 in rel2
        joined_tpl.add_value(otherTpl.get_value(other_indexes.at(j)));
    }
    return joined_tpl;
}

void Relation::check_for_duplicates_in_query(vector <string> tokens,vector<string> input) {//duplicates in the query
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
    /*cout<<"CHECKING QUERY DUPLS"<<endl;
    for (int k=0; k<var_instance_list.size(); k++) {
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

bool Relation::all_attributesDiffer(vector<string> att) {
    bool none_are_equal = true;
    vector<string> v1 = attributes;
    vector<string> v2 = att;
    int i=0;
    while (i<(int)attributes.size()&&none_are_equal){
        int j=0;
        while (j<(int)att.size()&&none_are_equal){
            if (attributes.at(i) == att.at(j))
                none_are_equal=false;
            j++;
        }
        i++;
    }
    return none_are_equal;
}

void Relation::formNewAttributes(vector<Tuple> &matching_pairs, vector<string> &changed_att, vector<int>& other_indexes,
        vector<string> att1, vector<string> att2) {//CHECKS IF ATTRIBUTES ARE COMPARABLE OR NOT ...
    //bool can_join=true;
    vector<int> match_att_index;
    //if (!attributesMatch(att2)/*&&!all_attributesDiffer(att2)*/) {
    for (int i = 0; i < (int)att1.size(); i++) {
        for (int j = 0; j < (int)att2.size(); j++){
            if (att1.at(i) == att2.at(j)) {
                Tuple match_index;
                match_index.add_value(to_string(i));//from rel1
                match_index.add_value(to_string(j));//from rel2
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

bool Relation::foundIndex(vector<int> & vect, int val) {
    for(int i=0;i<(int)vect.size();i++){
        if (vect.at(i)==val){
            return true;
        }
    }
    return false;
}

bool Relation::foundTuple(Tuple tpl) {
    //cout<<"kek start: "<<new_inserted_tuples.size()<<endl;
    for (int x=0;x<(int)new_inserted_tuples.size();x++){
        Tuple tpl_n;
        tpl_n = *new_inserted_tuples.at(x);
        if (tpl.getValuesList() == tpl_n.getValuesList())
            return true;
        //cout<<tpl.toStringTuple()<<endl;
    }
    return false;
}
