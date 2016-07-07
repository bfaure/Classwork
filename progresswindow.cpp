#include "progresswindow.h"
#include "ui_progresswindow.h"
#include <iostream>

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

progresswindow::progresswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::progresswindow)
{
    ui->setupUi(this);

    QPixmap wiki_pic("/Users/Faure/Desktop/wikiclassify/site/wikiclassify/images/logo.svg");
    ui->image_label->setPixmap(wiki_pic);

}

void progresswindow::startProcess(){
    //qDebug() << "Inside startProcess() in progresswindow.cpp";

    compThread = new compileThread(this);

    //qDebug() <<"Right above connect()";

    connect(compThread, SIGNAL(total_articles(unsigned long long)), this, SLOT(total_articles_changed(unsigned long long)));
    connect(this, SIGNAL(sendData(shared_data)), compThread, SLOT(receiveData(shared_data)));
    connect(compThread, SIGNAL(send_data(shared_data)), this, SLOT(progress(shared_data)));

    //qDebug() << "About to set some memory in compThread";

    compThread->all_data = data;

    //data.print("About to start compThread->start()");



    compThread->start();


    //data.print("After calling compThread->start()");

}

progresswindow::~progresswindow()
{
    delete ui;
}


void progresswindow::total_articles_changed(unsigned long long input){
    ui->total_articles_parsed->setText(QString::number(input));
    float inputf = input;
    float totalf = data.total_articles;
    float percent = inputf/totalf;
    percent = percent*100;
    int cur = percent;
    ui->progressBar->setValue(cur);
    if(inputf == totalf){
        ui->done_label->setText("Parsing Complete, click button below to open directory.");
    }
}

void progresswindow::set_shared_data(shared_data share){
    shared = new shared_data;
    //memcpy(shared, share, sizeof(*share));
}

void progresswindow::receive_data(shared_data data_input){
    data = data_input;
    if(data.multi_folder){
        ui->good_title->setText("Copies Saved");
        ui->good_title_2->setText("Copies Deleted");
        ui->good_title_3->setText("Categories");
        ui->good_title_4->setText("Copies/Category");
        ui->articles_parsed_label_2->setText("Articles Scanned");
        ui->articles_parsed_label->setText("Articles Selected");
    }
    if(data.specific_titles){
        ui->articles_parsed_label_2->setText("Articles Scanned");
        ui->articles_parsed_label->setText("Articles Matched");
        ui->good_title->setText("Redirects Found");
        ui->good_title_2->setText(" ");
        ui->good_title_3->setText(" ");
        ui->good_title_4->setText(" ");
    }
    //data.print("Inside progresswindow receive_data");
    startProcess();
}

void progresswindow::progress(shared_data input){
    if(data.specific_titles){
        ui->done_label->setText(QString::fromStdString(input.message));
        ui->bytes_processed->setText(QString::number(input.bytes));
        ui->total_articles_parsed->setText(QString::number(input.pageCt));
        ui->good_label->setText(QString::number(input.goodCt));
        return;
    }
    if(input.done){
        ui->done_label->setText("Done cleaning directory.");
    }

    ui->total_articles_parsed->setText(QString::number(input.pageCt));
    ui->good_label->setText(QString::number(input.goodCt));
    ui->bad_label->setText(QString::number(input.badCt));
    ui->reg_label->setText(QString::number(input.regCt));
    if(data.multi_folder){
        ui->redir_label->setText(QString::number(input.copy_per_cat));
         ui->bytes_processed->setText(QString::number(input.viewCt));
    }
    else{
        ui->redir_label->setText(QString::number(input.redirectCt));
         ui->bytes_processed->setText(QString::number(input.bytes));
    }



    float inputf = input.pageCt;
    float totalf = data.total_articles;
    float percent = inputf/totalf;
    percent = percent*100;
    int cur = percent;
    ui->progressBar->setValue(cur);
    if(inputf == totalf){
        ui->done_label->setText("Parsing Complete. If multi-folder, wait for cleaning.");
    }
}



void progresswindow::on_pushButton_clicked()
{
    QString directory = data.q_base_folder;
    QDesktopServices::openUrl( QUrl::fromLocalFile(directory));

}
