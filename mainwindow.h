#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

#include <QMainWindow>
#include "progresswindow.h"
#include "compilethread.h"
#include "wikipage.h"
#include <string>
#include <QFileDialog>
#include "shared_data.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    progresswindow progwindow;

signals:
    void sendData(shared_data);

private slots:

    void on_tabWidget_currentChanged(int index);

    void on_parse_txt_start_button_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_directory_input_returnPressed();

    void on_articles_per_file_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
