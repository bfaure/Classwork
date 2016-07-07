#include "direct_struct.h"

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

direct_struct::direct_struct(){
    article_ct=0;
    size=0;
    have_base = false;
}

void direct_struct::remove(){
    if(!have_base){
        return;
    }
    remove_global_directory(location);
}

void direct_struct::buffer(wikiPage input){
    art_buffer.push_back(input);
    article_ct++;
}

void direct_struct::flush(){
    if(!have_base){
        create_global_directory(location);
        have_base = true;
    }

    //This is if you want to have all subclasses combined
    /*
    for(int i=0; i<cats.size(); i++){
        if(cat_set[i] == false){
            create_global_directory(location+"/"+cats[i]);
            cat_set[i] = true;
        }
    }
    */

    for(int i=0; i<art_buffer.size(); i++){

        //This is if you want to have all subclasses combined
        string loc = location+"/"+art_buffer[i].title+".txt";
        ofstream output(loc);
        saved_locations.push_back(loc);

        //This is if you want to have subclasses in each category
        /*
        ofstream output(art_buffer[i].save_location);
        saved_locations.push_back(art_buffer[i].save_location);
        */
        art_buffer[i].save_basic(output);
    }

    art_buffer.clear();

}

void direct_struct::save(wikiPage input){
    string loc = input.save_location;
    saved_locations.push_back(loc);
    ofstream output(loc);
    input.save_basic(output);
    article_ct++;
}

void direct_struct::add_cat(string category){
    cats.push_back(category);
    cat_set.push_back(false);
}
