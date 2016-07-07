#include "mainwindow.h"
#include "ui_mainwindow.h"

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

bool has_set_datadump_file;
bool has_set_base_location;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap wiki_pic("/Users/Faure/Desktop/wikiclassify/site/wikiclassify/images/logo.svg");
    ui->wiki_image->setPixmap(wiki_pic);
    has_set_base_location=false;
    has_set_datadump_file=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==0){ //parse txt

    }
    if(index==1){ //parse html

    }
}

void MainWindow::on_parse_txt_start_button_clicked()
{
    if(!has_set_datadump_file){
        ui->warning_label->setText("You need to select a Data Dump file before beginning");
        return;
    }
    if(!has_set_base_location){
        ui->warning_label->setText("You need to select a base directory location before beginning");
        return;
    }
    bool create_filesystem = ui->create_file_system->isChecked();
    int art = ui->articles_per_file->value();
    if(art<=0){
        ui->warning_label->setText("You must choose a nonzero number of articles per page");
        ui->articles_per_file->setFocus();
        return;
    }

    QString directory_input = ui->directory_input->text();
    std::string base_folder = directory_input.toUtf8().constData();


    QString datadump_input = ui->datadump_input->text();
    std::string datadump_location = datadump_input.toUtf8().constData();

    shared_data share;

    share.q_base_folder = directory_input;
    share.total_articles = ui->tot_art_box->value();
    share.articles_per_file = art;
    share.base_folder = base_folder;
    share.create_hash = ui->hashfile_checkbox->isChecked();
    share.article_headers = ui->headers_checkbox->isChecked();
    share.equal_class_count = ui->equal_counts->isChecked();

    share.save_bad = ui->bad_check->isChecked();
    share.save_good = ui->good_check->isChecked();
    share.save_regular = ui->regular_check->isChecked();
    share.save_redirect = ui->redirect_check->isChecked();
    share.multi_folder = ui->multiple_checkbox->isChecked();
    share.specific_titles = ui->titles_checkbox->isChecked();

    /*
    if(!share.save_bad and !share.save_good and !share.save_redirect and !share.save_regular){
        ui->warning_label->setText("Check one of the save boxes before starting.");
        return;
    }
    */

    if(create_filesystem){
        share.base_folder = base_folder+"/";
    }
    else{
        share.base_folder = base_folder+"/";
    }

    share.datadump_location = datadump_location;
    share.q_datadump_location = datadump_input;
    share.keep_formatting = !ui->parse_formatting->isChecked();

    if(create_filesystem and !share.multi_folder and !share.specific_titles){
        setup_no_parsed_folder(base_folder, share.save_good, share.save_bad, share.save_regular, share.save_redirect);
    }

    this->hide();

    connect(this, SIGNAL(sendData(shared_data)), &progwindow, SLOT(receive_data(shared_data)));
    progwindow.setModal(true);
    progwindow.open();
    emit sendData(share);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, "", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->directory_input->setText(directory);
    //ui->directory_input->setText("/Users/Faure/Desktop/parsed");
    if(directory==NULL){
        return;
    }
    has_set_base_location=true;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "", "", "XML Files (*.xml)");
    ui->datadump_input->setText(file);
    //ui->datadump_input->setText("/Users/Faure/Desktop/wikiclassify/data/sources/wikipedia/enwiki-20160113-pages-articles.xml");
    if(file==NULL){
        return;
    }
    has_set_datadump_file=true;
}

void MainWindow::on_directory_input_returnPressed()
{

}

void MainWindow::on_articles_per_file_valueChanged(int arg1)
{
    ui->warning_label->setText("Denotes the number of articles packaged in each file");
}
