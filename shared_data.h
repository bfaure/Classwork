#ifndef SHARED_DATA_H
#define SHARED_DATA_H

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

#include <string>
#include <iostream>
#include <QDebug>

class shared_data
{

public:
    shared_data();
    void print();
    void print(std::string input);

    int articles_per_file;
    bool keep_formatting;
    bool create_hash;
    bool article_headers;
    bool equal_class_count;
    int total_articles;
    bool specific_titles;
    bool done;
    float copy_per_cat;
    std::string message;

    std::string datadump_location;
    QString q_datadump_location;

    std::string base_folder;
    QString q_base_folder;


    unsigned long long pageCt;
    unsigned long goodCt;
    unsigned long redirectCt;
    unsigned long regCt;
    unsigned long badCt;
    unsigned long viewCt;

    bool save_regular;
    bool save_good;
    bool save_bad;
    bool save_redirect;

    bool multi_folder;

    unsigned long bytes;
};

#endif // SHARED_DATA_H
