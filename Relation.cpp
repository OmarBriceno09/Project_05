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

string Relation::toStringNewTuples() {
    string the_output="";
    for (int i=0; i<(int)tuples_list.size(); i++){
        if(foundIndex(union_n_inserted_tuples_indexes,i)) {
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

int Relation::setTuple(Tuple tpl) { // make sure tuple is added in alphabetical order, based on 1st element of tuple
    int insert_index=-1;
    bool does_it_match = false;
    for (int i=0; i<getRows(); i++){
        if (tpl.getValuesList() == getTuple(i).getValuesList()) {
            does_it_match = true;
        }
    }
    if (!does_it_match) {
        insert_index = returnRowToInsert(tpl);  //row of insertion is determined here, ordered alphabetically
        tuples_list.insert(tuples_list.begin() + insert_index, tpl);
    }
    return insert_index;
}

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

int Relation::rel_union(Relation rel) {
    union_n_inserted_tuples_indexes.clear();
    if (attributesMatch(rel.getAttributes_vector())){
        rel.re_sortAttributes(attributes);
        for(int i=0;i<(int)rel.tuples_list.size();i++){
            int new_index =setTuple(rel.tuples_list.at(i));
            if (new_index>-1)   //adds i to list if does not match already placed tuples
                union_n_inserted_tuples_indexes.push_back(new_index);
        }
    }
    return union_n_inserted_tuples_indexes.size();
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

void Relation::rel_join(Relation rel) {
    vector<string> new_attributes;
    vector<string> matched_attributes;
    vector<int> match_att_index;
    vector<int> other_indexes;
    if (formNewAttributes(new_attributes,matched_attributes,match_att_index,other_indexes, attributes, rel.getAttributes_vector())) {// if some attributes match,
        vector<Tuple> saved_list = tuples_list;
        tuples_list.clear();
        for (int i=0;i<(int)saved_list.size();i++){ //checks rows at this relation attribute...
            for(int h=0;h<(int)rel.tuples_list.size();h++){
                bool comp_match = true;
                int j=0;
                while((j<(int)attributes.size())&&comp_match){
                    int k=0;
                    while((k<(int)matched_attributes.size())&&comp_match){
                        if (attributes.at(j) == matched_attributes.at(k)) {
                            if (saved_list.at(i).get_value(j) != rel.tuples_list.at(h).get_value(match_att_index.at(k))) {
                                comp_match=false;
                            }
                        }
                        k++;
                    }
                    j++;
                }
                if (comp_match) {
                    Tuple tpl;
                    tpl = create_row_tuple(saved_list.at(i),rel.tuples_list.at(h),other_indexes);
                    tuples_list.push_back(tpl);
                    //cout<<tpl.toStringTuple()<<endl;
                }
            }
        }
        attributes=new_attributes;
    }
}

Tuple Relation::create_row_tuple(Tuple origTpl, Tuple otherTpl, vector<int> other_indexes) {
    Tuple tpl;
    for (int i=0; i<(int)origTpl.get_size();i++){
        tpl.add_value(origTpl.get_value(i));
    }
    for(int j=0;j<(int)other_indexes.size();j++){
        tpl.add_value(otherTpl.get_value(other_indexes.at(j)));
    }
    return tpl;
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
    /*cout<<"CHECKING DUPLS"<<endl;
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

bool Relation::formNewAttributes(vector<string> &changed_att,vector<string> &matched_att,
        vector<int>& match_att_index,vector<int>& other_indexes, vector<string> att1,
        vector<string> att2) {
    bool can_join=true;
    if (!attributesMatch(att2)/*&&!all_attributesDiffer(att2)*/) {
        for (int i = 0; i < (int)att1.size(); i++) {
            for (int j = 0; j < (int)att2.size(); j++){
                if (att1.at(i) == att2.at(j)) {
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
        changed_att.reserve(att1.size() + att2.size());
        changed_att.insert(changed_att.end(), att1.begin(), att1.end());
        changed_att.insert(changed_att.end(), att2.begin(), att2.end());
        for (int i = 0; i < (int)changed_att.size(); i++) {
            for (int j = i + 1; j < (int)changed_att.size(); j++)
                if (changed_att.at(i) == changed_att.at(j)) {
                    matched_att.push_back(changed_att.at(j));
                    changed_att.erase(changed_att.begin() + j);
                }
        }
    } else
        can_join = false;
    return can_join;

}

bool Relation::foundIndex(vector<int> & vect, int val) {
    for(int i=0;i<(int)vect.size();i++){
        if (vect.at(i)==val){
            return true;
        }
    }
    return false;
}
