#ifndef PROGRESSWINDOW_H
#define PROGRESSWINDOW_H

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

#include "compilethread.h"
#include <QDialog>
#include <string>
#include "wikipage.h"
#include "shared_data.h"
#include <stdio.h>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class progresswindow;
}

class progresswindow : public QDialog
{
    Q_OBJECT

public:
    explicit progresswindow(QWidget *parent=0);
    ~progresswindow();
    void startProcess();
    void set_shared_data(shared_data share);
    compileThread *compThread;
    shared_data data;
    shared_data *shared;

private:
    Ui::progresswindow *ui;


public slots:
    void total_articles_changed(unsigned long long input);
    void receive_data(shared_data);
    void progress(shared_data);
signals:
    void sendData(shared_data);

private slots:
    void on_pushButton_clicked();
};

#endif // PROGRESSWINDOW_H
