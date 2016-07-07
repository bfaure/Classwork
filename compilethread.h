#ifndef COMPILETHREAD_H
#define COMPILETHREAD_H

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

#include "wikipage.h"
#include <QThread>

#include <string>
using std::string;
using std::getline;
using std::size_t;
using std::to_string;

#include <vector>
using std::vector;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <time.h>
#include <unistd.h>
#include <limits>
#include <stdio.h>
#include <sys/stat.h>
#include <algorithm>
#include <stdio.h>

#include <iterator>

#include "shared_data.h"
#include "direct_struct.h"

class compileThread : public QThread{
    Q_OBJECT
public:
    explicit compileThread(QObject *parent);
    void run();
    void multi_folder();            //Save by article quality only
    void content_then_quality();    //Save by article content then subfolders for quality
    void titles_only();             //Parse only specified titles
    shared_data *data;
    shared_data return_data;
    shared_data all_data;
    void set_shared_data(shared_data *share);

signals:
    void total_articles(unsigned long long);
    void send_data(const shared_data);
public slots:
    void receiveData(shared_data);
};



#endif // COMPILETHREAD_H
