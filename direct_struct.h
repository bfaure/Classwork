#ifndef DIRECT_STRUCT_H
#define DIRECT_STRUCT_H

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <wikipage.h>

#include <iterator>


class direct_struct
{
public:
    direct_struct();
    string name;
    string location;
    bool have_base;
    unsigned long long created;
    int article_ct;
    unsigned long long size;
    vector<string> cats;
    vector<bool> cat_set;

    vector<wikiPage> art_buffer;
    vector<string> saved_locations;

    void buffer(wikiPage input);
    void save(wikiPage input);
    void flush();
    void remove();
    void add_cat(string category);
};




#endif // DIRECT_STRUCT_H

