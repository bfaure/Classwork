#include "shared_data.h"

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

shared_data::shared_data()
{

}
void shared_data::print(std::string input){
    //std::cout<<"Location = "<<input<<"\n";
    //std::cout<<"Articles per file = "<<articles_per_file;
    //std::cout<<"\nDatadump = "<<datadump_location;
    //std::cout<<"\nDirectory = "<<base_folder;
    //std::cout<<"\n";
    //std::cout.flush();
    QString temp = QString::fromStdString(input);
    qDebug() <<"Location = "<<temp;
    qDebug() <<"Datadump = "<<q_datadump_location;
    qDebug() <<"Directory = "<<q_base_folder;
    return;
}

void shared_data::print(){
    std::cout<<"Articles per file = "<<articles_per_file;
    std::cout<<"\nDatadump = "<<datadump_location;
    std::cout<<"\nDirectory = "<<base_folder;
    std::cout<<"\n";
    std::cout.flush();
    qDebug() <<"Datadump = "<<q_datadump_location;
    qDebug() <<"Directory = "<<q_base_folder;
    return;
}
